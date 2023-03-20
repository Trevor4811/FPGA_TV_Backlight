#ifndef CONV_H_
#define CONV_H_
#define EDGE_WIDTH 16
#define EDGE_HEIGHT 2000
#define NUM_LEDS_PER_EDGE 40

#include <ap_int.h>
#include "conv.h"

typedef ap_int<8> pixel_data_t;
typedef ap_int<20> acc_t;
typedef ap_int<12> mat_sum_t;

int STEP_SIZE = EDGE_HEIGHT/NUM_LEDS_PER_EDGE;

void conv_edge(
	pixel_data_t edge_results[NUM_LEDS_PER_EDGE],
	pixel_data_t input_pixels[EDGE_HEIGHT][EDGE_WIDTH]);

#endif
