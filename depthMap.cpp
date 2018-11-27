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

// Define CNN network model object
CKerasDepthMap network;

// Buffer for decoded image data
uint32_t imgView[IMAGE_W * IMAGE_H];
// Buffer for pre-processed image data
__fp16 imgProc[IMAGE_RZ_W * IMAGE_RZ_H * 3];

// Pre-processing function
void opencv2dmp(cv::Mat& input_frm, COverlayRGB& output_frm, bool isColor = true);

int main(int argc, char** argv) {
  // Initialize FB
  if (!init_fb()) {
    cout << "init_fb() failed." << endl;
    return 1;
  }

  // Get input images filenames
  vector<string> image_names;
  get_jpeg_image_names("./images/", image_names);
  int num_images = image_names.size();
  if (num_images == 0) {
    cout << "No input images." << endl;
    return 1;
  }

  // Initialize network object
  network.Verbose(0);
  if (!network.Initialize()) {
    return -1;
  }
  if (!network.LoadWeights(FILENAME_WEIGHTS)) {
    return -1;
  }
  if (!network.Commit()) {
    return -1;
  }

  // Get HW module frequency
  string conv_freq;
  conv_freq = std::to_string(network.get_dv_info().conv_freq);

  // Create background, image, and output overlay
  COverlayRGB bg_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.alloc_mem_overlay(SCREEN_W, SCREEN_H);
  bg_overlay.load_ppm_img("fpgatitle");
  COverlayRGB overlay_input(SCREEN_W, SCREEN_H);
  overlay_input.alloc_mem_overlay(IMAGE_W, IMAGE_H);
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

  int exit_code = -1;
  int image_nr = 0;
  bool pause = false;
  std::vector<float> networkOutput;
  std::vector<float> networkOutput_transposed(IMAGE_RZ_H*IMAGE_RZ_W);
  // Enter main loop
  while (exit_code == -1) {
    // If not pause, decode next JPEG image and do pre-processing
    if (!pause) {
      decode_jpg_file(image_names[image_nr], imgView, IMAGE_W, IMAGE_H);
      overlay_input.convert_to_overlay_pixel_format(imgView, IMAGE_W * IMAGE_H);
      preproc_image(imgView, imgProc, IMAGE_W, IMAGE_H, IMAGE_RZ_W, IMAGE_RZ_H,
                    0, 0, 0, 1.0 / 255.0, true);
      ++image_nr;
      image_nr %= num_images;
    }

    // Run network in HW
    memcpy(network.get_network_input_addr_cpu(), imgProc, IMAGE_W * IMAGE_H * 6);
    network.RunNetwork();

    // Handle output from HW
    network.get_final_output(networkOutput);
    // The values returned from get_final_output() is still transposed (height first) format.
    // So it is actually a width=128, height=384 image
    // need to transpose the output before you can compare to the Keras output.
    for(int y = 0 ; y < IMAGE_RZ_H; y++)
      for(int x = 0 ; x < IMAGE_RZ_W; x++)
        networkOutput_transposed[x+y*IMAGE_RZ_W] = networkOutput[y+x*IMAGE_RZ_H]*255;

    // Convert depth to color map
    cv::Mat matDepth(IMAGE_RZ_H, IMAGE_RZ_W, CV_32FC1, networkOutput_transposed.data());
    cv::Mat matDepth_8UC1;
    matDepth.convertTo(matDepth_8UC1, CV_8U);
    cv::Mat matDepth_8UC3, matDepth_color;
    cv::cvtColor(matDepth_8UC1,matDepth_8UC3,CV_GRAY2RGB);
    cv::applyColorMap(matDepth_8UC3, matDepth_color, cv::ColormapTypes::COLORMAP_JET);
    cv::Mat matDepth_color_resized;
    cv::resize( matDepth_color , matDepth_color_resized , cv::Size( IMAGE_W, IMAGE_H ), 0, 0, CV_INTER_LINEAR);
    opencv2dmp( matDepth_color_resized, overlay_output );

    // Draw results
    overlay_input.print_to_display(((SCREEN_W - IMAGE_W) / 2), ((SCREEN_H - IMAGE_H) / 2)-110);
    overlay_output.print_to_display(((SCREEN_W - IMAGE_W) / 2), ((SCREEN_H + IMAGE_H) / 2)-110);

    // Output HW processing times
    int conv_time_tot = network.get_conv_usec();
    print_conv_time(bg_overlay, 8 * SCREEN_H / 9 + 10, conv_time_tot, conv_freq);

    swap_buffer();

    handle_keyboard_input(exit_code, pause);
  }

  shutdown();

  return exit_code;
}

/**
 * @brief Convert opencv image format to dmp board frame format
 *
 * @param input_frm      opencv image format
 * @param output_frm dmp board image format
 * @param isColor        input_fram is color or grayscale
 */
void opencv2dmp(cv::Mat& input_frm, COverlayRGB& output_frm, bool isColor){
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
