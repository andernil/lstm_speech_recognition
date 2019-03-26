set moduleName fft_top
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
set C_modelName {fft_top}
set C_modelType { void 0 }
set C_modelArgList {
	{ direction uint 1 regular  }
	{ in_r int 32 regular {fifo 0 volatile }  }
	{ out_r int 32 regular {fifo 1 volatile }  }
	{ ovflo int 1 regular {fifo 1}  }
}
set C_modelArgMapList {[ 
	{ "Name" : "direction", "interface" : "wire", "bitwidth" : 1, "direction" : "READONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "direction","cData": "bool","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} , 
 	{ "Name" : "in_r", "interface" : "fifo", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":15,"cElement": [{"cName": "in._M_real.V","cData": "int16","bit_use": { "low": 0,"up": 15},"cArray": [{"low" : 0,"up" : 1023,"step" : 1}]}]},{"low":16,"up":31,"cElement": [{"cName": "in._M_imag.V","cData": "int16","bit_use": { "low": 0,"up": 15},"cArray": [{"low" : 0,"up" : 1023,"step" : 1}]}]}]} , 
 	{ "Name" : "out_r", "interface" : "fifo", "bitwidth" : 32, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":15,"cElement": [{"cName": "out._M_real.V","cData": "int16","bit_use": { "low": 0,"up": 15},"cArray": [{"low" : 0,"up" : 1023,"step" : 1}]}]},{"low":16,"up":31,"cElement": [{"cName": "out._M_imag.V","cData": "int16","bit_use": { "low": 0,"up": 15},"cArray": [{"low" : 0,"up" : 1023,"step" : 1}]}]}]} , 
 	{ "Name" : "ovflo", "interface" : "fifo", "bitwidth" : 1, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":0,"cElement": [{"cName": "ovflo","cData": "bool","bit_use": { "low": 0,"up": 0},"cArray": [{"low" : 0,"up" : 0,"step" : 1}]}]}]} ]}
# RTL Port declarations: 
set portNum 18
set portList { 
	{ direction sc_in sc_logic 1 signal 0 } 
	{ in_r_dout sc_in sc_lv 32 signal 1 } 
	{ in_r_empty_n sc_in sc_logic 1 signal 1 } 
	{ in_r_read sc_out sc_logic 1 signal 1 } 
	{ out_r_din sc_out sc_lv 32 signal 2 } 
	{ out_r_full_n sc_in sc_logic 1 signal 2 } 
	{ out_r_write sc_out sc_logic 1 signal 2 } 
	{ ovflo_din sc_out sc_logic 1 signal 3 } 
	{ ovflo_full_n sc_in sc_logic 1 signal 3 } 
	{ ovflo_write sc_out sc_logic 1 signal 3 } 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ direction_ap_vld sc_in sc_logic 1 invld 0 } 
	{ direction_ap_ack sc_out sc_logic 1 inacc 0 } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
}
set NewPortList {[ 
	{ "name": "direction", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "direction", "role": "default" }} , 
 	{ "name": "in_r_dout", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "in_r", "role": "dout" }} , 
 	{ "name": "in_r_empty_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "empty_n" }} , 
 	{ "name": "in_r_read", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "in_r", "role": "read" }} , 
 	{ "name": "out_r_din", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "out_r", "role": "din" }} , 
 	{ "name": "out_r_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "full_n" }} , 
 	{ "name": "out_r_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "out_r", "role": "write" }} , 
 	{ "name": "ovflo_din", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "ovflo", "role": "din" }} , 
 	{ "name": "ovflo_full_n", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "ovflo", "role": "full_n" }} , 
 	{ "name": "ovflo_write", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "ovflo", "role": "write" }} , 
 	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "direction_ap_vld", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "direction", "role": "ap_vld" }} , 
 	{ "name": "direction_ap_ack", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "direction", "role": "ap_ack" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9"],
		"CDFG" : "fft_top",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "Dataflow", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "1",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "3195", "EstimateLatencyMax" : "3195",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"InputProcess" : [
			{"ID" : "1", "Name" : "dummy_proc_fe_U0"}],
		"OutputProcess" : [
			{"ID" : "3", "Name" : "dummy_proc_be_U0"}],
		"Port" : [
			{"Name" : "direction", "Type" : "HS", "Direction" : "I"},
			{"Name" : "in_r", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "1", "SubInstance" : "dummy_proc_fe_U0", "Port" : "in_r"}]},
			{"Name" : "out_r", "Type" : "Fifo", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "dummy_proc_be_U0", "Port" : "out_r"}]},
			{"Name" : "ovflo", "Type" : "Fifo", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "3", "SubInstance" : "dummy_proc_be_U0", "Port" : "ovflo"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dummy_proc_fe_U0", "Parent" : "0",
		"CDFG" : "dummy_proc_fe",
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
			{"Name" : "direction", "Type" : "HS", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "direction_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "config_data_V", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "4",
				"BlockSignal" : [
					{"Name" : "config_data_V_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "in_r", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "in_r_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "out_r", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "2", "DependentChan" : "5",
				"BlockSignal" : [
					{"Name" : "out_r_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fft_config1_U0", "Parent" : "0",
		"CDFG" : "fft_config1_s",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "1", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "3195", "EstimateLatencyMax" : "3195",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "1",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "1",
		"HasNonBlockingOperation" : "0",
		"StartSource" : "1",
		"StartFifo" : "start_for_fft_config1_U0_U",
		"Port" : [
			{"Name" : "xn", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "5"},
			{"Name" : "xk", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "6"},
			{"Name" : "status_data_V", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "3", "DependentChan" : "7"},
			{"Name" : "config_ch_data_V", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "1", "DependentChan" : "4"}]},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.dummy_proc_be_U0", "Parent" : "0",
		"CDFG" : "dummy_proc_be",
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
		"StartFifo" : "start_for_dummy_proc_be_U0_U",
		"Port" : [
			{"Name" : "status_in_data_V", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "7",
				"BlockSignal" : [
					{"Name" : "status_in_data_V_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "ovflo", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "ovflo_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "in_r", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "2", "DependentChan" : "6",
				"BlockSignal" : [
					{"Name" : "in_r_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "out_r", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "out_r_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fft_config_data_V_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.xn_channel_U", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.xk_channel_U", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fft_status_data_V_U", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_fft_config1_U0_U", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.start_for_dummy_proc_be_U0_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	fft_top {
		direction {Type I LastRead 0 FirstWrite -1}
		in_r {Type I LastRead 1 FirstWrite -1}
		out_r {Type O LastRead -1 FirstWrite 1}
		ovflo {Type O LastRead -1 FirstWrite 1}}
	dummy_proc_fe {
		direction {Type I LastRead 0 FirstWrite -1}
		config_data_V {Type O LastRead -1 FirstWrite 0}
		in_r {Type I LastRead 1 FirstWrite -1}
		out_r {Type O LastRead -1 FirstWrite 1}}
	fft_config1_s {
		xn {Type I LastRead -1 FirstWrite -1}
		xk {Type O LastRead -1 FirstWrite -1}
		status_data_V {Type O LastRead -1 FirstWrite -1}
		config_ch_data_V {Type I LastRead -1 FirstWrite -1}}
	dummy_proc_be {
		status_in_data_V {Type I LastRead 1 FirstWrite -1}
		ovflo {Type O LastRead -1 FirstWrite 1}
		in_r {Type I LastRead 1 FirstWrite -1}
		out_r {Type O LastRead -1 FirstWrite 1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "3195", "Max" : "3195"}
	, {"Name" : "Interval", "Min" : "3196", "Max" : "3196"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	direction { ap_hs {  { direction in_data 0 1 }  { direction_ap_vld in_vld 0 1 }  { direction_ap_ack in_acc 1 1 } } }
	in_r { ap_fifo {  { in_r_dout fifo_data 0 32 }  { in_r_empty_n fifo_status 0 1 }  { in_r_read fifo_update 1 1 } } }
	out_r { ap_fifo {  { out_r_din fifo_data 1 32 }  { out_r_full_n fifo_status 0 1 }  { out_r_write fifo_update 1 1 } } }
	ovflo { ap_fifo {  { ovflo_din fifo_data 1 1 }  { ovflo_full_n fifo_status 0 1 }  { ovflo_write fifo_update 1 1 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
	in_r { fifo_read 1 no_conditional }
	out_r { fifo_write 1 no_conditional }
	ovflo { fifo_write 1 no_conditional }
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
