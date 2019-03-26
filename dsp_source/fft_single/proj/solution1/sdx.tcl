# ==============================================================
# File generated on Fri Mar 08 13:32:31 CET 2019
# Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
# SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
# IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
# Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
# ==============================================================
add_files -tb ../../fft_tb.cpp -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_00.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_01.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_02.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_03.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_04.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_05.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_06.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_07.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_08.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_09.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_10.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_11.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_12.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_13.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_14.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_15.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_16.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_17.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_18.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_19.dat -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_00.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_01.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_02.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_03.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_04.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_05.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_06.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_07.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_08.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_09.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_10.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_11.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_12.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_13.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_14.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_15.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_16.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_17.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_18.res -cflags { -Wno-unknown-pragmas}
add_files -tb ../../data/stimulus_19.res -cflags { -Wno-unknown-pragmas}
add_files fft_top.cpp
set_part xazu2eg-sbva484-1-i
create_clock -name default -period 3.3
set_clock_uncertainty 12.5% default
config_dataflow -default_channel=fifo
config_dataflow -fifo_depth=1
config_dataflow -strict_mode=warning
config_sdx -optimization_level=none
config_sdx -target=none
config_bind -effort=medium
config_schedule -effort=medium
config_schedule -relax_ii_for_timing=0
