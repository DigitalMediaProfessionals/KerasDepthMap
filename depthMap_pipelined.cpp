/*
 *  Copyright 2018 Digital Media Professionals Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <ctime>

#include "KerasDepthMap_gen.h"
#include "util_draw.h"
#include "util_input.h"
#include "demo_common.h"

#define DMP_MEASURE_TIME
#include "util_time.h"

using namespace std;
using namespace dmp;
using namespace util;

#define SCREEN_W (get_screen_width())
#define SCREEN_H (get_screen_height())

#define IMAGE_W 768
#define IMAGE_H 256

#define IMAGE_RZ_W 384
#define IMAGE_RZ_H 128

#define FILENAME_WEIGHTS "../KerasDepthMap_weights.bin"

#define RING_BUF_SIZE 5
#define USLEEP_TIME 100000

// Define CNN network model object
CKerasDepthMap network;
int exit_code = -1;
bool do_pause = false;

// Buffer for pre-processed image data
__fp16 imgProc[IMAGE_RZ_W * IMAGE_RZ_H * 3][RING_BUF_SIZE];
// Buffer for overlay_input
COverlayRGB *overlay_input[RING_BUF_SIZE];
// Buffer for network output
vector<float> net_output[RING_BUF_SIZE];

unsigned preproc_rbuf_idx     = 0;
unsigned inreference_rbuf_idx = 0;
unsigned postproc_rbuf_idx    = 0;

void increment_circular_variable(unsigned &v, unsigned max) {
  v++;
  if(v > max) {
    v = 0;
  }
}

/**
 * @brief Convert opencv image format to dmp board frame format
 *
 * @param input_frm      opencv image format
 * @param output_frm dmp board image format
 * @param isColor        input_fram is color or grayscale
 */
void opencv2dmp(cv::Mat& input_frm, COverlayRGB& output_frm, bool isColor = true) {
  if( input_frm.cols != IMAGE_RZ_W && input_frm.rows != IMAGE_RZ_H ){
      output_frm.alloc_mem_overlay(input_frm.cols, input_frm.rows);
  }
  // int i = 0;
  for (unsigned int h=0;h<output_frm.get_overlay_height();h++) {
    for(unsigned int w=0;w<output_frm.get_overlay_width();w++) {
      if(isColor){
        cv::Vec3b intensity = input_frm.at<cv::Vec3b>(h, w);
        uchar blue = intensity.val[0];
        uchar green = intensity.val[1];
        uchar red = intensity.val[2];
        output_frm.set_pixel(w,h, red, green, blue);
        // if(++i<32)
        //   printf("%d %d %d\n", red, green, blue);
      }else{
        uchar intensity = input_frm.at<uchar>(h, w);
        output_frm.set_pixel(w,h, intensity, intensity, intensity);
      }
    }
  }
}

void *preproc(void *) {
  uint32_t imgView[IMAGE_W * IMAGE_H];
  unsigned &rbuf_idx = preproc_rbuf_idx;

  // Get input images filenames
  vector<string> image_names;
  get_jpeg_image_names("./images/", image_names);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    exit_code = 2;
    return NULL;
  }

  unsigned image_nr = 0;
  while (exit_code == -1) {
    while ((rbuf_idx + 1) % RING_BUF_SIZE == postproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }
    DECLARE_TVAL(preproc);
    GET_TVAL_START(preproc);

    // If not pause, decode next JPEG image and do pre-processing
    if (!do_pause) {
      decode_jpg_file(image_names[image_nr], imgView, IMAGE_W, IMAGE_H);
      overlay_input[rbuf_idx]->convert_to_overlay_pixel_format(imgView, IMAGE_W * IMAGE_H);
      preproc_image(imgView, imgProc[rbuf_idx], IMAGE_W, IMAGE_H, IMAGE_RZ_W, IMAGE_RZ_H,
                    0, 0, 0, 1.0 / 255.0, true);

      increment_circular_variable(image_nr, num_images - 1);
    }

    GET_SHOW_TVAL_END(preproc);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }
  return NULL;
}

