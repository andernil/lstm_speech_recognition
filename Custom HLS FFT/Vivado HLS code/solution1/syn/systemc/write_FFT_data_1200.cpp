// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "write_FFT_data_1200.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic write_FFT_data_1200::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic write_FFT_data_1200::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<2> write_FFT_data_1200::ap_ST_fsm_state1 = "1";
const sc_lv<2> write_FFT_data_1200::ap_ST_fsm_state2 = "10";
const sc_lv<32> write_FFT_data_1200::ap_const_lv32_0 = "00000000000000000000000000000000";
const sc_lv<32> write_FFT_data_1200::ap_const_lv32_1 = "1";
const sc_lv<1> write_FFT_data_1200::ap_const_lv1_0 = "0";
const sc_lv<11> write_FFT_data_1200::ap_const_lv11_0 = "00000000000";
const sc_lv<21> write_FFT_data_1200::ap_const_lv21_AAAAD = "10101010101010101101";
const sc_lv<32> write_FFT_data_1200::ap_const_lv32_14 = "10100";
const sc_lv<11> write_FFT_data_1200::ap_const_lv11_400 = "10000000000";
const sc_lv<11> write_FFT_data_1200::ap_const_lv11_1 = "1";
const sc_lv<1> write_FFT_data_1200::ap_const_lv1_1 = "1";
const bool write_FFT_data_1200::ap_const_boolean_1 = true;

write_FFT_data_1200::write_FFT_data_1200(sc_module_name name) : sc_module(name), mVcdFile(0) {

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state2);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_block_state1);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( fft_config_data_V_empty_n );
    sensitive << ( fft_config_data_V_full_n );

    SC_METHOD(thread_ap_block_state2);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_ap_done);
    sensitive << ( ap_done_reg );
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_ap_idle);
    sensitive << ( real_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( internal_ap_ready );

    SC_METHOD(thread_exitcond_fu_97_p2);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );
    sensitive << ( i_reg_73 );

    SC_METHOD(thread_fft_config_data_V_din);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_dout );
    sensitive << ( fft_config_data_V_empty_n );
    sensitive << ( fft_config_data_V_full_n );

    SC_METHOD(thread_fft_config_data_V_i_blk_n);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_empty_n );

    SC_METHOD(thread_fft_config_data_V_o_blk_n);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_full_n );

    SC_METHOD(thread_fft_config_data_V_read);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_empty_n );
    sensitive << ( fft_config_data_V_full_n );

    SC_METHOD(thread_fft_config_data_V_write);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_empty_n );
    sensitive << ( fft_config_data_V_full_n );

    SC_METHOD(thread_i_1_fu_103_p2);
    sensitive << ( i_reg_73 );

    SC_METHOD(thread_internal_ap_ready);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_real_start);
    sensitive << ( ap_start );
    sensitive << ( start_full_n );
    sensitive << ( start_once_reg );

    SC_METHOD(thread_start_out);
    sensitive << ( real_start );

    SC_METHOD(thread_start_write);
    sensitive << ( real_start );
    sensitive << ( start_once_reg );

    SC_METHOD(thread_to_FFT_2_blk_n);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_to_FFT_2_din);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_dout );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_to_FFT_2_write);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_to_FFT_blk_n);
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_to_FFT_read);
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( real_start );
    sensitive << ( ap_done_reg );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( fft_config_data_V_empty_n );
    sensitive << ( fft_config_data_V_full_n );
    sensitive << ( to_FFT_2_full_n );
    sensitive << ( to_FFT_empty_n );
    sensitive << ( ap_CS_fsm_state2 );
    sensitive << ( exitcond_fu_97_p2 );

    start_once_reg = SC_LOGIC_0;
    ap_done_reg = SC_LOGIC_0;
    ap_CS_fsm = "01";
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "write_FFT_data_1200_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT_HIER__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst, "(port)ap_rst");
    sc_trace(mVcdFile, ap_start, "(port)ap_start");
    sc_trace(mVcdFile, start_full_n, "(port)start_full_n");
    sc_trace(mVcdFile, ap_done, "(port)ap_done");
    sc_trace(mVcdFile, ap_continue, "(port)ap_continue");
    sc_trace(mVcdFile, ap_idle, "(port)ap_idle");
    sc_trace(mVcdFile, ap_ready, "(port)ap_ready");
    sc_trace(mVcdFile, start_out, "(port)start_out");
    sc_trace(mVcdFile, start_write, "(port)start_write");
    sc_trace(mVcdFile, fft_config_data_V_dout, "(port)fft_config_data_V_dout");
    sc_trace(mVcdFile, fft_config_data_V_empty_n, "(port)fft_config_data_V_empty_n");
    sc_trace(mVcdFile, fft_config_data_V_read, "(port)fft_config_data_V_read");
    sc_trace(mVcdFile, fft_config_data_V_din, "(port)fft_config_data_V_din");
    sc_trace(mVcdFile, fft_config_data_V_full_n, "(port)fft_config_data_V_full_n");
    sc_trace(mVcdFile, fft_config_data_V_write, "(port)fft_config_data_V_write");
    sc_trace(mVcdFile, to_FFT_2_din, "(port)to_FFT_2_din");
    sc_trace(mVcdFile, to_FFT_2_full_n, "(port)to_FFT_2_full_n");
    sc_trace(mVcdFile, to_FFT_2_write, "(port)to_FFT_2_write");
    sc_trace(mVcdFile, to_FFT_dout, "(port)to_FFT_dout");
    sc_trace(mVcdFile, to_FFT_empty_n, "(port)to_FFT_empty_n");
    sc_trace(mVcdFile, to_FFT_read, "(port)to_FFT_read");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, real_start, "real_start");
    sc_trace(mVcdFile, start_once_reg, "start_once_reg");
    sc_trace(mVcdFile, ap_done_reg, "ap_done_reg");
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, internal_ap_ready, "internal_ap_ready");
    sc_trace(mVcdFile, fft_config_data_V_i_blk_n, "fft_config_data_V_i_blk_n");
    sc_trace(mVcdFile, fft_config_data_V_o_blk_n, "fft_config_data_V_o_blk_n");
    sc_trace(mVcdFile, to_FFT_2_blk_n, "to_FFT_2_blk_n");
    sc_trace(mVcdFile, ap_CS_fsm_state2, "ap_CS_fsm_state2");
    sc_trace(mVcdFile, exitcond_fu_97_p2, "exitcond_fu_97_p2");
    sc_trace(mVcdFile, to_FFT_blk_n, "to_FFT_blk_n");
    sc_trace(mVcdFile, i_1_fu_103_p2, "i_1_fu_103_p2");
    sc_trace(mVcdFile, ap_block_state2, "ap_block_state2");
    sc_trace(mVcdFile, i_reg_73, "i_reg_73");
    sc_trace(mVcdFile, ap_block_state1, "ap_block_state1");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
}

