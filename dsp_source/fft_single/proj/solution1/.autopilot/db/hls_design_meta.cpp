#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("direction", 1, hls_in, 0, "ap_hs", "in_data", 1),
	Port_Property("in_r_dout", 32, hls_in, 1, "ap_fifo", "fifo_data", 1),
	Port_Property("in_r_empty_n", 1, hls_in, 1, "ap_fifo", "fifo_status", 1),
	Port_Property("in_r_read", 1, hls_out, 1, "ap_fifo", "fifo_update", 1),
	Port_Property("out_r_din", 32, hls_out, 2, "ap_fifo", "fifo_data", 1),
	Port_Property("out_r_full_n", 1, hls_in, 2, "ap_fifo", "fifo_status", 1),
	Port_Property("out_r_write", 1, hls_out, 2, "ap_fifo", "fifo_update", 1),
	Port_Property("ovflo_din", 1, hls_out, 3, "ap_fifo", "fifo_data", 1),
	Port_Property("ovflo_full_n", 1, hls_in, 3, "ap_fifo", "fifo_status", 1),
	Port_Property("ovflo_write", 1, hls_out, 3, "ap_fifo", "fifo_update", 1),
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst", 1, hls_in, -1, "", "", 1),
	Port_Property("direction_ap_vld", 1, hls_in, 0, "ap_hs", "in_vld", 1),
	Port_Property("direction_ap_ack", 1, hls_out, 0, "ap_hs", "in_acc", 1),
	Port_Property("ap_start", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_done", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_ready", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_idle", 1, hls_out, -1, "", "", 1),
};
const char* HLS_Design_Meta::dut_name = "fft_top";
