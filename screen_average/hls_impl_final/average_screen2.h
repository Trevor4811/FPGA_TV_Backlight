#ifndef AVERAGE_SCREEN_H_
#define AVERAGE_SCREEN_H_

#include <ap_int.h>
#include <stdio.h>
#include <string.h>

typedef ap_uint<8> color_array;

#define IMAGE_LENGTH 255960
//#define IMAGE_LENGTH 11

ap_uint<64> color255[256] = {0};

#endif
