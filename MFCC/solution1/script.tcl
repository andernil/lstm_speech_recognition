############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project MFCC
set_top MFCC_main
add_files Vivado_HLS/hamming_original.cpp
open_solution "solution1"
set_part {xczu3eg-sbva484-1-e} -tool vivado
create_clock -period 10 -name default
#source "./MFCC/solution1/directives.tcl"
#csim_design
csynth_design
#cosim_design
export_design -format ip_catalog
