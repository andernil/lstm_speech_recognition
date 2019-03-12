# CMake script for FFT
# Define project name
project (HLS_FFT)
# Define version and C++ standard
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
# Add executable
add_executable(HLS_FFT hamming_original.cpp)
# Set compile options
target_compile_options(HLS_FFT PUBLIC -g)

