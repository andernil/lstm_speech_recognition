This repository contains the files used for a masters thesis at NTNU during Spring 2019. The thesis involved FPGA-acceleration of keyword spotting neural networks using Intel OpenVINO and Xilinx DNNDK. In addition to the networks, the pre-processing for the networks was accelerated on FPGA using Vivado HLS.


Instructions:
To run pre-processing on all target words for the Google Speech Commands dataset, compile dsp_source and copy the compiled program, along with generate_all_mels.py and generate_mels.py into the dataset root folder, such as speech_commands_v0.01/. Run the scripts using Python 3.
