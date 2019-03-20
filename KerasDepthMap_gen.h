/*
 *  Copyright 2018 Digital Media Professionals Inc.

 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at

 *      http://www.apache.org/licenses/LICENSE-2.0

 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.

 *  This source code was generated using DMP-DV700 tools.
 */
#pragma once

#include "dmp_network.h"

class CKerasDepthMap : public CDMP_Network {
 private:
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 0 | FPGA-Layer | Convolution | (384, 128, 3) | (192, 64, 32) | - | - |
  | 0-0 | cnv1 | Convolution | (384, 128, 3) | (192, 64, 32) | - | 13888 |

  */
  void Layer_0();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 1 | FPGA-Layer | Convolution | (192, 64, 32) | (192, 64, 32) | - | - |
  | 1-0 | cnv1b | Convolution | (192, 64, 32) | (192, 64, 32) | - | 147520 |

  */
  void Layer_1();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 2 | FPGA-Layer | Convolution | (192, 64, 32) | (96, 32, 64) | - | - |
  | 2-0 | cnv2 | Convolution | (192, 64, 32) | (96, 32, 64) | - | 147584 |

  */
  void Layer_2();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 3 | FPGA-Layer | Convolution | (96, 32, 64) | (96, 32, 64) | - | - |
  | 3-0 | cnv2b | Convolution | (96, 32, 64) | (96, 32, 64) | - | 295040 |

  */
  void Layer_3();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 4 | FPGA-Layer | Convolution | (96, 32, 64) | (48, 16, 128) | - | - |
  | 4-0 | cnv3 | Convolution | (96, 32, 64) | (48, 16, 128) | - | 147712 |

  */
  void Layer_4();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 5 | FPGA-Layer | Convolution | (48, 16, 128) | (48, 16, 128) | - | - |
  | 5-0 | cnv3b | Convolution | (48, 16, 128) | (48, 16, 128) | - | 295168 |

  */
  void Layer_5();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 6 | FPGA-Layer | Convolution | (48, 16, 128) | (24, 8, 256) | - | - |
  | 6-0 | cnv4 | Convolution | (48, 16, 128) | (24, 8, 256) | - | 590336 |

  */
  void Layer_6();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 7 | FPGA-Layer | Convolution | (24, 8, 256) | (24, 8, 256) | - | - |
  | 7-0 | cnv4b | Convolution | (24, 8, 256) | (24, 8, 256) | - | 1180160 |

  */
  void Layer_7();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 8 | FPGA-Layer | Convolution | (24, 8, 256) | (12, 4, 512) | - | - |
  | 8-0 | cnv5 | Convolution | (24, 8, 256) | (12, 4, 512) | - | 2360320 |

  */
  void Layer_8();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 9 | FPGA-Layer | Convolution | (12, 4, 512) | (12, 4, 512) | - | - |
  | 9-0 | cnv5b | Convolution | (12, 4, 512) | (12, 4, 512) | - | 4719616 |

  */
  void Layer_9();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 10 | FPGA-Layer | Convolution | (12, 4, 512) | (6, 2, 512) | - | - |
  | 10-0 | cnv6 | Convolution | (12, 4, 512) | (6, 2, 512) | - | 4719616 |

  */
  void Layer_10();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 11 | FPGA-Layer | Convolution | (6, 2, 512) | (6, 2, 512) | - | - |
  | 11-0 | cnv6b | Convolution | (6, 2, 512) | (6, 2, 512) | - | 4719616 |

  */
  void Layer_11();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 12 | FPGA-Layer | Convolution | (6, 2, 512) | (3, 1, 512) | - | - |
  | 12-0 | cnv7 | Convolution | (6, 2, 512) | (3, 1, 512) | - | 4719616 |

  */
  void Layer_12();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 13 | FPGA-Layer | Convolution | (3, 1, 512) | (3, 1, 512) | - | - |
  | 13-0 | cnv7b | Convolution | (3, 1, 512) | (3, 1, 512) | - | 4719616 |

  */
  void Layer_13();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 14 | FPGA-Layer | Convolution | (3, 1, 512) | (6, 2, 512) | - | - |
  | 14-0 | up_sampling2d_1 | UpSampling | (3, 1, 512) | (6, 2, 512) | - | - |

  */
  void Layer_14();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 15 | FPGA-Layer | Convolution | (6, 2, 512) | (6, 2, 512) | - | - |
  | 15-0 | upcnv7 | Convolution | (6, 2, 512) | (6, 2, 512) | - | 4719616 |

