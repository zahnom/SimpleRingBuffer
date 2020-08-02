# SimpleRingBuffer
A simple ring buffer implementation in C.

# Installation
## Preconditions
- Make sure you have the Conan package manager installed.

## Clone and import project into CLion
CLion is the recommended development environment for this project.
1. Clone and import the project into CLion.
2. In CLion, load the top-level CMakeLists.txt file. You should get an error like 
  ```
  CMake Error at CMakeLists.txt:7 (include):
    include could not find load file:

    /Users/zahnom/CLionProjects/SimpleRingBuffer/cmake-build-debug/conanbuildinfo.cmake


  CMake Error at CMakeLists.txt:8 (conan_basic_setup):
    Unknown CMake command "conan_basic_setup".
  ```
3. CLion has made a build folder, like `cmake-build-debug`. `cd` into this folder and run `conan install ..`.
4. Load the top-level CMakeLists.txt again. It should work now.

## Clone project using plain command line
1. Clone the repo.
2. Create a build directory.
3. Change into build directory and run `conan install ..`.
4. Run `cmake ..`.
5. Run `make`.
