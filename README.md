# FPGA TV Backlight
We are developing an FPGA based TV backlighting system that uses HDMI pass through on a PYNQ Z2 development board to display an image to a TV/monitor while simultaneously running computations on each frame to decide the backlight color pattern. We are using individually addressable rgb LEDs as a backlight, allowing us to decide color on an LED by LED basis. We are developing two seperate modes. 

--------------------------------
## Inputs and Outputs
### Inputs:
The inputs will be 24-bit RGB or BGR images/video frames that we will be stored locally on the PYNQ board. A further implementation would be to use the HDMI input to accept a video stream, duplicate the frames, and send them through the FPGA conversion as well as to the HDMI output to a screen. 

### Outputs:
The outputs will be the numerical color values for each LED location based on the video input. A further implementation would be to actually output the color values to an addressable LED strip.

--------------------------------
## Processing Modes
### Mode 1 - Edge Color Matching
#### *Summary:*
The first mode is an edge extension mode that uses convolution on the pixels around the edge of the image to color match each LED to what is on the screen next to the currrent frame.

Matrix convolution is a common method for applying effects to images including sharpening, edge detection, blurring, and more. The convolution applied to one part of the image does not affect the convolution on another part of the image meaning these tasks can be run in parallel making it suitable for an FPGA.

#### *Usage Instructions*
The final hardware version is updated in the [HLS Convolution](./edge_convolution/hls_conv/files) folder. This contains all of the necessary files to run it on the Pynq-Z2 board as well as all of the source files to rebuild the project from scratch.

To run this add the [overlay](./edge_convolution/hls_conv/files/overlay/) files into a folder at the following location on the PYNQ Z2 board `'/home/xilinx/pynq/overlays/conv/'`. Then add the python [jupyter notebook](./edge_convolution/hls_conv/edge_conv_hw_sw_comparison.ipynb) and [sample image](./edge_convolution/hls_conv/sample.jpg) to the PYNQ board and run it. There is one section in the jupyter notebook that has a test script for the convolution to test the single convolution used in the testbench. Then there is a script to run both the sw and hw convolution versions on an entire image and compare them both in time and the result values. The edge color results are saved as images in [results](./edge_convolution/hls_conv/results/) and the hw and sw version results can be visually compared. 

### Mode 2 - matching the most common color in an image
#### *Summary:*
This mode is a color analysis mode that analyzes the r, g, and b values of every pixel in a .png file. It then determines the two most common colors that appear within the image.
The two most common colors are determined by figuring out what the two most common r, g, and b values are. This is done with numpy arrays that keep track of every value that appears. The most common two are then selected and combined to create the respective most and second most common colors.

#### *Project Update 1:*

average_screen.ipynb takes in Sample6.png as an input. Then, it calculates the most common and second most common colors to appear in the image. It will then output these two colors as two 200x200 pixel images. 

It does this by taking in the image and creating individual arrays for the r, g, and b values. It then creates another array for each color that is 256 integers long. This array is filled with how many times a certain color value appears (every time r=112 is seen, +1 to the 112th position in the r array)
Once that array is filled, it is known how many times every value for r, g, and b appear in the image. These values are called and combined to create the most common colors. This code can be run by running the entire Jupyter Notebook on the PYNQ board or a computer with all the neccessary import dependencies.

#### *Project Update 2:*
[HLS Screen Average](./screen_average/)\
Designed a screen averaging HLS function in screen_average.cpp and screen_average.h to find the most common color value in an inputted array. Uses the master AXI input for the array input from ps into pl, however it will be switched to streaming for reasons discussed in the issues portion. The script was compiled into IP to be used in Vivado.

The compilied HLS IP was added to Vivado with connection automation and manual steps to create the block diagram. The block diagram has all of the connections for the master AXI interface. This was then compiled into a bitstream so that it can be used in python to be run in the Jupyter notebooks and ultimately compared to the PL time. The output files can be found in the [overlay](./screen_average/overlay/) folder.

To run this add the overlay files into a folder at the following location on the PYNQ Z2 board `'/home/xilinx/pynq/overlays/screen_average/'`. Then add the python [jupyter notebook](./screen_average/average_screen_hardware.ipynb) and [sample image](./screen_average/Sample6.png) to the PYNQ board and run all of the cells.


**Issues:** 

The issue with the current implementation is that there is some sort of issue when attempting to get the result. The function can take in an array and correctly identify the most common value, but when the result is called it is always 0 or seg faults. We spent a lot of time troubleshooting this with a TA to no gain. Because of this, we will be pivoting to a streaming design instead of using the master AXI method. This in-progress implementation can be found in the [hls_impl2](./screen_average/hls_impl2) folder.

--------------------------------

## Evaluation
These algorithms are both deterministice making it easy to calculate expected output values based on the input image and the filter applied to verify correctness. Since our FPGA is outputting these values we can verify them against the expected output LED values. 

The more interesting aspect of success is the speed at which we can convert images to pixel colors for the LED’s. Ideally, this would be as fast as possible to minimize the latency between the image being displayed and the colors of the LED’s updating. Thus we will strive for the total latency to be at least less than the period of a 30Hz display (33.3 ms).


--------------------------------
