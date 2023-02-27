#include "conv.h"

// 5 original with smaller data types
void conv(
	pixel_data_t *result,
	pixel_data_t input_pixels[CONV_HEIGHT][CONV_WIDTH],
	pixel_data_t conv_array[CONV_HEIGHT][CONV_WIDTH],
	mat_sum_t matrix_sum
	)
{
	int x;
	int y;
	acc_t acc;

Multiply_Sum_Loop:
	acc = 0;
	for (y = 0; y < CONV_HEIGHT; y++)
	{
//#pragma HLS UNROLL
		for (x = 0; x < CONV_WIDTH; x++)
		{
//#pragma HLS UNROLL
			acc += input_pixels[x][y] * conv_array[x][y];
		}
	}

Division:
	*result = acc/matrix_sum;
}
