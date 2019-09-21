# Screensaver based on OpenGL

# To execute 

Before executing, install following packages:

1) for glm: sudo apt-get install libglm-dev
2) for stb: git clone https://github.com/nothings/stb.git && cp ./stb/stb_image.h

Then, use this command to run:
mkdir build && cd build && cmake .. && make && ./main

# Options:
1) Moving of the main triangle:
a) WSAD - forward, left, back, right;
b) R/F - up, down;
c) Q/E - turning to the left/right regarding to vertical axle.
2) ESCAPE - close.
