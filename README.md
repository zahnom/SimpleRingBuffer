[ ![Download](https://api.bintray.com/packages/zahnom/conan-main/SimpleRingBuffer%3Azahnom/images/download.svg) ](https://bintray.com/zahnom/conan-main/SimpleRingBuffer%3Azahnom/_latestVersion)

# SimpleRingBuffer
A simple ring buffer implementation in C.

# Building from sources
## Preconditions
- Make sure you have the [Conan package manager](https://conan.io/) installed.

## Importing into CLion
CLion is the recommended development environment for this project.
1. Clone and import the project into CLion.
2. In CLion, load the top-level `CMakeLists.txt` file. You should get an error like 
  ```
  CMake Error at CMakeLists.txt:7 (include):
    include could not find load file:

    /Users/zahnom/CLionProjects/SimpleRingBuffer/cmake-build-debug/conanbuildinfo.cmake


  CMake Error at CMakeLists.txt:8 (conan_basic_setup):
    Unknown CMake command "conan_basic_setup".
  ```
3. CLion has made a build folder, like `cmake-build-debug`. `cd` into this folder and run `conan install ..`.
4. Load the top-level `CMakeLists.txt` again. It should work now.

## Using plain command line
1. Clone the repo.
2. Create a build directory.
3. Change into build directory and run `conan install ..`.
4. Run `cmake ..` and afterwards `make`.
