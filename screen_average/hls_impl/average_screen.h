#ifndef AVERAGE_SCREEN_H_
#define AVERAGE_SCREEN_H_

#include <ap_int.h>
#include <stdio.h>
#include <string.h>

typedef ap_int<8> color_array;

#define IMAGE_WIDTH 711
#define IMAGE_HEIGHT 360

int color255[256] = {0};

void average_screen(
		color_array *result,
		color_array input_array[IMAGE_WIDTH][IMAGE_HEIGHT]
);

#endif
