#include "conv.h"
#include <stdio.h>
#include <string.h>

// 5 original with smaller data types
void conv(
	pixel_data_t *result,
	volatile pixel_data_t *input_pixels
	)
{
#pragma HLS interface s_axilite port=return
#pragma HLS INTERFACE m_axi port=input_pixels depth=50 offset=slave
#pragma HLS INTERFACE s_axilite port=result


	int x;
	acc_t acc;
	pixel_data_t out;

	pixel_data_t buff[CONV_LENGTH];

	//memcpy creates a burst access to memory
  	//multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
  	//memcpy requires a local buffer to store the results of the memory transaction
 	memcpy(buff,(const pixel_data_t*)input_pixels,CONV_LENGTH*sizeof(pixel_data_t));

Multiply_Sum_Loop:
	acc = 0;
	for (x = 0; x < CONV_LENGTH; x++)
	{
// #pragma HLS UNROLL
		acc += buff[x] * CONV_ARRAY[x];
	}

Division:
	out = acc/MATRIX_SUM;
	*result = out;
	memcpy((pixel_data_t *)input_pixels, &out, sizeof(pixel_data_t));
}
