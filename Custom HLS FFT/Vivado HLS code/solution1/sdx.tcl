# ==============================================================
# File generated on Wed Jun 05 21:03:54 CEST 2019
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../wav_data.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../../speech_commands_v0.01/golden_mel.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../fft_tb.cpp -cflags { -Wno-unknown-pragmas}
add_files HLS/hamming_original.h
add_files HLS/hamming_original.cpp
add_files HLS/FFT_top.h
add_files HLS/FFT_top.cpp
set_part xczu3eg-sbva484-1-i
create_clock -name default -period 10
set_clock_uncertainty 12.5% default
config_compile -no_signed_zeros=0
config_compile -unsafe_math_optimizations=0
config_schedule -effort=medium
config_schedule -enable_dsp_full_reg=0
config_schedule -relax_ii_for_timing=0
config_schedule -verbose=0
config_bind -effort=medium
config_sdx -optimization_level=none
config_sdx -target=none
