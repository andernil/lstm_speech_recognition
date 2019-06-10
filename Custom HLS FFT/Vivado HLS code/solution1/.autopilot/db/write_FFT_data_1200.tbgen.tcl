set moduleName write_FFT_data_1200
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 0
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {write_FFT_data.1200}
set C_modelType { void 0 }
set C_modelArgList {
	{ fft_config_data_V int 24 regular {fifo 2}  }
	{ to_FFT_2 int 64 regular {fifo 1 volatile }  }
	{ to_FFT int 64 regular {fifo 0 volatile } {global 0}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "fft_config_data_V", "interface" : "fifo", "bitwidth" : 24, "direction" : "READWRITE"} , 
 	{ "Name" : "to_FFT_2", "interface" : "fifo", "bitwidth" : 64, "direction" : "WRITEONLY"} , 
 	{ "Name" : "to_FFT", "interface" : "fifo", "bitwidth" : 64, "direction" : "READONLY", "extern" : 0} ]}
# RTL Port declarations: 
set portNum 22
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ start_full_n sc_in sc_logic 1 signal -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ start_out sc_out sc_logic 1 signal -1 } 
	{ start_write sc_out sc_logic 1 signal -1 } 
	{ fft_config_data_V_dout sc_in sc_lv 24 signal 0 } 
	{ fft_config_data_V_empty_n sc_in sc_logic 1 signal 0 } 
	{ fft_config_data_V_read sc_out sc_logic 1 signal 0 } 
	{ fft_config_data_V_din sc_out sc_lv 24 signal 0 } 
	{ fft_config_data_V_full_n sc_in sc_logic 1 signal 0 } 
	{ fft_config_data_V_write sc_out sc_logic 1 signal 0 } 
	{ to_FFT_2_din sc_out sc_lv 64 signal 1 } 
	{ to_FFT_2_full_n sc_in sc_logic 1 signal 1 } 
	{ to_FFT_2_write sc_out sc_logic 1 signal 1 } 
	{ to_FFT_dout sc_in sc_lv 64 signal 2 } 
	{ to_FFT_empty_n sc_in sc_logic 1 signal 2 } 
	{ to_FFT_read sc_out sc_logic 1 signal 2 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "start_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_full_n", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "start_out", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_out", "role": "default" }} , 
 	{ "name": "start_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "start_write", "role": "default" }} , 
 	{ "name": "fft_config_data_V_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":24, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "dout" }} , 
 	{ "name": "fft_config_data_V_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "empty_n" }} , 
 	{ "name": "fft_config_data_V_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "read" }} , 
 	{ "name": "fft_config_data_V_din", "direction": "out", "datatype": "sc_lv", "bitwidth":24, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "din" }} , 
 	{ "name": "fft_config_data_V_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "full_n" }} , 
 	{ "name": "fft_config_data_V_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "fft_config_data_V", "role": "write" }} , 
 	{ "name": "to_FFT_2_din", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "to_FFT_2", "role": "din" }} , 
 	{ "name": "to_FFT_2_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT_2", "role": "full_n" }} , 
 	{ "name": "to_FFT_2_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT_2", "role": "write" }} , 
 	{ "name": "to_FFT_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "to_FFT", "role": "dout" }} , 
 	{ "name": "to_FFT_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT", "role": "empty_n" }} , 
 	{ "name": "to_FFT_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT", "role": "read" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "",
		"CDFG" : "write_FFT_data_1200",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "1025", "EstimateLatencyMax" : "1025",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "fft_config_data_V", "Type" : "Fifo", "Direction" : "IO", "DependentProc" : "0", "DependentChan" : "0",
				"BlockSignal" : [
					{"Name" : "fft_config_data_V_i_blk_n", "Type" : "RtlSignal"},
					{"Name" : "fft_config_data_V_o_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT_2", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "0", "DependentChan" : "0",
				"BlockSignal" : [
					{"Name" : "to_FFT_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "to_FFT_blk_n", "Type" : "RtlSignal"}]}]}]}


set ArgLastReadFirstWriteLatency {
	write_FFT_data_1200 {
		fft_config_data_V {Type IO LastRead 0 FirstWrite 0}
		to_FFT_2 {Type O LastRead -1 FirstWrite 1}
		to_FFT {Type I LastRead 1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "1025", "Max" : "1025"}
	, {"Name" : "Interval", "Min" : "1025", "Max" : "1025"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	fft_config_data_V { ap_fifo {  { fft_config_data_V_dout fifo_data 0 24 }  { fft_config_data_V_empty_n fifo_status 0 1 }  { fft_config_data_V_read fifo_update 1 1 }  { fft_config_data_V_din fifo_data 1 24 }  { fft_config_data_V_full_n fifo_status 0 1 }  { fft_config_data_V_write fifo_update 1 1 } } }
	to_FFT_2 { ap_fifo {  { to_FFT_2_din fifo_data 1 64 }  { to_FFT_2_full_n fifo_status 0 1 }  { to_FFT_2_write fifo_update 1 1 } } }
	to_FFT { ap_fifo {  { to_FFT_dout fifo_data 0 64 }  { to_FFT_empty_n fifo_status 0 1 }  { to_FFT_read fifo_update 1 1 } } }
}
