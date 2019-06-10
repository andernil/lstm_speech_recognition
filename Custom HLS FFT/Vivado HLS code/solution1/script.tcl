############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project HLS
set_top window_FFT
add_files HLS/FFT_top.cpp
add_files HLS/FFT_top.h
add_files HLS/hamming_original.cpp
add_files HLS/hamming_original.h
add_files -tb HLS/fft_tb.cpp
add_files -tb ../speech_commands_v0.01/golden_mel.dat -cflags "-Wno-unknown-pragmas"
add_files -tb HLS/wav_data.dat -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xczu3eg-sbva484-1-i}
create_clock -period 10 -name default
config_compile  
config_schedule -effort medium  -relax_ii_for_timing=0 
config_bind -effort medium
config_sdx -optimization_level none -target none
#source "./HLS/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