  */
  void Layer_15();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 16 | FPGA-Layer | Concatenate | (6, 2, 1024) | (6, 2, 1024) | - | - |

  */
  void Layer_16();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 17 | FPGA-Layer | Convolution | (6, 2, 1024) | (6, 2, 512) | - | - |
  | 17-0 | icnv7 | Convolution | (6, 2, 1024) | (6, 2, 512) | - | 9438208 |

  */
  void Layer_17();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 18 | FPGA-Layer | Convolution | (6, 2, 512) | (12, 4, 512) | - | - |
  | 18-0 | up_sampling2d_2 | UpSampling | (6, 2, 512) | (12, 4, 512) | - | - |

  */
  void Layer_18();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 19 | FPGA-Layer | Convolution | (12, 4, 512) | (12, 4, 512) | - | - |
  | 19-0 | upcnv6 | Convolution | (12, 4, 512) | (12, 4, 512) | - | 4719616 |

  */
  void Layer_19();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 20 | FPGA-Layer | Concatenate | (12, 4, 1024) | (12, 4, 1024) | - | - |

  */
  void Layer_20();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 21 | FPGA-Layer | Convolution | (12, 4, 1024) | (12, 4, 512) | - | - |
  | 21-0 | icnv6 | Convolution | (12, 4, 1024) | (12, 4, 512) | - | 9438208 |

  */
  void Layer_21();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 22 | FPGA-Layer | Convolution | (12, 4, 512) | (24, 8, 512) | - | - |
  | 22-0 | up_sampling2d_3 | UpSampling | (12, 4, 512) | (24, 8, 512) | - | - |

  */
  void Layer_22();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 23 | FPGA-Layer | Convolution | (24, 8, 512) | (24, 8, 256) | - | - |
  | 23-0 | upcnv5 | Convolution | (24, 8, 512) | (24, 8, 256) | - | 2359808 |

  */
  void Layer_23();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 24 | FPGA-Layer | Concatenate | (24, 8, 512) | (24, 8, 512) | - | - |

  */
  void Layer_24();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 25 | FPGA-Layer | Convolution | (24, 8, 512) | (24, 8, 256) | - | - |
  | 25-0 | icnv5 | Convolution | (24, 8, 512) | (24, 8, 256) | - | 2359808 |

  */
  void Layer_25();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 26 | FPGA-Layer | Convolution | (24, 8, 256) | (48, 16, 256) | - | - |
  | 26-0 | up_sampling2d_4 | UpSampling | (24, 8, 256) | (48, 16, 256) | - | - |

  */
  void Layer_26();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 27 | FPGA-Layer | Convolution | (48, 16, 256) | (48, 16, 128) | - | - |
  | 27-0 | upcnv4 | Convolution | (48, 16, 256) | (48, 16, 128) | - | 590080 |

  */
  void Layer_27();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 28 | FPGA-Layer | Concatenate | (48, 16, 256) | (48, 16, 256) | - | - |

  */
  void Layer_28();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 29 | FPGA-Layer | Convolution | (48, 16, 256) | (48, 16, 128) | - | - |
  | 29-0 | icnv4 | Convolution | (48, 16, 256) | (48, 16, 128) | - | 590080 |

  */
  void Layer_29();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 30 | FPGA-Layer | Convolution | (48, 16, 128) | (96, 32, 128) | - | - |
  | 30-0 | up_sampling2d_6 | UpSampling | (48, 16, 128) | (96, 32, 128) | - | - |

  */
  void Layer_30();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 31 | FPGA-Layer | Convolution | (96, 32, 128) | (96, 32, 64) | - | - |
  | 31-0 | upcnv3 | Convolution | (96, 32, 128) | (96, 32, 64) | - | 147584 |

  */
  void Layer_31();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 32 | FPGA-Layer | Convolution | (48, 16, 128) | (48, 16, 1) | - | - |
  | 32-0 | disp4 | Convolution | (48, 16, 128) | (48, 16, 1) | - | 2320 |

  */
  void Layer_32();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 33 | FPGA-Layer | Convolution | (48, 16, 1) | (48, 16, 1) | - | - |
  | 33-0 | depthwise_conv2d_1 | Convolution | (48, 16, 1) | (48, 16, 1) | - | 160 |

  */
  void Layer_33();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 34 | FPGA-Layer | Convolution | (48, 16, 1) | (96, 32, 1) | - | - |
  | 34-0 | up_sampling2d_5 | UpSampling | (48, 16, 1) | (96, 32, 1) | - | - |

  */
  void Layer_34();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 35 | FPGA-Layer | Concatenate | (96, 32, 129) | (96, 32, 129) | - | - |

