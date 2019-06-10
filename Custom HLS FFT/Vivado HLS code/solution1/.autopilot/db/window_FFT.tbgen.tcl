set moduleName window_FFT
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
set C_modelName {window_FFT}
set C_modelType { void 0 }
set C_modelArgList {
	{ input_data_M_real double 64 regular {array 16000 { 1 3 } 1 1 }  }
	{ input_data_M_imag double 64 unused {array 16000 { } 0 1 }  }
	{ output_data double 64 regular {array 60416 { 0 3 } 0 1 }  }
	{ peak_value int 32 regular  }
}
set C_modelArgMapList {[ 
	{ "Name" : "input_data_M_real", "interface" : "memory", "bitwidth" : 64, "direction" : "READONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "input_data._M_real","cData": "complex","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 15999,"step" : 1}]}]}]} , 
 	{ "Name" : "input_data_M_imag", "interface" : "memory", "bitwidth" : 64, "direction" : "NONE", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "input_data._M_imag","cData": "complex","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 15999,"step" : 1}]}]}]} , 
 	{ "Name" : "output_data", "interface" : "memory", "bitwidth" : 64, "direction" : "WRITEONLY", "bitSlice":[{"low":0,"up":63,"cElement": [{"cName": "output_data","cData": "double","bit_use": { "low": 0,"up": 63},"cArray": [{"low" : 0,"up" : 60415,"step" : 1}]}]}]} , 
 	{ "Name" : "peak_value", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY", "bitSlice":[{"low":0,"up":31,"cElement": [{"cName": "peak_value","cData": "int","bit_use": { "low": 0,"up": 31},"cArray": [{"low" : 0,"up" : 0,"step" : 0}]}]}]} ]}
# RTL Port declarations: 
set portNum 24
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ input_data_M_real_address0 sc_out sc_lv 14 signal 0 } 
	{ input_data_M_real_ce0 sc_out sc_logic 1 signal 0 } 
	{ input_data_M_real_q0 sc_in sc_lv 64 signal 0 } 
	{ input_data_M_imag_address0 sc_out sc_lv 14 signal 1 } 
	{ input_data_M_imag_ce0 sc_out sc_logic 1 signal 1 } 
	{ input_data_M_imag_we0 sc_out sc_logic 1 signal 1 } 
	{ input_data_M_imag_d0 sc_out sc_lv 64 signal 1 } 
	{ input_data_M_imag_q0 sc_in sc_lv 64 signal 1 } 
	{ input_data_M_imag_address1 sc_out sc_lv 14 signal 1 } 
	{ input_data_M_imag_ce1 sc_out sc_logic 1 signal 1 } 
	{ input_data_M_imag_we1 sc_out sc_logic 1 signal 1 } 
	{ input_data_M_imag_d1 sc_out sc_lv 64 signal 1 } 
	{ input_data_M_imag_q1 sc_in sc_lv 64 signal 1 } 
	{ output_data_address0 sc_out sc_lv 16 signal 2 } 
	{ output_data_ce0 sc_out sc_logic 1 signal 2 } 
	{ output_data_we0 sc_out sc_logic 1 signal 2 } 
	{ output_data_d0 sc_out sc_lv 64 signal 2 } 
	{ peak_value sc_in sc_lv 32 signal 3 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "input_data_M_real_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":14, "type": "signal", "bundle":{"name": "input_data_M_real", "role": "address0" }} , 
 	{ "name": "input_data_M_real_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_M_real", "role": "ce0" }} , 
 	{ "name": "input_data_M_real_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_M_real", "role": "q0" }} , 
 	{ "name": "input_data_M_imag_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":14, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "address0" }} , 
 	{ "name": "input_data_M_imag_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "ce0" }} , 
 	{ "name": "input_data_M_imag_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "we0" }} , 
 	{ "name": "input_data_M_imag_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "d0" }} , 
 	{ "name": "input_data_M_imag_q0", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "q0" }} , 
 	{ "name": "input_data_M_imag_address1", "direction": "out", "datatype": "sc_lv", "bitwidth":14, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "address1" }} , 
 	{ "name": "input_data_M_imag_ce1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "ce1" }} , 
 	{ "name": "input_data_M_imag_we1", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "we1" }} , 
 	{ "name": "input_data_M_imag_d1", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "d1" }} , 
 	{ "name": "input_data_M_imag_q1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_data_M_imag", "role": "q1" }} , 
 	{ "name": "output_data_address0", "direction": "out", "datatype": "sc_lv", "bitwidth":16, "type": "signal", "bundle":{"name": "output_data", "role": "address0" }} , 
 	{ "name": "output_data_ce0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_data", "role": "ce0" }} , 
 	{ "name": "output_data_we0", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_data", "role": "we0" }} , 
 	{ "name": "output_data_d0", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "output_data", "role": "d0" }} , 
 	{ "name": "peak_value", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "peak_value", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "18", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30"],
		"CDFG" : "window_FFT",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "2529653", "EstimateLatencyMax" : "2537845",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "1",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"WaitState" : [
			{"State" : "ap_ST_fsm_state89", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_FFT_fu_568"},
			{"State" : "ap_ST_fsm_state44", "FSM" : "ap_CS_fsm", "SubInstance" : "grp_scaled_fixed2ieee_fu_576"}],
		"Port" : [
			{"Name" : "input_data_M_real", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "input_data_M_imag", "Type" : "Memory", "Direction" : "X"},
			{"Name" : "output_data", "Type" : "Memory", "Direction" : "O"},
			{"Name" : "peak_value", "Type" : "None", "Direction" : "I"},
			{"Name" : "ref_4oPi_table_256_V", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_4", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_5", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_6", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_7", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "fourth_order_double_s", "Type" : "Memory", "Direction" : "I"},
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "9", "SubInstance" : "grp_FFT_fu_568", "Port" : "to_FFT"}]},
			{"Name" : "from_FFT", "Type" : "Fifo", "Direction" : "IO",
				"SubConnect" : [
					{"ID" : "9", "SubInstance" : "grp_FFT_fu_568", "Port" : "from_FFT"}]}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.ref_4oPi_table_256_V_U", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fourth_order_double_4_U", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fourth_order_double_5_U", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fourth_order_double_6_U", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fourth_order_double_7_U", "Parent" : "0"},
	{"ID" : "6", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fourth_order_double_s_U", "Parent" : "0"},
	{"ID" : "7", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.data_frame_U", "Parent" : "0"},
	{"ID" : "8", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.hamming_window_U", "Parent" : "0"},
	{"ID" : "9", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568", "Parent" : "0", "Child" : ["10", "11", "12", "13", "14", "15", "16", "17"],
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
			{"ID" : "10", "Name" : "write_FFT_data_1200_U0"}],
		"OutputProcess" : [
			{"ID" : "12", "Name" : "read_FFT_data_1201_U0"}],
		"Port" : [
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "I",
				"SubConnect" : [
					{"ID" : "10", "SubInstance" : "write_FFT_data_1200_U0", "Port" : "to_FFT"}]},
			{"Name" : "from_FFT", "Type" : "Fifo", "Direction" : "O",
				"SubConnect" : [
					{"ID" : "12", "SubInstance" : "read_FFT_data_1201_U0", "Port" : "from_FFT"}]}]},
	{"ID" : "10", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.write_FFT_data_1200_U0", "Parent" : "9",
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
			{"Name" : "fft_config_data_V", "Type" : "Fifo", "Direction" : "IO", "DependentProc" : "11", "DependentChan" : "13",
				"BlockSignal" : [
					{"Name" : "fft_config_data_V_i_blk_n", "Type" : "RtlSignal"},
					{"Name" : "fft_config_data_V_o_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT_2", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "11", "DependentChan" : "14",
				"BlockSignal" : [
					{"Name" : "to_FFT_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "to_FFT", "Type" : "Fifo", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "to_FFT_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "11", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.fft_FFT_params_U0", "Parent" : "9",
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
		"StartSource" : "10",
		"StartFifo" : "start_for_fft_FFT_params_U0_U",
		"Port" : [
			{"Name" : "xn", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "10", "DependentChan" : "14"},
			{"Name" : "xk", "Type" : "Fifo", "Direction" : "O", "DependentProc" : "12", "DependentChan" : "15"},
			{"Name" : "status_data_V", "Type" : "Fifo", "Direction" : "O"},
			{"Name" : "config_ch_data_V", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "10", "DependentChan" : "13"}]},
	{"ID" : "12", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.read_FFT_data_1201_U0", "Parent" : "9",
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
		"StartSource" : "10",
		"StartFifo" : "start_for_read_FFT_data_1201_U0_U",
		"Port" : [
			{"Name" : "from_FFT_2", "Type" : "Fifo", "Direction" : "I", "DependentProc" : "11", "DependentChan" : "15",
				"BlockSignal" : [
					{"Name" : "from_FFT_2_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "from_FFT", "Type" : "Fifo", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "from_FFT_blk_n", "Type" : "RtlSignal"}]}]},
	{"ID" : "13", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.FFT_config_data_V_U", "Parent" : "9"},
	{"ID" : "14", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.x_in_channel_U", "Parent" : "9"},
	{"ID" : "15", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.x_out_channel_U", "Parent" : "9"},
	{"ID" : "16", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.start_for_fft_FFT_params_U0_U", "Parent" : "9"},
	{"ID" : "17", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_FFT_fu_568.start_for_read_FFT_data_1201_U0_U", "Parent" : "9"},
	{"ID" : "18", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.grp_scaled_fixed2ieee_fu_576", "Parent" : "0", "Child" : ["19", "20"],
		"CDFG" : "scaled_fixed2ieee",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "19", "EstimateLatencyMax" : "27",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"Port" : [
			{"Name" : "in_V", "Type" : "None", "Direction" : "I"},
			{"Name" : "prescale", "Type" : "None", "Direction" : "I"}]},
	{"ID" : "19", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_scaled_fixed2ieee_fu_576.out_bits_V_U", "Parent" : "18"},
	{"ID" : "20", "Level" : "2", "Path" : "`AUTOTB_DUT_INST.grp_scaled_fixed2ieee_fu_576.c_U", "Parent" : "18"},
	{"ID" : "21", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_dsub_64ns_64ns_64_5_full_dsp_1_U18", "Parent" : "0"},
	{"ID" : "22", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_dmul_64ns_64ns_64_5_max_dsp_1_U19", "Parent" : "0"},
	{"ID" : "23", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_ddiv_64ns_64ns_64_22_1_U20", "Parent" : "0"},
	{"ID" : "24", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_sitodp_32ns_64_4_1_U21", "Parent" : "0"},
	{"ID" : "25", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_mul_170ns_53ns_223_2_1_U22", "Parent" : "0"},
	{"ID" : "26", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_mux_83_1_1_1_U23", "Parent" : "0"},
	{"ID" : "27", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_mux_164_1_1_1_U24", "Parent" : "0"},
	{"ID" : "28", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.window_FFT_mux_164_1_1_1_U25", "Parent" : "0"},
	{"ID" : "29", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.from_FFT_fifo_U", "Parent" : "0"},
	{"ID" : "30", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.to_FFT_fifo_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	window_FFT {
		input_data_M_real {Type I LastRead 6 FirstWrite -1}
		input_data_M_imag {Type X LastRead -1 FirstWrite -1}
		output_data {Type O LastRead -1 FirstWrite 12}
		peak_value {Type I LastRead 0 FirstWrite -1}
		ref_4oPi_table_256_V {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_4 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_5 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_6 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_7 {Type I LastRead -1 FirstWrite -1}
		fourth_order_double_s {Type I LastRead -1 FirstWrite -1}
		to_FFT {Type IO LastRead -1 FirstWrite -1}
		from_FFT {Type IO LastRead -1 FirstWrite -1}}
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
		from_FFT {Type O LastRead -1 FirstWrite 1}}
	scaled_fixed2ieee {
		in_V {Type I LastRead 0 FirstWrite -1}
		prescale {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 1

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "2529653", "Max" : "2537845"}
	, {"Name" : "Interval", "Min" : "2529654", "Max" : "2537846"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	input_data_M_real { ap_memory {  { input_data_M_real_address0 mem_address 1 14 }  { input_data_M_real_ce0 mem_ce 1 1 }  { input_data_M_real_q0 mem_dout 0 64 } } }
	input_data_M_imag { ap_memory {  { input_data_M_imag_address0 mem_address 1 14 }  { input_data_M_imag_ce0 mem_ce 1 1 }  { input_data_M_imag_we0 mem_we 1 1 }  { input_data_M_imag_d0 mem_din 1 64 }  { input_data_M_imag_q0 mem_dout 0 64 }  { input_data_M_imag_address1 MemPortADDR2 1 14 }  { input_data_M_imag_ce1 MemPortCE2 1 1 }  { input_data_M_imag_we1 MemPortWE2 1 1 }  { input_data_M_imag_d1 MemPortDIN2 1 64 }  { input_data_M_imag_q1 MemPortDOUT2 0 64 } } }
	output_data { ap_memory {  { output_data_address0 mem_address 1 16 }  { output_data_ce0 mem_ce 1 1 }  { output_data_we0 mem_we 1 1 }  { output_data_d0 mem_din 1 64 } } }
	peak_value { ap_none {  { peak_value in_data 0 32 } } }
}

set busDeadlockParameterList { 
}

# RTL port scheduling information:
set fifoSchedulingInfoList { 
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
