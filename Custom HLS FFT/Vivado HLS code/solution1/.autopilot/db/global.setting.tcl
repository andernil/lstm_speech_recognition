
set TopModule "window_FFT"
set ClockPeriod 10
set ClockList ap_clk
set HasVivadoClockPeriod 0
set CombLogicFlag 0
set PipelineFlag 0
set DataflowTaskPipelineFlag 1
set TrivialPipelineFlag 0
set noPortSwitchingFlag 0
set FloatingPointFlag 1
set FftOrFirFlag 1
set NbRWValue 0
set intNbAccess 0
set NewDSPMapping 1
set HasDSPModule 0
set ResetLevelFlag 1
set ResetStyle control
set ResetSyncFlag 1
set ResetRegisterFlag 0
set ResetVariableFlag 0
set FsmEncStyle onehot
set MaxFanout 0
set RtlPrefix {}
set ExtraCCFlags {}
set ExtraCLdFlags {}
set SynCheckOptions {}
set PresynOptions {}
set PreprocOptions {}
set SchedOptions {}
set BindOptions {}
set RtlGenOptions {}
set RtlWriterOptions {}
set CbcGenFlag {}
set CasGenFlag {}
set CasMonitorFlag {}
set AutoSimOptions {}
set ExportMCPathFlag 0
set SCTraceFileName mytrace
set SCTraceFileFormat vcd
set SCTraceOption all
set TargetInfo xczu3eg:-sbva484:-1-i
set SourceFiles {sc {} c {../hamming_original.cpp ../FFT_top.cpp}}
set SourceFlags {sc {} c {{} {}}}
set DirectiveFile /home/anders/master/HLS/solution1/solution1.directive
set TBFiles {verilog {../wav_data.dat ../../../speech_commands_v0.01/golden_mel.dat ../fft_tb.cpp} bc {../wav_data.dat ../../../speech_commands_v0.01/golden_mel.dat ../fft_tb.cpp} vhdl {../wav_data.dat ../../../speech_commands_v0.01/golden_mel.dat ../fft_tb.cpp} sc {../wav_data.dat ../../../speech_commands_v0.01/golden_mel.dat ../fft_tb.cpp} cas {../wav_data.dat ../../../speech_commands_v0.01/golden_mel.dat ../fft_tb.cpp} c {}}
set SpecLanguage C
set TVInFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TVOutFiles {bc {} c {} sc {} cas {} vhdl {} verilog {}}
set TBTops {verilog {} bc {} vhdl {} sc {} cas {} c {}}
set TBInstNames {verilog {} bc {} vhdl {} sc {} cas {} c {}}
set XDCFiles {}
set ExtraGlobalOptions {"area_timing" 1 "clock_gate" 1 "impl_flow" map "power_gate" 0}
set TBTVFileNotFound {}
set AppFile ../vivado_hls.app
set ApsFile solution1.aps
set AvePath ../..
set DefaultPlatform DefaultPlatform
set multiClockList {}
set SCPortClockMap {}
set intNbAccess 0
set PlatformFiles {{DefaultPlatform {xilinx/zynquplus/zynquplus xilinx/zynquplus/zynquplus_fpv7}}}
set HPFPO 0
