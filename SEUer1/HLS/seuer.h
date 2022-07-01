#include <cstddef>
#include <stdio.h>
#include <math.h>
#include <ap_fixed.h>
#include "hls_stream.h"
#include <iostream>
#include <fstream>
#include <cmath>


#define FM_RG			8
#define FM_ACC_RG		11
#define WT_RG			10

#define AXI_ADDR_WIDTH 32
#define AXI_DATA_WIDTH 512

//for conv
#define WID 84
#define HEI 44
#define CHA 32



	typedef ap_uint<32> 				dtype_mem;
	typedef ap_uint<AXI_DATA_WIDTH> 	dtype_pipe;

	typedef ap_fixed<9 , 3, AP_RND, AP_SAT> FIX_FM;	//fix point for feature map
	typedef ap_fixed<12, 4, AP_RND, AP_SAT> FIX_FM_acc;	//fix point for accumulation
	typedef ap_fixed<11, 4, AP_RND, AP_SAT> FIX_WT;	//fix point for weights

	typedef ap_fixed<16, 8, AP_RND, AP_SAT> FIX_16_8;
	typedef ap_fixed<16, 6, AP_RND, AP_SAT> FIX_16_6;
	typedef ap_fixed<16, 5, AP_RND, AP_SAT> FIX_16_5;
	typedef ap_fixed<16, 4, AP_RND, AP_SAT> FIX_16_4;
	typedef ap_fixed<16, 3, AP_RND, AP_SAT> FIX_16_3;
	typedef ap_fixed<16, 10, AP_RND, AP_SAT> FIX_16_10;
	typedef ap_fixed<32,16, AP_RND, AP_SAT> FIX_32_16;
	typedef ap_fixed<32,12, AP_RND, AP_SAT> FIX_32_12;
	typedef ap_fixed<32,10, AP_RND, AP_SAT> FIX_32_10;
	typedef ap_fixed<32, 4, AP_RND, AP_SAT> FIX_32_4;
	typedef ap_fixed<32, 7, AP_RND, AP_SAT> FIX_32_7;
	typedef ap_fixed<32,25, AP_RND, AP_SAT> FIX_32_25;

	typedef ap_uint<1> uint1;
	typedef ap_uint<2> uint2;
	typedef ap_uint<4> uint4;
	typedef ap_uint<8> uint8;
	typedef ap_uint<16> uint16;
	typedef ap_uint<256> uint256;
	typedef ap_uint<512> uint512;


	typedef struct
	{
		ap_uint<AXI_ADDR_WIDTH> awaddr;
		ap_uint<8> awlen;
	}dtype_aw;

	typedef struct
	{
		ap_uint<AXI_DATA_WIDTH> wdata;
		ap_uint<AXI_DATA_WIDTH/8> wstrb;
		ap_uint<1> wlast;
	}dtype_w;

	typedef struct
	{
		ap_uint<2> bresp;
	}dtype_b;

	typedef struct
	{
		ap_uint<AXI_ADDR_WIDTH> araddr;
		ap_uint<8> arlen;
	}dtype_ar;

	typedef struct
	{
		ap_uint<AXI_DATA_WIDTH> rdata;
		ap_uint<1> rlast;
	}dtype_r;


void SEUer(
				hls::stream<dtype_aw> &axi_aw,
				hls::stream<dtype_w> &axi_w,
				hls::stream<dtype_b> &axi_b,
				hls::stream<dtype_ar> &axi_ar,
				hls::stream<dtype_r> &axi_r,

				dtype_mem image_in_raw_pad,
				dtype_mem output_ini,

				uint512 fix_conv_weight_1x1_all_512bit[1000][32],
				uint512 fix_conv_weight_3x3_all_512bit[1000][9],
				uint512 fix_bias_all_512bit[500],

				uint512 DDR_dw1_pool_out_PL[64/32*82*2*162*2],
				uint512 DDR_dw2_pool_out_PL[96/32*42*2*82*2],

				uint512 DDR_buf[128*44*84],

				int *debug,
				float predict_box[4][5],
				int constant[4][3]
);

void Conv2D(FIX_FM bottom[CHA][HEI][WID],
			  FIX_FM_acc top[CHA][HEI][WID],
			  FIX_WT weights[CHA][CHA],
			  FIX_FM ex_bottom[CHA][HEI][WID],
			  uint1 mode, uint1 relu, uint2 CI);



