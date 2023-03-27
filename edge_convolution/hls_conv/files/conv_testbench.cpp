#include <iostream>
//#include "conv.h"
//#include "conv.cpp"
#include <ap_int.h>
using namespace std;

typedef ap_uint<8> 	pixel_data_t;
#define CONV_LENGTH 496

void conv (
		pixel_data_t *result,
			volatile pixel_data_t *input_pixels
  );

int main()
{
    // Establish an initial return value. 0 = success
    int ret;

    // Call any preliminary functions required to prepare input for the test.
    pixel_data_t input_arr[CONV_LENGTH] = {169, 168, 168, 171, 170, 169, 169, 168, 169, 172, 174, 175, 174, 174, 172, 170,
    166, 165, 167, 170, 168, 167, 168, 168, 168, 169, 172, 173, 173, 172, 171, 169,
    164, 165, 167, 169, 168, 167, 168, 169, 169, 169, 169, 168, 168, 169, 169, 170,
    167, 166, 166, 167, 168, 168, 169, 169, 169, 170, 170, 168, 168, 170, 171, 172,
    171, 168, 167, 167, 168, 169, 169, 169, 167, 172, 173, 172, 172, 172, 172, 171,
    171, 169, 168, 168, 167, 168, 169, 170, 166, 171, 173, 172, 171, 172, 172, 171,
    168, 167, 167, 167, 167, 168, 169, 169, 170, 172, 172, 171, 171, 172, 173, 174,
    167, 166, 166, 167, 169, 170, 170, 169, 171, 171, 170, 171, 172, 172, 172, 174,
    168, 168, 167, 167, 171, 169, 165, 165, 169, 170, 169, 170, 173, 172, 171, 173,
    168, 168, 166, 165, 168, 166, 163, 164, 169, 169, 169, 170, 172, 172, 171, 172,
    167, 165, 163, 164, 166, 166, 165, 166, 169, 169, 169, 170, 171, 171, 171, 170,
    167, 165, 164, 165, 166, 167, 167, 169, 170, 169, 170, 170, 169, 170, 171, 169,
    168, 167, 167, 166, 166, 168, 169, 170, 170, 169, 170, 170, 166, 169, 171, 169,
    165, 164, 165, 165, 164, 167, 168, 169, 170, 170, 171, 170, 167, 170, 172, 170,
    165, 163, 164, 166, 166, 167, 169, 170, 170, 172, 171, 170, 169, 171, 173, 171,
    167, 164, 165, 167, 166, 167, 169, 170, 167, 170, 170, 168, 169, 171, 172, 171,
    167, 166, 167, 167, 165, 166, 169, 168, 167, 168, 170, 167, 165, 167, 169, 173,
    167, 167, 169, 170, 168, 168, 169, 168, 170, 169, 170, 167, 167, 170, 170, 171,
    168, 169, 169, 169, 169, 168, 169, 169, 169, 167, 167, 166, 167, 170, 168, 168,
    168, 169, 168, 169, 170, 170, 169, 170, 169, 167, 168, 167, 167, 169, 168, 171,
    167, 168, 168, 169, 172, 172, 170, 170, 169, 168, 169, 169, 168, 168, 169, 176,
    167, 167, 167, 168, 171, 171, 170, 169, 167, 167, 169, 171, 171, 169, 167, 173,
    167, 166, 166, 167, 168, 168, 169, 169, 165, 165, 167, 172, 173, 168, 165, 169,
    167, 167, 168, 169, 168, 167, 168, 168, 167, 167, 167, 169, 170, 168, 166, 170,
    167, 168, 170, 169, 168, 166, 165, 166, 169, 170, 168, 167, 170, 171, 171, 173,
    167, 166, 167, 166, 166, 167, 166, 166, 168, 168, 168, 170, 172, 171, 171, 175,
    167, 165, 165, 164, 166, 169, 167, 167, 170, 169, 169, 172, 174, 171, 170, 174,
    166, 165, 166, 166, 167, 169, 168, 168, 172, 170, 169, 172, 175, 171, 169, 172,
    166, 166, 166, 166, 168, 171, 170, 171, 172, 170, 169, 171, 174, 173, 170, 171,
    167, 165, 164, 164, 167, 171, 172, 172, 170, 169, 168, 169, 172, 174, 173, 172,
    166, 165, 166, 164, 166, 170, 170, 171, 168, 169, 168, 169, 171, 173, 173, 171};
 
    // Call the top-level function multiple times, passing input stimuli as needed.
    // for (i = 0; i < NUM_TRANS; i++)
    // {
    //     top_func(input, output);
    // }
    pixel_data_t output;
    conv(&output, input_arr);

    // Capture the output results of the function, write to a file

    // Compare the results of the function against expected results
    // ret = system("diff --brief  -w output.dat output.golden.dat");

    if (output != 167)
    {
        cout << "Test failed  !!!\n" << output << "\n";
        ret = 1;
    }
    else
    {
    	cout << "Test success  !\n";
        ret = 0;
    }

    return ret;
}