write_FFT_data_1200::~write_FFT_data_1200() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

}

void write_FFT_data_1200::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_done_reg = ap_const_logic_0;
    } else {
        if (esl_seteq<1,1,1>(ap_const_logic_1, ap_continue.read())) {
            ap_done_reg = ap_const_logic_0;
        } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
                    !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))) && 
                    esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_1))) {
            ap_done_reg = ap_const_logic_1;
        }
    }
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
         !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))))) {
        i_reg_73 = i_1_fu_103_p2.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_empty_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_full_n.read())))) {
        i_reg_73 = ap_const_lv11_0;
    }
    if ( ap_rst.read() == ap_const_logic_1) {
        start_once_reg = ap_const_logic_0;
    } else {
        if ((esl_seteq<1,1,1>(ap_const_logic_1, real_start.read()) && 
             esl_seteq<1,1,1>(ap_const_logic_0, internal_ap_ready.read()))) {
            start_once_reg = ap_const_logic_1;
        } else if (esl_seteq<1,1,1>(ap_const_logic_1, internal_ap_ready.read())) {
            start_once_reg = ap_const_logic_0;
        }
    }
}

void write_FFT_data_1200::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void write_FFT_data_1200::thread_ap_CS_fsm_state2() {
    ap_CS_fsm_state2 = ap_CS_fsm.read()[1];
}

void write_FFT_data_1200::thread_ap_block_state1() {
    ap_block_state1 = (esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_empty_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_full_n.read()));
}

void write_FFT_data_1200::thread_ap_block_state2() {
    ap_block_state2 = ((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read())));
}

void write_FFT_data_1200::thread_ap_done() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_1))) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_done_reg.read();
    }
}

