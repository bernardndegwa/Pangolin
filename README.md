What is Pangolin {#mainpage}
====================================

Pangolin is a lightweight portable rapid development library for managing OpenGL
display / interaction and abstracting video input. At its heart is a simple
OpenGl viewport manager which can help to modularise 3D visualisation without
adding to its complexity, and offers an advanced but intuitive 3D navigation
handler. Pangolin also provides a mechanism for manipulating program variables
through config files and ui integration, and has a flexible real-time plotter
for visualising graphical data.

The ethos of Pangolin is to reduce the boilerplate code that normally
gets written to visualise and interact with (typically image and 3D
based) systems, without compromising performance. It also enables write-once
code for a number of platforms, currently including Windows, Linux, OSX, Android
and IOS.

## Code ##

Find the latest version on [Github](http://github.com/stevenlovegrove/Pangolin):
>     git clone https://github.com/stevenlovegrove/Pangolin.git

Current build status on [Drone.io](https://drone.io/github.com/stevenlovegrove/Pangolin)
![Build Status](https://drone.io/github.com/stevenlovegrove/Pangolin/status.png)

## Dependencies ##

Optional dependencies are enabled when found, otherwise they are silently disabled.
Check the CMake configure output for details.

### Required Dependencies ###

* OpenGL (Desktop / ES / ES2)

* CMake (for build environment)
 * (win) http://www.cmake.org/cmake/resources/software.html
 * (deb) sudo apt-get install cmake
 * (mac) sudo port install cmake

### Recommended Dependencies ###

* Glut / GLU / Glew (Required for window management on OSX/Win/Linux)
 * (win) http://www.transmissionzero.co.uk/software/freeglut-devel/
 * (deb) sudo apt-get install freeglut3-dev libglu-dev libglew-dev
 * (mac) sudo port install freeglut glew
 * (mac) OsxGlut for smooth scroll/zoom: https://github.com/stevenlovegrove/osxglut

* Boost (optional with C++11. Configure with 'cmake -DCPP11_NO_BOOST=1 ..' )
 * (win) http://www.boost.org/users/download/
 * (deb) sudo apt-get install libboost-dev libboost-thread-dev libboost-filesystem-dev
 * (mac) sudo port install boost

### Optional Dependencies for video input ###

* FFMPEG (For video decoding and image rescaling)
 * (deb) sudo apt-get install ffmpeg libavcodec-dev libavutil-dev libavformat-dev libswscale-dev

* DC1394 (For firewire input)
 * (deb) sudo apt-get install libdc1394-22-dev libraw1394-dev

* libuvc (For cross-platform webcam video input via libusb)
 * git://github.com/ktossell/libuvc.git

* libjpeg, libpng (For reading still-image sequences)

* OpenNI / OpenNI2 (For Kinect / Xtrion / Primesense capture)

* DepthSense SDK

### Very Optional Dependencies ###

* GLConsole (For graphical drop-down console. Must be built before Pangolin.)
 * git clone git://git.code.sf.net/p/glconsole/code glconsole

* Eigen / TooN (These matrix types supported in the Pangolin API.)

* CUDA Toolkit (>= 3.2)
 * http://developer.nvidia.com/object/cuda_3_2_downloads.html

