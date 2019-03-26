
set TopModule "fft_top"
set ClockPeriod 3.3
set ClockList ap_clk
set HasVivadoClockPeriod 0
set CombLogicFlag 0
set PipelineFlag 1
set DataflowTaskPipelineFlag 1
set TrivialPipelineFlag 0
set noPortSwitchingFlag 0
set FloatingPointFlag 0
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
set TargetInfo xazu2eg:-sbva484:-1-i
set SourceFiles {sc {} c ../../fft_top.cpp}
set SourceFlags {sc {} c {{}}}
set DirectiveFile /home/anders/master/Vivado_HLS/fft_single/proj/solution1/solution1.directive
set TBFiles {verilog {../../fft_tb.cpp ../../data/stimulus_00.dat ../../data/stimulus_01.dat ../../data/stimulus_02.dat ../../data/stimulus_03.dat ../../data/stimulus_04.dat ../../data/stimulus_05.dat ../../data/stimulus_06.dat ../../data/stimulus_07.dat ../../data/stimulus_08.dat ../../data/stimulus_09.dat ../../data/stimulus_10.dat ../../data/stimulus_11.dat ../../data/stimulus_12.dat ../../data/stimulus_13.dat ../../data/stimulus_14.dat ../../data/stimulus_15.dat ../../data/stimulus_16.dat ../../data/stimulus_17.dat ../../data/stimulus_18.dat ../../data/stimulus_19.dat ../../data/stimulus_00.res ../../data/stimulus_01.res ../../data/stimulus_02.res ../../data/stimulus_03.res ../../data/stimulus_04.res ../../data/stimulus_05.res ../../data/stimulus_06.res ../../data/stimulus_07.res ../../data/stimulus_08.res ../../data/stimulus_09.res ../../data/stimulus_10.res ../../data/stimulus_11.res ../../data/stimulus_12.res ../../data/stimulus_13.res ../../data/stimulus_14.res ../../data/stimulus_15.res ../../data/stimulus_16.res ../../data/stimulus_17.res ../../data/stimulus_18.res ../../data/stimulus_19.res} bc {../../fft_tb.cpp ../../data/stimulus_00.dat ../../data/stimulus_01.dat ../../data/stimulus_02.dat ../../data/stimulus_03.dat ../../data/stimulus_04.dat ../../data/stimulus_05.dat ../../data/stimulus_06.dat ../../data/stimulus_07.dat ../../data/stimulus_08.dat ../../data/stimulus_09.dat ../../data/stimulus_10.dat ../../data/stimulus_11.dat ../../data/stimulus_12.dat ../../data/stimulus_13.dat ../../data/stimulus_14.dat ../../data/stimulus_15.dat ../../data/stimulus_16.dat ../../data/stimulus_17.dat ../../data/stimulus_18.dat ../../data/stimulus_19.dat ../../data/stimulus_00.res ../../data/stimulus_01.res ../../data/stimulus_02.res ../../data/stimulus_03.res ../../data/stimulus_04.res ../../data/stimulus_05.res ../../data/stimulus_06.res ../../data/stimulus_07.res ../../data/stimulus_08.res ../../data/stimulus_09.res ../../data/stimulus_10.res ../../data/stimulus_11.res ../../data/stimulus_12.res ../../data/stimulus_13.res ../../data/stimulus_14.res ../../data/stimulus_15.res ../../data/stimulus_16.res ../../data/stimulus_17.res ../../data/stimulus_18.res ../../data/stimulus_19.res} vhdl {../../fft_tb.cpp ../../data/stimulus_00.dat ../../data/stimulus_01.dat ../../data/stimulus_02.dat ../../data/stimulus_03.dat ../../data/stimulus_04.dat ../../data/stimulus_05.dat ../../data/stimulus_06.dat ../../data/stimulus_07.dat ../../data/stimulus_08.dat ../../data/stimulus_09.dat ../../data/stimulus_10.dat ../../data/stimulus_11.dat ../../data/stimulus_12.dat ../../data/stimulus_13.dat ../../data/stimulus_14.dat ../../data/stimulus_15.dat ../../data/stimulus_16.dat ../../data/stimulus_17.dat ../../data/stimulus_18.dat ../../data/stimulus_19.dat ../../data/stimulus_00.res ../../data/stimulus_01.res ../../data/stimulus_02.res ../../data/stimulus_03.res ../../data/stimulus_04.res ../../data/stimulus_05.res ../../data/stimulus_06.res ../../data/stimulus_07.res ../../data/stimulus_08.res ../../data/stimulus_09.res ../../data/stimulus_10.res ../../data/stimulus_11.res ../../data/stimulus_12.res ../../data/stimulus_13.res ../../data/stimulus_14.res ../../data/stimulus_15.res ../../data/stimulus_16.res ../../data/stimulus_17.res ../../data/stimulus_18.res ../../data/stimulus_19.res} sc {../../fft_tb.cpp ../../data/stimulus_00.dat ../../data/stimulus_01.dat ../../data/stimulus_02.dat ../../data/stimulus_03.dat ../../data/stimulus_04.dat ../../data/stimulus_05.dat ../../data/stimulus_06.dat ../../data/stimulus_07.dat ../../data/stimulus_08.dat ../../data/stimulus_09.dat ../../data/stimulus_10.dat ../../data/stimulus_11.dat ../../data/stimulus_12.dat ../../data/stimulus_13.dat ../../data/stimulus_14.dat ../../data/stimulus_15.dat ../../data/stimulus_16.dat ../../data/stimulus_17.dat ../../data/stimulus_18.dat ../../data/stimulus_19.dat ../../data/stimulus_00.res ../../data/stimulus_01.res ../../data/stimulus_02.res ../../data/stimulus_03.res ../../data/stimulus_04.res ../../data/stimulus_05.res ../../data/stimulus_06.res ../../data/stimulus_07.res ../../data/stimulus_08.res ../../data/stimulus_09.res ../../data/stimulus_10.res ../../data/stimulus_11.res ../../data/stimulus_12.res ../../data/stimulus_13.res ../../data/stimulus_14.res ../../data/stimulus_15.res ../../data/stimulus_16.res ../../data/stimulus_17.res ../../data/stimulus_18.res ../../data/stimulus_19.res} cas {../../fft_tb.cpp ../../data/stimulus_00.dat ../../data/stimulus_01.dat ../../data/stimulus_02.dat ../../data/stimulus_03.dat ../../data/stimulus_04.dat ../../data/stimulus_05.dat ../../data/stimulus_06.dat ../../data/stimulus_07.dat ../../data/stimulus_08.dat ../../data/stimulus_09.dat ../../data/stimulus_10.dat ../../data/stimulus_11.dat ../../data/stimulus_12.dat ../../data/stimulus_13.dat ../../data/stimulus_14.dat ../../data/stimulus_15.dat ../../data/stimulus_16.dat ../../data/stimulus_17.dat ../../data/stimulus_18.dat ../../data/stimulus_19.dat ../../data/stimulus_00.res ../../data/stimulus_01.res ../../data/stimulus_02.res ../../data/stimulus_03.res ../../data/stimulus_04.res ../../data/stimulus_05.res ../../data/stimulus_06.res ../../data/stimulus_07.res ../../data/stimulus_08.res ../../data/stimulus_09.res ../../data/stimulus_10.res ../../data/stimulus_11.res ../../data/stimulus_12.res ../../data/stimulus_13.res ../../data/stimulus_14.res ../../data/stimulus_15.res ../../data/stimulus_16.res ../../data/stimulus_17.res ../../data/stimulus_18.res ../../data/stimulus_19.res} c {}}
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
set PlatformFiles {{DefaultPlatform {xilinx/azynquplus/azynquplus xilinx/azynquplus/azynquplus_fpv7}}}
set HPFPO 0