void write_FFT_data_1200::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_ap_ready() {
    ap_ready = internal_ap_ready.read();
}

void write_FFT_data_1200::thread_exitcond_fu_97_p2() {
    exitcond_fu_97_p2 = (!i_reg_73.read().is_01() || !ap_const_lv11_400.is_01())? sc_lv<1>(): sc_lv<1>(i_reg_73.read() == ap_const_lv11_400);
}

void write_FFT_data_1200::thread_fft_config_data_V_din() {
    fft_config_data_V_din = esl_partset<24,24,21,32,32>(fft_config_data_V_dout.read(), ap_const_lv21_AAAAD, ap_const_lv32_0, ap_const_lv32_14);
}

void write_FFT_data_1200::thread_fft_config_data_V_i_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        fft_config_data_V_i_blk_n = fft_config_data_V_empty_n.read();
    } else {
        fft_config_data_V_i_blk_n = ap_const_logic_1;
    }
}

void write_FFT_data_1200::thread_fft_config_data_V_o_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1)))) {
        fft_config_data_V_o_blk_n = fft_config_data_V_full_n.read();
    } else {
        fft_config_data_V_o_blk_n = ap_const_logic_1;
    }
}

void write_FFT_data_1200::thread_fft_config_data_V_read() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_empty_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_full_n.read())))) {
        fft_config_data_V_read = ap_const_logic_1;
    } else {
        fft_config_data_V_read = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_fft_config_data_V_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
         !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_empty_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_full_n.read())))) {
        fft_config_data_V_write = ap_const_logic_1;
    } else {
        fft_config_data_V_write = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_i_1_fu_103_p2() {
    i_1_fu_103_p2 = (!i_reg_73.read().is_01() || !ap_const_lv11_1.is_01())? sc_lv<11>(): (sc_biguint<11>(i_reg_73.read()) + sc_biguint<11>(ap_const_lv11_1));
}

void write_FFT_data_1200::thread_internal_ap_ready() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_1))) {
        internal_ap_ready = ap_const_logic_1;
    } else {
        internal_ap_ready = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_real_start() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, start_full_n.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_0, start_once_reg.read()))) {
        real_start = ap_const_logic_0;
    } else {
        real_start = ap_start.read();
    }
}

void write_FFT_data_1200::thread_start_out() {
    start_out = real_start.read();
}

void write_FFT_data_1200::thread_start_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, start_once_reg.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, real_start.read()))) {
        start_write = ap_const_logic_1;
    } else {
        start_write = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_to_FFT_2_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0))) {
        to_FFT_2_blk_n = to_FFT_2_full_n.read();
    } else {
        to_FFT_2_blk_n = ap_const_logic_1;
    }
}

void write_FFT_data_1200::thread_to_FFT_2_din() {
    to_FFT_2_din = to_FFT_dout.read();
}

void write_FFT_data_1200::thread_to_FFT_2_write() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
         !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))))) {
        to_FFT_2_write = ap_const_logic_1;
    } else {
        to_FFT_2_write = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_to_FFT_blk_n() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0))) {
        to_FFT_blk_n = to_FFT_empty_n.read();
    } else {
        to_FFT_blk_n = ap_const_logic_1;
    }
}

void write_FFT_data_1200::thread_to_FFT_read() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && 
         esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
         !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))))) {
        to_FFT_read = ap_const_logic_1;
    } else {
        to_FFT_read = ap_const_logic_0;
    }
}

void write_FFT_data_1200::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && !(esl_seteq<1,1,1>(ap_const_logic_0, real_start.read()) || esl_seteq<1,1,1>(ap_done_reg.read(), ap_const_logic_1) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_empty_n.read()) || esl_seteq<1,1,1>(ap_const_logic_0, fft_config_data_V_full_n.read())))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state1;
            }
            break;
        case 2 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))) && esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_1))) {
                ap_NS_fsm = ap_ST_fsm_state1;
            } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state2.read()) && esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && !((esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_empty_n.read())) || (esl_seteq<1,1,1>(exitcond_fu_97_p2.read(), ap_const_lv1_0) && 
  esl_seteq<1,1,1>(ap_const_logic_0, to_FFT_2_full_n.read()))))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state2;
            }
            break;
        default : 
            ap_NS_fsm = "XX";
            break;
    }
}

}

