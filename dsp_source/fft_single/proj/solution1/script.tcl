############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project proj
set_top fft_top
add_files fft_top.cpp
add_files -tb data/stimulus_19.res
add_files -tb data/stimulus_18.res
add_files -tb data/stimulus_17.res
add_files -tb data/stimulus_16.res
add_files -tb data/stimulus_15.res
add_files -tb data/stimulus_14.res
add_files -tb data/stimulus_13.res
add_files -tb data/stimulus_12.res
add_files -tb data/stimulus_11.res
add_files -tb data/stimulus_10.res
add_files -tb data/stimulus_09.res
add_files -tb data/stimulus_08.res
add_files -tb data/stimulus_07.res
add_files -tb data/stimulus_06.res
add_files -tb data/stimulus_05.res
add_files -tb data/stimulus_04.res
add_files -tb data/stimulus_03.res
add_files -tb data/stimulus_02.res
add_files -tb data/stimulus_01.res
add_files -tb data/stimulus_00.res
add_files -tb data/stimulus_19.dat
add_files -tb data/stimulus_18.dat
add_files -tb data/stimulus_17.dat
add_files -tb data/stimulus_16.dat
add_files -tb data/stimulus_15.dat
add_files -tb data/stimulus_14.dat
add_files -tb data/stimulus_13.dat
add_files -tb data/stimulus_12.dat
add_files -tb data/stimulus_11.dat
add_files -tb data/stimulus_10.dat
add_files -tb data/stimulus_09.dat
add_files -tb data/stimulus_08.dat
add_files -tb data/stimulus_07.dat
add_files -tb data/stimulus_06.dat
add_files -tb data/stimulus_05.dat
add_files -tb data/stimulus_04.dat
add_files -tb data/stimulus_03.dat
add_files -tb data/stimulus_02.dat
add_files -tb data/stimulus_01.dat
add_files -tb data/stimulus_00.dat
add_files -tb fft_tb.cpp
open_solution "solution1"
set_part {xazu2eg-sbva484-1-i}
create_clock -period 3.3 -name default
config_dataflow -default_channel fifo -fifo_depth 1 -strict_mode warning
config_sdx -optimization_level none -target none
config_bind -effort medium
config_schedule -effort medium -relax_ii_for_timing=0
set_clock_uncertainty 12.5%
#source "./proj/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
