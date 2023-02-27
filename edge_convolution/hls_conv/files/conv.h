#ifndef CONV_H_
#define CONV_H_
#define CONV_WIDTH 16
#define CONV_HEIGHT 31

#include <ap_int.h>

typedef ap_int<8> 	pixel_data_t;
typedef ap_int<20> 	acc_t;
typedef ap_int<12> 	mat_sum_t;

void conv (
	pixel_data_t *result,
    pixel_data_t input_pixels[CONV_HEIGHT][CONV_WIDTH],
	pixel_data_t conv_array[CONV_HEIGHT][CONV_WIDTH],
	mat_sum_t matrix_sum
  );

#endif