void *inference(void *) {
  unsigned &rbuf_idx = inreference_rbuf_idx;

  // Initialize network object
  while (exit_code == -1) {
    while (rbuf_idx == preproc_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(inference);
    GET_TVAL_START(inference);

    // Run network in HW
    memcpy(network.get_network_input_addr_cpu(), imgProc[rbuf_idx], IMAGE_RZ_W * IMAGE_RZ_H * 6);
    network.RunNetwork();

    // Handle output from HW
    network.get_final_output(net_output[rbuf_idx]);

    GET_SHOW_TVAL_END(inference);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }

  return NULL;
}

void *postproc(void *) {
  unsigned &rbuf_idx = postproc_rbuf_idx;

  // Get HW module frequency
  string conv_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);

  // Create background, image, and output overlay
  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle");
  COverlayRGB overlay_output(SCREEN_W, SCREEN_H);
  overlay_output.alloc_mem_overlay(IMAGE_W, IMAGE_H);

  // Draw background two times for front and back buffer
  const char *titles[] = {
    "Depth Map",
    "Per-Pixel Depth Estimation",
  };
  for (int i = 0; i < 2; ++i) {
    bg_overlay.print_to_display(0, 0);
    print_demo_title(bg_overlay, titles);
    swap_buffer();
  }

#ifdef DMP_MEASURE_TIME
  DECLARE_TVAL(swap_buffer);
  TVAL_START(swap_buffer).tv_sec = 0;
#endif
  while(exit_code == -1) {
    while(rbuf_idx == inreference_rbuf_idx) {
      usleep(USLEEP_TIME);
    }

    DECLARE_TVAL(postproc);
    GET_TVAL_START(postproc);

    // The values returned from get_final_output() is still transposed (height first) format.
    // So it is actually a width=128, height=384 image
    // need to transpose the output before you can compare to the Keras output.
    vector<float> networkOutput_transposed(IMAGE_RZ_H*IMAGE_RZ_W);
    for(int y = 0 ; y < IMAGE_RZ_H; y++) {
      for(int x = 0 ; x < IMAGE_RZ_W; x++) {
        networkOutput_transposed[x+y*IMAGE_RZ_W] = net_output[rbuf_idx][y+x*IMAGE_RZ_H]*255;
      }
    }

    // Convert depth to color map
    cv::Mat matDepth(IMAGE_RZ_H, IMAGE_RZ_W, CV_32FC1, networkOutput_transposed.data());
    cv::Mat matDepth_8UC1;
    matDepth.convertTo(matDepth_8UC1, CV_8U);
    cv::Mat matDepth_8UC3, matDepth_color;
    cv::cvtColor(matDepth_8UC1,matDepth_8UC3,CV_GRAY2RGB);
    cv::applyColorMap(matDepth_8UC3, matDepth_color, cv::ColormapTypes::COLORMAP_JET);
    cv::Mat matDepth_color_resized;
    cv::resize(matDepth_color , matDepth_color_resized , cv::Size( IMAGE_W, IMAGE_H ), 0, 0, CV_INTER_LINEAR);
    opencv2dmp(matDepth_color_resized, overlay_output );

    // Draw results
    overlay_input[rbuf_idx]->print_to_display(((SCREEN_W - IMAGE_W) / 2), ((SCREEN_H - IMAGE_H) / 2)-110);
    overlay_output.print_to_display(((SCREEN_W - IMAGE_W) / 2), ((SCREEN_H + IMAGE_H) / 2)-110);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 8 * SCREEN_H / 9 + 10, conv_time_tot, conv_freq);

    swap_buffer();
#ifdef DMP_MEASURE_TIME
    GET_TVAL_END(swap_buffer);
    if(TVAL_START(swap_buffer).tv_sec) {
      SHOW_TIME(swap_buffer);
    }
    TVAL_START(swap_buffer).tv_sec = TVAL_END(swap_buffer).tv_sec;
    TVAL_START(swap_buffer).tv_usec = TVAL_END(swap_buffer).tv_usec;
    cout << endl;
#endif

    handle_keyboard_input(exit_code, do_pause);

    GET_SHOW_TVAL_END(postproc);
    increment_circular_variable(rbuf_idx, RING_BUF_SIZE - 1);
  }
  return NULL;
}

int main(int argc, char** argv) {
  // Initialize FB
  if (!init_fb()) {
    cerr << "init_fb() failed." << endl;
    exit_code = 1;
    goto error;
  }
  for(int i = 0; i < RING_BUF_SIZE; i++) {
    overlay_input[i] = new COverlayRGB(SCREEN_W, SCREEN_H);
    if(!overlay_input[i]) {
      cerr << "fail to allocate COverlayRGB" << endl;
      exit_code = 1;
      goto error;
    }
    overlay_input[i]->alloc_mem_overlay(IMAGE_W, IMAGE_H);
  }

  // Initialize Network
  network.Verbose(0);
  if (!network.Initialize()) {
    exit_code = 1;
    goto error;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    exit_code = 1;
    goto error;
  }
  if (!network.Commit()) {
    exit_code = 1;
    goto error;
  }

  pthread_t preproc_th;
  pthread_t inf_th;
  pthread_t postproc_th;

  pthread_create(&preproc_th,  NULL, preproc, NULL);
  pthread_create(&inf_th,      NULL, inference, NULL);
  pthread_create(&postproc_th, NULL, postproc, NULL);

  pthread_join(preproc_th,  NULL);
  pthread_join(inf_th,      NULL);
  pthread_join(postproc_th, NULL);

error:
  shutdown();
  for(int i = 0; i < RING_BUF_SIZE; i++) {
    if(overlay_input[i]) {
      delete overlay_input[i];
    }
  }

  return exit_code;
}

