/*
 * Copyright 2021 Xilinx, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file contains an example for creating an AXI4-master interface in Vivado HLS
 */
				      
#include <stdio.h>
#include <string.h>
#include "example.h"

#define LENGTH 496
#define MATRIX_SUM 2511

// Defined convolution array
pixel_data_t CONV_ARRAY[LENGTH] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                        16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                        18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0,
                        20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0,
                        22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0,
                        24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0,
                        26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0,
                        28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0,
                        30, 28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1,
                        28, 26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0,
                        26, 24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0,
                        24, 22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0,
                        22, 20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0,
                        20, 18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0,
                        18, 16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0,
                        16, 14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0,
                        14, 12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0,
                        12, 10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        10, 8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        8, 6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        6, 4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        4, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                        1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Convolution function. Set as topfile
void example(volatile pixel_data_t *a){
#pragma HLS INTERFACE mode=m_axi depth=50 port=a offset=slave
#pragma HLS INTERFACE s_axilite port=return

  counter_t i;
  pixel_data_t buff[496];
  acc_t acc;
  pixel_data_t out;
  
  //memcpy creates a burst access to memory
  //multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
  //memcpy requires a local buffer to store the results of the memory transaction
  memcpy(buff,(const pixel_data_t*)a,LENGTH*sizeof(pixel_data_t));

  acc = 0;
  Multiply_Sum_Loop:
  for(i=0; i < LENGTH; i++){
    #pragma HLS UNROLL factor=8
    acc += buff[i] * CONV_ARRAY[i];
  }
  
  Division:
  out = acc/MATRIX_SUM;

  memcpy((pixel_data_t *)a,&out,sizeof(pixel_data_t));
}


// Version for simulation. Does not seem to return result properly during simulation
// by storing it back in the input array as is done in the version above.
void conv (
		pixel_data_t *result,
			volatile pixel_data_t *a
  ){
#pragma HLS INTERFACE m_axi port=a depth=50 offset=slave
#pragma HLS INTERFACE s_axilite port=return

  counter_t i;
  pixel_data_t buff[496];
  acc_t acc;
  pixel_data_t out;

  //memcpy creates a burst access to memory
  //multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
  //memcpy requires a local buffer to store the results of the memory transaction
  memcpy(buff,(const pixel_data_t*)a,LENGTH*sizeof(pixel_data_t));

  acc = 0;
  Multiply_Sum_Loop:
  for(i=0; i < LENGTH; i++){
    acc += buff[i] * CONV_ARRAY[i];
  }

  Division:
  *result = acc/MATRIX_SUM;

}

