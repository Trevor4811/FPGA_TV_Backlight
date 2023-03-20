#include "average_screen.h"

void average_screen(
		color_array *result,
		color_array *input_array
)
{
#pragma HLS INTERFACE s_axilite port=return
#pragma HLS INTERFACE s_axilite port=result
#pragma HLS INTERFACE m_axi port=input_array offset=slave

	int i;
	int j;
	//color_array buff[IMAGE_WIDTH*IMAGE_HEIGHT];

	//memcpy creates a burst access to memory
	//multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
	//memcpy requires a local buffer to store the results of the memory transaction
	//memcpy(buff,(const color_array*)input_array,IMAGE_WIDTH*IMAGE_HEIGHT*sizeof(color_array));

Find_Color_Loop:
	for(i = 0; i < IMAGE_WIDTH*IMAGE_HEIGHT; i++) {
			color255[input_array[i]] += 1;
		}

	int max = color255[0];
Find_Max_Loop:
	for(i = 1; i < 256; i++) {
		if(color255[i] > max)
			max = color255[i];
	}

	*result = max;

}
