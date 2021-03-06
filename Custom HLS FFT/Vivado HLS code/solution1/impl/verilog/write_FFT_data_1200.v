// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module write_FFT_data_1200 (
        ap_clk,
        ap_rst,
        ap_start,
        start_full_n,
        ap_done,
        ap_continue,
        ap_idle,
        ap_ready,
        start_out,
        start_write,
        fft_config_data_V_dout,
        fft_config_data_V_empty_n,
        fft_config_data_V_read,
        fft_config_data_V_din,
        fft_config_data_V_full_n,
        fft_config_data_V_write,
        to_FFT_2_din,
        to_FFT_2_full_n,
        to_FFT_2_write,
        to_FFT_dout,
        to_FFT_empty_n,
        to_FFT_read
);

parameter    ap_ST_fsm_state1 = 2'd1;
parameter    ap_ST_fsm_state2 = 2'd2;

input   ap_clk;
input   ap_rst;
input   ap_start;
input   start_full_n;
output   ap_done;
input   ap_continue;
output   ap_idle;
output   ap_ready;
output   start_out;
output   start_write;
input  [23:0] fft_config_data_V_dout;
input   fft_config_data_V_empty_n;
output   fft_config_data_V_read;
output  [23:0] fft_config_data_V_din;
input   fft_config_data_V_full_n;
output   fft_config_data_V_write;
output  [63:0] to_FFT_2_din;
input   to_FFT_2_full_n;
output   to_FFT_2_write;
input  [63:0] to_FFT_dout;
input   to_FFT_empty_n;
output   to_FFT_read;

reg ap_done;
reg ap_idle;
reg start_write;
reg fft_config_data_V_read;
reg fft_config_data_V_write;
reg to_FFT_2_write;
reg to_FFT_read;

reg    real_start;
reg    start_once_reg;
reg    ap_done_reg;
(* fsm_encoding = "none" *) reg   [1:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg    internal_ap_ready;
reg    fft_config_data_V_i_blk_n;
reg    fft_config_data_V_o_blk_n;
reg    to_FFT_2_blk_n;
wire    ap_CS_fsm_state2;
wire   [0:0] exitcond_fu_97_p2;
reg    to_FFT_blk_n;
wire   [10:0] i_1_fu_103_p2;
reg    ap_block_state2;
reg   [10:0] i_reg_73;
reg    ap_block_state1;
reg   [1:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 start_once_reg = 1'b0;
#0 ap_done_reg = 1'b0;
#0 ap_CS_fsm = 2'd1;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        start_once_reg <= 1'b0;
    end else begin
        if (((internal_ap_ready == 1'b0) & (real_start == 1'b1))) begin
            start_once_reg <= 1'b1;
        end else if ((internal_ap_ready == 1'b1)) begin
            start_once_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        i_reg_73 <= i_1_fu_103_p2;
    end else if ((~((real_start == 1'b0) | (fft_config_data_V_full_n == 1'b0) | (fft_config_data_V_empty_n == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        i_reg_73 <= 11'd0;
    end
end

always @ (*) begin
    if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = ap_done_reg;
    end
end

always @ (*) begin
    if (((real_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        fft_config_data_V_i_blk_n = fft_config_data_V_empty_n;
    end else begin
        fft_config_data_V_i_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~((real_start == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        fft_config_data_V_o_blk_n = fft_config_data_V_full_n;
    end else begin
        fft_config_data_V_o_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~((real_start == 1'b0) | (fft_config_data_V_full_n == 1'b0) | (fft_config_data_V_empty_n == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        fft_config_data_V_read = 1'b1;
    end else begin
        fft_config_data_V_read = 1'b0;
    end
end

always @ (*) begin
    if ((~((real_start == 1'b0) | (fft_config_data_V_full_n == 1'b0) | (fft_config_data_V_empty_n == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
        fft_config_data_V_write = 1'b1;
    end else begin
        fft_config_data_V_write = 1'b0;
    end
end

always @ (*) begin
    if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
        internal_ap_ready = 1'b1;
    end else begin
        internal_ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((start_full_n == 1'b0) & (start_once_reg == 1'b0))) begin
        real_start = 1'b0;
    end else begin
        real_start = ap_start;
    end
end

always @ (*) begin
    if (((start_once_reg == 1'b0) & (real_start == 1'b1))) begin
        start_write = 1'b1;
    end else begin
        start_write = 1'b0;
    end
end

always @ (*) begin
    if (((exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        to_FFT_2_blk_n = to_FFT_2_full_n;
    end else begin
        to_FFT_2_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        to_FFT_2_write = 1'b1;
    end else begin
        to_FFT_2_write = 1'b0;
    end
end

always @ (*) begin
    if (((exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        to_FFT_blk_n = to_FFT_empty_n;
    end else begin
        to_FFT_blk_n = 1'b1;
    end
end

always @ (*) begin
    if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
        to_FFT_read = 1'b1;
    end else begin
        to_FFT_read = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if ((~((real_start == 1'b0) | (fft_config_data_V_full_n == 1'b0) | (fft_config_data_V_empty_n == 1'b0) | (ap_done_reg == 1'b1)) & (1'b1 == ap_CS_fsm_state1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else if ((~(((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0))) & (exitcond_fu_97_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

always @ (*) begin
    ap_block_state1 = ((real_start == 1'b0) | (fft_config_data_V_full_n == 1'b0) | (fft_config_data_V_empty_n == 1'b0) | (ap_done_reg == 1'b1));
end

always @ (*) begin
    ap_block_state2 = (((exitcond_fu_97_p2 == 1'd0) & (to_FFT_2_full_n == 1'b0)) | ((exitcond_fu_97_p2 == 1'd0) & (to_FFT_empty_n == 1'b0)));
end

assign ap_ready = internal_ap_ready;

assign exitcond_fu_97_p2 = ((i_reg_73 == 11'd1024) ? 1'b1 : 1'b0);

assign fft_config_data_V_din = {{fft_config_data_V_dout[23:21]}, {21'd699053}};

assign i_1_fu_103_p2 = (i_reg_73 + 11'd1);

assign start_out = real_start;

assign to_FFT_2_din = to_FFT_dout;

endmodule //write_FFT_data_1200
