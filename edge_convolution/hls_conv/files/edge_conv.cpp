#include "edge_conv.h"
#include "conv.h"

// 5 original with smaller data types
void edge_conv(
	pixel_data_t edge_results[NUM_LEDS_PER_EDGE],
	pixel_data_t input_pixels[EDGE_HEIGHT][EDGE_WIDTH])
{
int i;


Edge_Conv_Loop:
for (i = 0; i < NUM_LEDS_PER_EDGE; i++) {
	conv(&(edge_results[i]), &(input_pixels[i*STEP_SIZE][0]));
}

}
