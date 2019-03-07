############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project MFCC
set_top MFCC_main
add_files MFCC/hamming_original.cpp
add_files MFCC/hamming_original.h
add_files -tb MFCC/solution1/fft_tb.cpp -cflags "-Wno-unknown-pragmas"
add_files -tb MFCC/solution1/csim/build/goldenMFCC_yes.dat
add_files -tb MFCC/solution1/csim/build/wavData_yes.dat
open_solution "solution1"
set_part {xczu3eg-sbva484-1-e} -tool vivado
create_clock -period 10 -name default
config_compile -no_signed_zeros=0 -unsafe_math_optimizations=0
config_schedule -effort medium -enable_dsp_full_reg=0 -relax_ii_for_timing=0 -verbose=0
config_dataflow -default_channel fifo -fifo_depth 1 -strict_mode warning
#source "./MFCC/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -setup -trace_level port
export_design -format ip_catalog
