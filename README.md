# FPGA TV Backlight
We are developing an FPGA based TV backlighting system that uses HDMI pass through on a PYNQ Z2 development board to display an image to a TV/monitor while simultaneously running computations on each frame to decide the backlight color pattern. We are using individually addressable rgb LEDs as a backlight, allowing us to decide color on an LED by LED basis. We are developing two seperate modes. 

## Mode 1 - Edge Color Matching
The first mode is an edge extension mode that uses convolution on the pixels around the edge of the image to color match each LED to what is on the screen next to the currrent frame.

Matrix convolution is a common method for applying effects to images including sharpening, edge detection, blurring, and more. The convolution applied to one part of the image does not affect the convolution on another part of the image meaning these tasks can be run in parallel making it suitable for an FPGA.



## Mode 2 - matching the most common color in an image
average_screen.ipynb takes in Sample6.png as an input. Then, it calculates the most common and second most common colors to appear in the image. It will then output these two colors as two 200x200 pixel images. 

It does this by taking in the image and creating individual arrays for the r, g, and b values. It then creates another array for each color that is 256 integers long. This array is filled with how many times a certain color value appears (every time r=112 is seen, +1 to the 112th position in the r array)
Once that array is filled, it is known how many times every value for r, g, and b appear in the image. These values are called and combined to create the most common colors.


