############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project MFCC
set_top window_FFT
add_files MFCC/hamming_original.h
add_files MFCC/hamming_original.cpp
add_files MFCC/FFT_top.h
add_files MFCC/FFT_top.cpp
add_files -tb ../speech_commands_v0.01/wav_data.dat -cflags "-Wno-unknown-pragmas"
add_files -tb ../speech_commands_v0.01/golden_mel.dat -cflags "-Wno-unknown-pragmas"
add_files -tb MFCC/solution1/fft_tb.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xczu3eg-sbva484-1-e} -tool vivado
create_clock -period 10 -name default
config_compile -no_signed_zeros=0 -unsafe_math_optimizations=0
config_sdx -optimization_level none -profile 0 -target none
config_schedule -effort medium -enable_dsp_full_reg=0 -relax_ii_for_timing=0 -verbose=0
config_dataflow -default_channel fifo -fifo_depth 1 -strict_mode warning
config_bind -effort medium
set_clock_uncertainty 12.5%
#source "./MFCC/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design -compiled_library_dir "/home/anders/master/MFCC/solution1/sim/verilog" -tool xsim
export_design -format ip_catalog
