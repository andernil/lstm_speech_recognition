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
add_files -tb MFCC/solution1/csim/build/goldenMFCC.dat
add_files -tb MFCC/solution1/csim/build/wavData.dat
open_solution "solution1"
set_part {xczu3eg-sbva484-1-e} -tool vivado
create_clock -period 10 -name default
#source "./MFCC/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
