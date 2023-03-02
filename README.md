# FPGA TV Backlight
We are developing an FPGA based TV backlighting system that uses HDMI pass through on a PYNQ Z2 development board to display an image to a TV/monitor while simultaneously running computations on each frame to decide the backlight color pattern. We are using individually addressable rgb LEDs as a backlight, allowing us to decide color on an LED by LED basis. We are developing two seperate modes. 

--------------------------------
## Inputs and Outputs
### Inputs:
The inputs will be 24-bit RGB or BGR images/video frames that we will be stored locally on the PYNQ board. Then time permitting, we will use the HDMI input to accept a video stream, duplicate the frames, and send them through the FPGA conversion as well as to the HDMI output to a screen. 

### Outputs:
The outputs will depend on our implementation. Our primary goal is to calculate the numerical color values for each LED location based on the video input. A further implementation would be to actually output the color values to an addressable LED strip.

--------------------------------
## Processing Modes
### Mode 1 - Edge Color Matching
#### *Summary:*
The first mode is an edge extension mode that uses convolution on the pixels around the edge of the image to color match each LED to what is on the screen next to the currrent frame.

Matrix convolution is a common method for applying effects to images including sharpening, edge detection, blurring, and more. The convolution applied to one part of the image does not affect the convolution on another part of the image meaning these tasks can be run in parallel making it suitable for an FPGA.

#### *Project Update 1:*
[Python Implementation](./edge_convolution/python_impl/single_image_convolution.ipynb)\
The Python implementation for this mode is fully designed. This code takes in an image and a convolution matrix. Then runs the image through a function to create seperate arrays for each of the edges in a uniform shape. The the convolution matrix is applied to each array of edges. This works by applying the matrix convolution on the edge spaced for the set number of LEDs along that edge. Then the RGB outputs for each LED are stored. It took 0.0986 sec to run this process on the test image on the ZYNQ board. This code can be run by running the entire Jupyter Notebook on the PYNQ board or a computer with all the neccessary import dependencies.

[HLS Convolution](./edge_convolution/hls_conv/files)\
Designed a basic convolution HLS function in conv.cpp and conv.h to apply the convolution matrix to a given input. Have not yet verified the output of the function. The next step will be to compile this function into a bitstream so the functionallity may be used in python to compare doing the convolution on the FPGS vs the PL. 

Also started to outline an HLS function in edge_conv.cpp and edge_conv.h to apply the convolution across the entire edge of the image in the FPGA.


### Mode 2 - matching the most common color in an image
#### *Summary:*
This mode is a color analysis mode that analyzes the r, g, and b values of every pixel in a .png file. It then determines the two most common colors that appear within the image.
The two most common colors are determined by figuring out what the two most common r, g, and b values are. This is done with numpy arrays that keep track of every value that appears. The most common two are then selected and combined to create the respective most and second most common colors.

#### *Project Update 1:*

average_screen.ipynb takes in Sample6.png as an input. Then, it calculates the most common and second most common colors to appear in the image. It will then output these two colors as two 200x200 pixel images. 

It does this by taking in the image and creating individual arrays for the r, g, and b values. It then creates another array for each color that is 256 integers long. This array is filled with how many times a certain color value appears (every time r=112 is seen, +1 to the 112th position in the r array)
Once that array is filled, it is known how many times every value for r, g, and b appear in the image. These values are called and combined to create the most common colors. This code can be run by running the entire Jupyter Notebook on the PYNQ board or a computer with all the neccessary import dependencies.


--------------------------------

## Evaluation
These algorithms are both deterministice making it easy to calculate expected output values based on the input image and the filter applied to verify correctness. Since our FPGA is outputting these values we can verify them against the expected output LED values. 

The more interesting aspect of success is the speed at which we can convert images to pixel colors for the LED’s. Ideally, this would be as fast as possible to minimize the latency between the image being displayed and the colors of the LED’s updating. Thus we will strive for the total latency to be at least less than the period of a 30Hz display (33.3 ms). One strict requirement for success is that the PL implementation will be faster than the PS implementation, otherwise, there would be no point in the FPGA implementation.





--------------------------------
