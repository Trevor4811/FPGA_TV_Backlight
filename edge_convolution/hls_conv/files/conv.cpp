#include "conv.h"

// 5 original with smaller data types
void conv(
	pixel_data_t *result,
	pixel_data_t input_pixels[CONV_HEIGHT][CONV_WIDTH]
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
			acc += input_pixels[x][y] * CONV_ARRAY[x][y];
		}
	}

Division:
	*result = acc/MATRIX_SUM;
}
