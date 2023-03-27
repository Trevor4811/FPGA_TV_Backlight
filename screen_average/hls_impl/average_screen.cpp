#include "average_screen.h"

void average_screen(
		color_array *result,
		volatile color_array* input_array
)
{
#pragma HLS INTERFACE mode=s_axilite port=return
#pragma HLS INTERFACE mode=s_axilite port=result
#pragma HLS INTERFACE mode=m_axi port=input_array depth=50 offset=slave

	int i;
	color_array num;
	color_array max = 0;
	int buff[IMAGE_LENGTH];

	//memcpy creates a burst access to memory
	//multiple calls of memcpy cannot be pipelined and will be scheduled sequentially
	//memcpy requires a local buffer to store the results of the memory transaction
	memcpy(buff,(const color_array*)input_array,IMAGE_LENGTH*sizeof(color_array*));

Find_Color_Loop:
	for(i = 0; i < IMAGE_LENGTH; i++) {
				num = input_array[i];
				color255[num] += 1;
		}

Find_Max_Loop:
	for(i = 0; i < 256; i++) {
		if(i ==0) {
			max = i;
		}
		else {
			if(color255[i] > color255[max]) {
				max = i;
			}
		}
	}

	*result = max;
	memcpy((color_array *)input_array, &max, sizeof(color_array));

}
