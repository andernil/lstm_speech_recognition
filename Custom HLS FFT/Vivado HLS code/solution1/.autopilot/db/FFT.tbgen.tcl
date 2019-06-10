set moduleName FFT
set isTaskLevelControl 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type dataflow
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set C_modelName {FFT}
set C_modelType { void 0 }
set C_modelArgList {
	{ to_FFT int 64 regular {fifo 0 volatile } {global 0}  }
	{ from_FFT int 64 regular {fifo 1 volatile } {global 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "to_FFT", "interface" : "fifo", "bitwidth" : 64, "direction" : "READONLY", "extern" : 0} , 
 	{ "Name" : "from_FFT", "interface" : "fifo", "bitwidth" : 64, "direction" : "WRITEONLY", "extern" : 0} ]}
# RTL Port declarations: 
set portNum 13
set portList { 
	{ to_FFT_dout sc_in sc_lv 64 signal 0 } 
	{ to_FFT_empty_n sc_in sc_logic 1 signal 0 } 
	{ to_FFT_read sc_out sc_logic 1 signal 0 } 
	{ from_FFT_din sc_out sc_lv 64 signal 1 } 
	{ from_FFT_full_n sc_in sc_logic 1 signal 1 } 
	{ from_FFT_write sc_out sc_logic 1 signal 1 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_continue sc_in sc_logic 1 continue -1 } 
}
set NewPortList {[ 
	{ "name": "to_FFT_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "to_FFT", "role": "dout" }} , 
 	{ "name": "to_FFT_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT", "role": "empty_n" }} , 
 	{ "name": "to_FFT_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "to_FFT", "role": "read" }} , 
 	{ "name": "from_FFT_din", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "from_FFT", "role": "din" }} , 
 	{ "name": "from_FFT_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "from_FFT", "role": "full_n" }} , 
 	{ "name": "from_FFT_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "from_FFT", "role": "write" }} , 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_continue", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "continue", "bundle":{"name": "ap_continue", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8"],
		"CDFG" : "FFT",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "7331", "EstimateLatencyMax" : "7331",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"InputProcess" : [
			{"ID" : "1", "Name" : "write_FFT_data_1200_U0"}],
		"OutputProcess" : [
			{"ID" : "3", "Name" : "read_FFT_data_1201_U0"}],
		"Port" : [
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "write_FFT_data_1200_U0", "Port" : "to_FFT"}]},
			{"Name" : "from_FFT", "Type" : "Fifo", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "read_FFT_data_1201_U0", "Port" : "from_FFT"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.write_FFT_data_1200_U0", "Parent" : "0",
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
			{"Name" : "fft_config_data_V", "Type" : "Fifo", "Direction" : "IO", "DependentProc" : "2", "DependentChan" : "4",
				"BlockSignal" : [
					{"Name" : "fft_config_data_V_i_blk_n", "Type" : "RtlSignal"},
					{"Name" : "fft_config_data_V_o_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT_2", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "5",
				"BlockSignal" : [
					{"Name" : "to_FFT_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "to_FFT_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fft_FFT_params_U0", "Parent" : "0",
		"CDFG" : "fft_FFT_params_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "7331", "EstimateLatencyMax" : "7331",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"StartSource" : "1",
		"StartFifo" : "start_for_fft_FFT_params_U0_U",
		"Port" : [
			{"Name" : "xn", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "5"},
			{"Name" : "xk", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "6"},
			{"Name" : "status_data_V", "Type" : "Fifo", "Direction" : "O"},
			{"Name" : "config_ch_data_V", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "4"}]},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.read_FFT_data_1201_U0", "Parent" : "0",
		"CDFG" : "read_FFT_data_1201",
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
		"StartSource" : "1",
		"StartFifo" : "start_for_read_FFT_data_1201_U0_U",
		"Port" : [
			{"Name" : "from_FFT_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "6",
				"BlockSignal" : [
					{"Name" : "from_FFT_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "from_FFT", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "from_FFT_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.FFT_config_data_V_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.x_in_channel_U", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.x_out_channel_U", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_fft_FFT_params_U0_U", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_read_FFT_data_1201_U0_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	FFT {
		to_FFT {Type I LastRead 1 FirstWrite -1}
		from_FFT {Type O LastRead -1 FirstWrite 1}}
	write_FFT_data_1200 {
		fft_config_data_V {Type IO LastRead 0 FirstWrite 0}
		to_FFT_2 {Type O LastRead -1 FirstWrite 1}
		to_FFT {Type I LastRead 1 FirstWrite -1}}
	fft_FFT_params_s {
		xn {Type I LastRead -1 FirstWrite -1}
		xk {Type O LastRead -1 FirstWrite -1}
		status_data_V {Type O LastRead -1 FirstWrite -1}
		config_ch_data_V {Type I LastRead -1 FirstWrite -1}}
	read_FFT_data_1201 {
		from_FFT_2 {Type I LastRead 1 FirstWrite -1}
		from_FFT {Type O LastRead -1 FirstWrite 1}}}

set hasDtUnsupportedChannel 1

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "7331", "Max" : "7331"}
	, {"Name" : "Interval", "Min" : "7332", "Max" : "7332"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	to_FFT { ap_fifo {  { to_FFT_dout fifo_data 0 64 }  { to_FFT_empty_n fifo_status 0 1 }  { to_FFT_read fifo_update 1 1 } } }
	from_FFT { ap_fifo {  { from_FFT_din fifo_data 1 64 }  { from_FFT_full_n fifo_status 0 1 }  { from_FFT_write fifo_update 1 1 } } }
}