  */
  void Layer_35();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 36 | FPGA-Layer | Convolution | (96, 32, 129) | (96, 32, 64) | - | - |
  | 36-0 | icnv3 | Convolution | (96, 32, 129) | (96, 32, 64) | - | 156800 |

  */
  void Layer_36();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 37 | FPGA-Layer | Convolution | (96, 32, 64) | (192, 64, 64) | - | - |
  | 37-0 | up_sampling2d_8 | UpSampling | (96, 32, 64) | (192, 64, 64) | - | - |

  */
  void Layer_37();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 38 | FPGA-Layer | Convolution | (192, 64, 64) | (192, 64, 32) | - | - |
  | 38-0 | upcnv2 | Convolution | (192, 64, 64) | (192, 64, 32) | - | 36928 |

  */
  void Layer_38();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 39 | FPGA-Layer | Convolution | (96, 32, 64) | (96, 32, 1) | - | - |
  | 39-0 | disp3 | Convolution | (96, 32, 64) | (96, 32, 1) | - | 1168 |

  */
  void Layer_39();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 40 | FPGA-Layer | Convolution | (96, 32, 1) | (96, 32, 1) | - | - |
  | 40-0 | depthwise_conv2d_2 | Convolution | (96, 32, 1) | (96, 32, 1) | - | 160 |

  */
  void Layer_40();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 41 | FPGA-Layer | Convolution | (96, 32, 1) | (192, 64, 1) | - | - |
  | 41-0 | up_sampling2d_7 | UpSampling | (96, 32, 1) | (192, 64, 1) | - | - |

  */
  void Layer_41();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 42 | FPGA-Layer | Concatenate | (192, 64, 65) | (192, 64, 65) | - | - |

  */
  void Layer_42();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 43 | FPGA-Layer | Convolution | (192, 64, 65) | (192, 64, 32) | - | - |
  | 43-0 | icnv2 | Convolution | (192, 64, 65) | (192, 64, 32) | - | 41536 |

  */
  void Layer_43();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 44 | FPGA-Layer | Convolution | (192, 64, 32) | (384, 128, 32) | - | - |
  | 44-0 | up_sampling2d_10 | UpSampling | (192, 64, 32) | (384, 128, 32) | - | - |

  */
  void Layer_44();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 45 | FPGA-Layer | Convolution | (384, 128, 32) | (384, 128, 16) | - | - |
  | 45-0 | upcnv1 | Convolution | (384, 128, 32) | (384, 128, 16) | - | 9248 |

  */
  void Layer_45();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 46 | FPGA-Layer | Convolution | (192, 64, 32) | (192, 64, 1) | - | - |
  | 46-0 | disp2 | Convolution | (192, 64, 32) | (192, 64, 1) | - | 592 |

  */
  void Layer_46();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 47 | FPGA-Layer | Convolution | (192, 64, 1) | (192, 64, 1) | - | - |
  | 47-0 | depthwise_conv2d_3 | Convolution | (192, 64, 1) | (192, 64, 1) | - | 160 |

  */
  void Layer_47();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 48 | FPGA-Layer | Convolution | (192, 64, 1) | (384, 128, 1) | - | - |
  | 48-0 | up_sampling2d_9 | UpSampling | (192, 64, 1) | (384, 128, 1) | - | - |

  */
  void Layer_48();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 49 | FPGA-Layer | Concatenate | (384, 128, 17) | (384, 128, 17) | - | - |

  */
  void Layer_49();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 50 | FPGA-Layer | Convolution | (384, 128, 17) | (384, 128, 16) | - | - |
  | 50-0 | icnv1 | Convolution | (384, 128, 17) | (384, 128, 16) | - | 6944 |

  */
  void Layer_50();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 51 | FPGA-Layer | Convolution | (384, 128, 16) | (384, 128, 1) | - | - |
  | 51-0 | disp1 | Convolution | (384, 128, 16) | (384, 128, 1) | - | 304 |

  */
  void Layer_51();
  /*!

  Layer description

  | ID | Layers | Type | Dim In | Dim Out | Param | Mem |
  | :- | :- | :-: | :-: | :-: | :-: | :-: |
  | 52 | FPGA-Layer | Convolution | (384, 128, 1) | (49152,) | - | - |
  | 52-0 | depthwise_conv2d_4 | Convolution | (384, 128, 1) | (384, 128, 1) | - | 160 |

  */
  void Layer_52();

 public:
  virtual bool Initialize();
  CKerasDepthMap();
  virtual ~CKerasDepthMap();
};
