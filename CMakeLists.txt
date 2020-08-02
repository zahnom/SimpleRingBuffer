cmake_minimum_required(VERSION 3.14)
project(SimpleRingBuffer)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
add_subdirectory(googletest)
add_subdirectory(test)