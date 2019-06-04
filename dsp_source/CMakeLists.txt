# CMake script for FFT
# Define project name
project (generate_log_mel_filterbank_energies)
# Define version and C++ standard
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
# Add executable
add_executable(generate_log_mel_filterbank_energies dsp_source.cpp)
# Set compile options
target_compile_options(generate_log_mel_filterbank_energies PUBLIC -g)

