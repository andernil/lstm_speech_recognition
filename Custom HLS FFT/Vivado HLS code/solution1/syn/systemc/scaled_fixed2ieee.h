// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2018.3
// Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _scaled_fixed2ieee_HH_
#define _scaled_fixed2ieee_HH_

#include "systemc.h"
#include "AESL_pkg.h"

#include "scaled_fixed2ieee_out_bits_V.h"
#include "scaled_fixed2ieee_c.h"

namespace ap_rtl {

struct scaled_fixed2ieee : public sc_module {
    // Port declarations 9
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_in< sc_lv<63> > in_V;
    sc_in< sc_lv<12> > prescale;
    sc_out< sc_lv<64> > ap_return;


    // Module declarations
    scaled_fixed2ieee(sc_module_name name);
    SC_HAS_PROCESS(scaled_fixed2ieee);

    ~scaled_fixed2ieee();

    sc_trace_file* mVcdFile;

    scaled_fixed2ieee_out_bits_V* out_bits_V_U;
    scaled_fixed2ieee_c* c_U;
    sc_signal< sc_lv<7> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_lv<2> > i_5_fu_247_p2;
    sc_signal< sc_lv<2> > i_5_reg_613;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<2> > out_bits_V_addr_1_reg_618;
    sc_signal< sc_lv<1> > exitcond6_fu_241_p2;
    sc_signal< sc_lv<3> > i_6_fu_409_p2;
    sc_signal< sc_lv<3> > i_6_reg_626;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_lv<64> > tmp_62_fu_415_p1;
    sc_signal< sc_lv<64> > tmp_62_reg_631;
    sc_signal< sc_lv<1> > exitcond_fu_403_p2;
    sc_signal< sc_lv<1> > tmp_99_fu_439_p3;
    sc_signal< sc_lv<1> > tmp_99_reg_641;
    sc_signal< sc_logic > ap_CS_fsm_state6;
    sc_signal< sc_lv<3> > i_7_fu_447_p2;
    sc_signal< sc_lv<3> > i_7_reg_645;
    sc_signal< sc_lv<32> > shift_2_fu_458_p2;
    sc_signal< sc_logic > ap_CS_fsm_state7;
    sc_signal< sc_lv<63> > r_V_36_fu_503_p3;
    sc_signal< sc_lv<2> > out_bits_V_address0;
    sc_signal< sc_logic > out_bits_V_ce0;
    sc_signal< sc_lv<4> > out_bits_V_we0;
    sc_signal< sc_lv<32> > out_bits_V_d0;
    sc_signal< sc_lv<32> > out_bits_V_q0;
    sc_signal< sc_lv<2> > c_address0;
    sc_signal< sc_logic > c_ce0;
    sc_signal< sc_logic > c_we0;
    sc_signal< sc_lv<32> > c_d0;
    sc_signal< sc_lv<32> > c_q0;
    sc_signal< sc_lv<2> > i_reg_165;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_lv<3> > i1_reg_177;
    sc_signal< sc_logic > ap_CS_fsm_state5;
    sc_signal< sc_lv<63> > p_s_reg_188;
    sc_signal< sc_lv<1> > tmp_67_fu_512_p2;
    sc_signal< sc_lv<32> > shift_reg_198;
    sc_signal< sc_lv<3> > i2_reg_210;
    sc_signal< sc_lv<63> > ap_phi_mux_p_Val2_9_in_phi_fu_224_p4;
    sc_signal< sc_lv<63> > p_Val2_9_in_reg_221;
    sc_signal< sc_lv<32> > ap_phi_mux_shift_1_phi_fu_234_p4;
    sc_signal< sc_lv<32> > shift_1_reg_231;
    sc_signal< sc_lv<64> > tmp_fu_253_p1;
    sc_signal< sc_lv<64> > tmp_64_fu_453_p1;
    sc_signal< sc_lv<32> > tmp_83_fu_261_p3;
    sc_signal< sc_lv<32> > p_Result_4_fu_390_p5;
    sc_signal< sc_lv<15> > tmp_82_fu_258_p1;
    sc_signal< sc_lv<6> > tmp_s_fu_270_p3;
    sc_signal< sc_lv<6> > Lo_assign_fu_284_p2;
    sc_signal< sc_lv<6> > Hi_assign_fu_278_p2;
    sc_signal< sc_lv<1> > tmp_84_fu_290_p2;
    sc_signal< sc_lv<6> > tmp_86_fu_305_p2;
    sc_signal< sc_lv<6> > tmp_88_fu_317_p2;
    sc_signal< sc_lv<63> > tmp_85_fu_296_p4;
    sc_signal< sc_lv<6> > tmp_87_fu_311_p2;
    sc_signal< sc_lv<6> > tmp_89_fu_323_p3;
    sc_signal< sc_lv<6> > tmp_91_fu_338_p3;
    sc_signal< sc_lv<6> > tmp_92_fu_346_p2;
    sc_signal< sc_lv<63> > tmp_90_fu_331_p3;
    sc_signal< sc_lv<63> > tmp_93_fu_352_p1;
    sc_signal< sc_lv<63> > tmp_94_fu_356_p1;
    sc_signal< sc_lv<63> > tmp_95_fu_360_p2;
    sc_signal< sc_lv<63> > tmp_96_fu_366_p2;
    sc_signal< sc_lv<63> > p_Result_s_fu_372_p2;
    sc_signal< sc_lv<16> > tmp_98_fu_378_p1;
    sc_signal< sc_lv<17> > tmp_61_fu_382_p3;
    sc_signal< sc_lv<32> > p_Result_39_fu_420_p4;
    sc_signal< sc_lv<1> > isNeg_fu_465_p3;
    sc_signal< sc_lv<32> > tmp_65_fu_473_p2;
    sc_signal< sc_lv<32> > ush_fu_479_p3;
    sc_signal< sc_lv<63> > tmp_66_fu_487_p1;
    sc_signal< sc_lv<63> > r_V_fu_491_p2;
    sc_signal< sc_lv<63> > r_V_8_fu_497_p2;
    sc_signal< sc_lv<12> > tmp_68_fu_518_p2;
    sc_signal< sc_lv<32> > tmp_82_cast_fu_523_p1;
    sc_signal< sc_lv<32> > newexp_fu_527_p2;
    sc_signal< sc_lv<1> > tmp_101_fu_533_p3;
    sc_signal< sc_lv<1> > tmp_69_fu_541_p2;
    sc_signal< sc_lv<1> > or_cond_fu_546_p2;
    sc_signal< sc_lv<52> > phitmp1_fu_556_p4;
    sc_signal< sc_lv<11> > tmp_102_fu_552_p1;
    sc_signal< sc_lv<11> > out_exp_V_fu_574_p3;
    sc_signal< sc_lv<52> > significand_V_fu_566_p3;
    sc_signal< sc_lv<64> > p_Result_40_fu_582_p4;
    sc_signal< sc_lv<64> > result_write_assign_fu_592_p1;
    sc_signal< sc_lv<64> > ap_return_preg;
    sc_signal< sc_lv<7> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<7> ap_ST_fsm_state1;
    static const sc_lv<7> ap_ST_fsm_state2;
    static const sc_lv<7> ap_ST_fsm_state3;
    static const sc_lv<7> ap_ST_fsm_state4;
    static const sc_lv<7> ap_ST_fsm_state5;
    static const sc_lv<7> ap_ST_fsm_state6;
    static const sc_lv<7> ap_ST_fsm_state7;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<32> ap_const_lv32_5;
    static const sc_lv<32> ap_const_lv32_6;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<2> ap_const_lv2_0;
    static const sc_lv<3> ap_const_lv3_0;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_4;
    static const sc_lv<64> ap_const_lv64_3;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<4> ap_const_lv4_C;
    static const sc_lv<4> ap_const_lv4_F;
    static const sc_lv<2> ap_const_lv2_3;
    static const sc_lv<2> ap_const_lv2_1;
    static const sc_lv<17> ap_const_lv17_10000;
    static const sc_lv<6> ap_const_lv6_3E;
    static const sc_lv<6> ap_const_lv6_2F;
    static const sc_lv<32> ap_const_lv32_3E;
    static const sc_lv<63> ap_const_lv63_7FFFFFFFFFFFFFFF;
    static const sc_lv<32> ap_const_lv32_F;
    static const sc_lv<32> ap_const_lv32_1F;
    static const sc_lv<3> ap_const_lv3_4;
    static const sc_lv<3> ap_const_lv3_1;
    static const sc_lv<32> ap_const_lv32_10;
    static const sc_lv<12> ap_const_lv12_3FF;
    static const sc_lv<63> ap_const_lv63_0;
    static const sc_lv<32> ap_const_lv32_A;
    static const sc_lv<32> ap_const_lv32_3D;
    static const sc_lv<52> ap_const_lv52_0;
    static const sc_lv<11> ap_const_lv11_0;
    static const sc_lv<64> ap_const_lv64_0;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_Hi_assign_fu_278_p2();
    void thread_Lo_assign_fu_284_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_CS_fsm_state5();
    void thread_ap_CS_fsm_state6();
    void thread_ap_CS_fsm_state7();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_phi_mux_p_Val2_9_in_phi_fu_224_p4();
    void thread_ap_phi_mux_shift_1_phi_fu_234_p4();
    void thread_ap_ready();
    void thread_ap_return();
    void thread_c_address0();
    void thread_c_ce0();
    void thread_c_d0();
    void thread_c_we0();
    void thread_exitcond6_fu_241_p2();
    void thread_exitcond_fu_403_p2();
    void thread_i_5_fu_247_p2();
    void thread_i_6_fu_409_p2();
    void thread_i_7_fu_447_p2();
    void thread_isNeg_fu_465_p3();
    void thread_newexp_fu_527_p2();
    void thread_or_cond_fu_546_p2();
    void thread_out_bits_V_address0();
    void thread_out_bits_V_ce0();
    void thread_out_bits_V_d0();
    void thread_out_bits_V_we0();
    void thread_out_exp_V_fu_574_p3();
    void thread_p_Result_39_fu_420_p4();
    void thread_p_Result_40_fu_582_p4();
    void thread_p_Result_4_fu_390_p5();
    void thread_p_Result_s_fu_372_p2();
    void thread_phitmp1_fu_556_p4();
    void thread_r_V_36_fu_503_p3();
    void thread_r_V_8_fu_497_p2();
    void thread_r_V_fu_491_p2();
    void thread_result_write_assign_fu_592_p1();
    void thread_shift_2_fu_458_p2();
    void thread_significand_V_fu_566_p3();
    void thread_tmp_101_fu_533_p3();
    void thread_tmp_102_fu_552_p1();
    void thread_tmp_61_fu_382_p3();
    void thread_tmp_62_fu_415_p1();
    void thread_tmp_64_fu_453_p1();
    void thread_tmp_65_fu_473_p2();
    void thread_tmp_66_fu_487_p1();
    void thread_tmp_67_fu_512_p2();
    void thread_tmp_68_fu_518_p2();
    void thread_tmp_69_fu_541_p2();
    void thread_tmp_82_cast_fu_523_p1();
    void thread_tmp_82_fu_258_p1();
    void thread_tmp_83_fu_261_p3();
    void thread_tmp_84_fu_290_p2();
    void thread_tmp_85_fu_296_p4();
    void thread_tmp_86_fu_305_p2();
    void thread_tmp_87_fu_311_p2();
    void thread_tmp_88_fu_317_p2();
    void thread_tmp_89_fu_323_p3();
    void thread_tmp_90_fu_331_p3();
    void thread_tmp_91_fu_338_p3();
    void thread_tmp_92_fu_346_p2();
    void thread_tmp_93_fu_352_p1();
    void thread_tmp_94_fu_356_p1();
    void thread_tmp_95_fu_360_p2();
    void thread_tmp_96_fu_366_p2();
    void thread_tmp_98_fu_378_p1();
    void thread_tmp_99_fu_439_p3();
    void thread_tmp_fu_253_p1();
    void thread_tmp_s_fu_270_p3();
    void thread_ush_fu_479_p3();
    void thread_ap_NS_fsm();
};

}

using namespace ap_rtl;

#endif
