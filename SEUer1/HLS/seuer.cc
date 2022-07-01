#include "seuer.h"
#include <math.h>
#include <fstream>
#include <hls_math.h>
#include <ap_fixed.h>
#include <string.h>

// feature map buffers
FIX_FM FM_buf1[32][44][84];
FIX_FM FM_buf2[32][44][84];
FIX_FM FM_buf3[32][44][84];
FIX_FM FM_buf4[32][44][84];
FIX_FM_acc FM_buf_acc[32][44][84];



// weight buffers
FIX_WT weight_buf[4][32][32];
FIX_WT bias_buf[4][32];



void compute_bounding_box(float predict_box[4][5], int constant[4][3])
{
    FIX_32_4 conf_thresh = -100.0;
    int conf_j = 0;
    int conf_m = 0;
    int conf_n = 0;
    FIX_32_4 conf_box1 = 0.0;
    FIX_32_4 conf_box2 = 0.0;

    for(int m = 1; m <= 20; m++){
        for(int n = 1; n <= 40; n++){
            conf_box1 = FM_buf_acc[4][m][n];
            if(conf_box1 > conf_thresh){
				conf_thresh = conf_box1;
				conf_j = 0;
				conf_m = m;
				conf_n = n;

            }
        }
    }

    for(int m = 1; m <= 20; m++){
        for(int n = 1; n <= 40; n++){
        	conf_box2 = FM_buf_acc[9][m][n];
            if(conf_box2 > conf_thresh){
                conf_thresh = conf_box2;
                conf_j = 1;
                conf_m = m;
                conf_n = n;
            }
        }
    }

	if( conf_j == 0 ) {
		// first bounding box
		predict_box[0][0] = FM_buf_acc[0][conf_m][conf_n];
		predict_box[0][1] = FM_buf_acc[1][conf_m][conf_n];
		predict_box[0][2] = FM_buf_acc[2][conf_m][conf_n];
		predict_box[0][3] = FM_buf_acc[3][conf_m][conf_n];
		predict_box[0][4] = conf_thresh;

	}
	else if( conf_j == 1 ) {
		// second bounding box
		predict_box[0][0] = FM_buf_acc[5][conf_m][conf_n];
		predict_box[0][1] = FM_buf_acc[6][conf_m][conf_n];
		predict_box[0][2] = FM_buf_acc[7][conf_m][conf_n];
		predict_box[0][3] = FM_buf_acc[8][conf_m][conf_n];
		predict_box[0][4] = conf_thresh;
	}

    constant[0][0] = conf_j;
    constant[0][1] = conf_n-1;
    constant[0][2] = conf_m-1;



    //// 1
    conf_thresh = -100.0;
    conf_j = 0;
    conf_m = 0;
    conf_n = 0;
    conf_box1 = 0.0;
    conf_box2 = 0.0;

    for(int m = 1; m <= 20; m++){
        for(int n = 43; n <= 82; n++){
            conf_box1 = FM_buf_acc[4][m][n];
            if(conf_box1 > conf_thresh){
				conf_thresh = conf_box1;
				conf_j = 0;
				conf_m = m;
				conf_n = n;

            }
        }
    }

    for(int m = 1; m <= 20; m++){
        for(int n = 43; n <= 82; n++){
        	conf_box2 = FM_buf_acc[9][m][n];
            if(conf_box2 > conf_thresh){
                conf_thresh = conf_box2;
                conf_j = 1;
                conf_m = m;
                conf_n = n;
            }
        }
    }

	if( conf_j == 0 ) {
		// first bounding box
		predict_box[1][0] = FM_buf_acc[0][conf_m][conf_n];
		predict_box[1][1] = FM_buf_acc[1][conf_m][conf_n];
		predict_box[1][2] = FM_buf_acc[2][conf_m][conf_n];
		predict_box[1][3] = FM_buf_acc[3][conf_m][conf_n];
		predict_box[1][4] = conf_thresh;

	}
	else if( conf_j == 1 ) {
		// second bounding box
		predict_box[1][0] = FM_buf_acc[5][conf_m][conf_n];
		predict_box[1][1] = FM_buf_acc[6][conf_m][conf_n];
		predict_box[1][2] = FM_buf_acc[7][conf_m][conf_n];
		predict_box[1][3] = FM_buf_acc[8][conf_m][conf_n];
		predict_box[1][4] = conf_thresh;
	}

    constant[1][0] = conf_j;
    constant[1][1] = conf_n-43;
    constant[1][2] = conf_m-1;




    //// 2
    conf_thresh = -100.0;
    conf_j = 0;
    conf_m = 0;
    conf_n = 0;
    conf_box1 = 0.0;
    conf_box2 = 0.0;

    for(int m = 23; m <= 42; m++){
        for(int n = 1; n <= 40; n++){
            conf_box1 = FM_buf_acc[4][m][n];
            if(conf_box1 > conf_thresh){
				conf_thresh = conf_box1;
				conf_j = 0;
				conf_m = m;
				conf_n = n;

            }
        }
    }

    for(int m = 23; m <= 42; m++){
        for(int n = 1; n <= 40; n++){
        	conf_box2 = FM_buf_acc[9][m][n];
            if(conf_box2 > conf_thresh){
                conf_thresh = conf_box2;
                conf_j = 1;
                conf_m = m;
                conf_n = n;
            }
        }
    }

	if( conf_j == 0 ) {
		// first bounding box
		predict_box[2][0] = FM_buf_acc[0][conf_m][conf_n];
		predict_box[2][1] = FM_buf_acc[1][conf_m][conf_n];
		predict_box[2][2] = FM_buf_acc[2][conf_m][conf_n];
		predict_box[2][3] = FM_buf_acc[3][conf_m][conf_n];
		predict_box[2][4] = conf_thresh;

	}
	else if( conf_j == 1 ) {
		// second bounding box
		predict_box[2][0] = FM_buf_acc[5][conf_m][conf_n];
		predict_box[2][1] = FM_buf_acc[6][conf_m][conf_n];
		predict_box[2][2] = FM_buf_acc[7][conf_m][conf_n];
		predict_box[2][3] = FM_buf_acc[8][conf_m][conf_n];
		predict_box[2][4] = conf_thresh;
	}

    constant[2][0] = conf_j;
    constant[2][1] = conf_n-1;
    constant[2][2] = conf_m-23;





    //// 3
    conf_thresh = -100.0;
    conf_j = 0;
    conf_m = 0;
    conf_n = 0;
    conf_box1 = 0.0;
    conf_box2 = 0.0;

    for(int m = 23; m <= 42; m++){
        for(int n = 43; n <= 82; n++){
            conf_box1 = FM_buf_acc[4][m][n];
            if(conf_box1 > conf_thresh){
				conf_thresh = conf_box1;
				conf_j = 0;
				conf_m = m;
				conf_n = n;

            }
        }
    }

    for(int m = 23; m <= 42; m++){
        for(int n = 43; n <= 82; n++){
        	conf_box2 = FM_buf_acc[9][m][n];
            if(conf_box2 > conf_thresh){
                conf_thresh = conf_box2;
                conf_j = 1;
                conf_m = m;
                conf_n = n;
            }
        }
    }

	if( conf_j == 0 ) {
		// first bounding box
		predict_box[3][0] = FM_buf_acc[0][conf_m][conf_n];
		predict_box[3][1] = FM_buf_acc[1][conf_m][conf_n];
		predict_box[3][2] = FM_buf_acc[2][conf_m][conf_n];
		predict_box[3][3] = FM_buf_acc[3][conf_m][conf_n];
		predict_box[3][4] = conf_thresh;

	}
	else if( conf_j == 1 ) {
		// second bounding box
		predict_box[3][0] = FM_buf_acc[5][conf_m][conf_n];
		predict_box[3][1] = FM_buf_acc[6][conf_m][conf_n];
		predict_box[3][2] = FM_buf_acc[7][conf_m][conf_n];
		predict_box[3][3] = FM_buf_acc[8][conf_m][conf_n];
		predict_box[3][4] = conf_thresh;
	}

    constant[3][0] = conf_j;
    constant[3][1] = conf_n-43;
    constant[3][2] = conf_m-23;



}


inline FIX_FM relu_single( FIX_FM d ) {
	if( d > 6 )
		return 6;
	if( d < 0 )
		return 0;
	return d;
}



void relu_copy_buf_to_DDR( uint512* dest, int buf_id, FIX_FM src[32][44][84], int offset_h, int offset_w)
{
	uint512* dest_ptr = dest + 44*84*buf_id + (offset_h*22)*84 + (offset_w*42);

	for(int h = 0; h < 44; h++) {


		for(int w = 0; w < 84; w++) {
#pragma HLS pipeline

			uint512 DATA = 0;
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				FIX_FM d = relu_single(src[c][h][w]);
				DATA.range(FM_RG + 16*c, 16*c) = d.range(FM_RG, 0);
			}
			dest_ptr[w].range(511, 0) = DATA.range(511, 0);
		}

		dest_ptr += 84;
	}
}

void xxxaxi_relu_copy_buf_to_DDR(hls::stream<dtype_aw> &axi_aw, hls::stream<dtype_w> &axi_w, hls::stream<dtype_b> &axi_b,
		dtype_mem base_addr, int buf_id, FIX_FM src[32][44][84], int offset_h, int offset_w)
{
	dtype_w w_pack;
	ap_uint<8> burst_len;

	dtype_aw aw_pack;
	dtype_mem addr_tp=base_addr + (44*84*buf_id + (offset_h*22)*84 + (offset_w*42))*(AXI_DATA_WIDTH/8);

	w_pack.wstrb=-1;

	for(int h=0;h<44;h++)
	{
		aw_pack.awlen=83;
		burst_len=83;

		aw_pack.awaddr=addr_tp;
		axi_aw.write(aw_pack);
		for(int w=0;w<=burst_len;w++)
		{
#pragma HLS PIPELINE
			uint512 DATA = 0;
			for(int c=0; c<32; c++)
			{
#pragma HLS unroll
				FIX_FM d = relu_single(src[c][h][w]);
				DATA.range(FM_RG + 16*c, 16*c) = d.range(FM_RG, 0);
			}
			w_pack.wdata= DATA;  //pipe.read()  buf[c][h][i].range(7, 0)
			if(w==burst_len)
				w_pack.wlast=1;
			else
				w_pack.wlast=0;
			axi_w.write(w_pack);
		}
		axi_b.read();

		addr_tp+=84*(AXI_DATA_WIDTH/8); //must be needed
	}
}


void relu_copy_buf_to_DDR_acc( uint512* dest, int buf_id, FIX_FM_acc src[32][44][84], int offset_h, int offset_w)
{
	uint512* dest_ptr = dest + 44*84*buf_id + (offset_h*22)*84 + (offset_w*42);

	for(int h = 0; h < 44; h++) {

		for(int w = 0; w < 84; w++) {
#pragma HLS pipeline

			uint512 DATA = 0;
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				FIX_FM d = relu_single((FIX_FM)src[c][h][w]);
				DATA.range(FM_RG + 16*c, 16*c) = d.range(FM_RG, 0);
			}
			dest_ptr[w].range(511, 0) = DATA.range(511, 0);
		}

		dest_ptr += 84;
	}
}

void xxxxaxi_relu_copy_buf_to_DDR_acc(hls::stream<dtype_aw> &axi_aw, hls::stream<dtype_w> &axi_w, hls::stream<dtype_b> &axi_b,
		dtype_mem base_addr, int buf_id, FIX_FM_acc src[32][44][84], int offset_h, int offset_w)
{
	dtype_w w_pack;
	ap_uint<8> burst_len;

	dtype_aw aw_pack;
	dtype_mem addr_tp=base_addr + (44*84*buf_id + (offset_h*22)*84 + (offset_w*42))*(AXI_DATA_WIDTH/8);

	w_pack.wstrb=-1;

	for(int h=0;h<44;h++)
	{
		aw_pack.awlen=83;
		burst_len=83;

		aw_pack.awaddr=addr_tp;
		axi_aw.write(aw_pack);
		for(int w=0;w<=burst_len;w++)
		{
#pragma HLS PIPELINE
			uint512 DATA = 0;
			for(int c=0; c<32; c++)
			{
#pragma HLS unroll
				FIX_FM d = relu_single((FIX_FM)src[c][h][w]);
				DATA.range(FM_RG + 16*c, 16*c) = d.range(FM_RG, 0);
			}
			w_pack.wdata= DATA;  //pipe.read()  buf[c][h][i].range(7, 0)
			if(w==burst_len)
				w_pack.wlast=1;
			else
				w_pack.wlast=0;
			axi_w.write(w_pack);
		}
		axi_b.read();

		addr_tp+=84*(AXI_DATA_WIDTH/8); //must be needed
	}
}


void load_buf_from_DDR( FIX_FM dest[32][44][84], uint512* src, int buf_id)
{
	uint512* src_ptr = src + 44*84*buf_id;

	for(int h = 0; h < 44; h++) {

		for(int w = 0; w < 84; w++) {
#pragma HLS pipeline II=1

			uint512 DATA= src_ptr[w];
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				dest[c][h][w].range(FM_RG, 0) = DATA.range(FM_RG + c*16, 16*c);
			}
		}
		src_ptr += 84;
	}
}
void xxxaxi_load_buf_from_DDR(hls::stream<dtype_ar> &axi_ar, hls::stream<dtype_r> &axi_r,
		dtype_mem base_addr, FIX_FM dest[32][44][84], int buf_id)
{
	dtype_r r_pack;
	dtype_ar ar_pack;

	dtype_mem addr_tp=base_addr + (44*84*buf_id)*(AXI_DATA_WIDTH/8);

	for(int h=0;h<44;h++)
	{
		ap_uint<8> ch=0;

		ar_pack.arlen=84-1;
		ar_pack.araddr=addr_tp+84*h*(AXI_DATA_WIDTH/8);
		axi_ar.write(ar_pack);
		for(int w=0; w<84; w++)
		{
#pragma HLS PIPELINE
			r_pack=axi_r.read();

			for(int c=0; c<32; c++)
			{
#pragma HLS unroll
				dest[c][h][w].range(FM_RG, 0) = r_pack.rdata.range(FM_RG + c*16, c*16);
			}
		}
	}
}


void load_weight_1x1_from_axi( FIX_WT dest[32][32], uint512 src[32])
{

	for(int ci = 0; ci < 32; ci++) {
#pragma HLS pipeline
		uint512 DATA = 0;
		DATA.range(511, 0) = src[ci].range(511, 0);
		for(int co = 0; co < 32; co++) {
#pragma HLS unroll
			dest[co][ci].range(WT_RG, 0) = DATA.range(WT_RG + co*16, co*16);
		}
	}
}



void load_weight_3x3_from_axi( FIX_WT dest[32][32], uint512 src[9])
{
	for(int m = 0; m < 3; m++) {
		for(int n = 0; n < 3; n++) {
#pragma HLS pipeline
			uint512 DATA = 0;
			DATA.range(511, 0) = src[3*m+n].range(511, 0);
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll

				dest[c][3*m+n].range(WT_RG, 0) = DATA.range(WT_RG + c*16, c*16);
			}
		}
	}
}



void load_bias_from_axi(FIX_WT dest[32], uint512 src)
{
	for(int c = 0; c < 32; c++) {
#pragma HLS unroll
		dest[c].range(WT_RG, 0) = src.range(WT_RG + c*16, c*16);
	}
}


void set_bias_1x1( FIX_FM_acc buf[32][44][84], FIX_WT bias[32])
{
#pragma HLS array_partition variable=buf dim=1 complete
#pragma HLS array_partition variable=bias dim=1 complete
	for(int h = 1; h <= 42; h+=2) {
		for(int w = 1; w <= 82; w++) {
#pragma HLS pipeline
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				buf[c][h  ][w] = bias[c];
				buf[c][h+1][w] = bias[c];
			}
		}
	}
}


void set_bias_3x3(FIX_FM buf[32][44][84], FIX_WT bias[32])
{
#pragma HLS array_partition variable=buf dim=1 complete
#pragma HLS array_partition variable=bias dim=1 complete
	for(int h = 1; h <= 42; h+=2) {
		for(int w = 1; w <= 82; w++) {
#pragma HLS pipeline
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				buf[c][h  ][w] = bias[c];
				buf[c][h+1][w] = bias[c];
			}
		}
	}
}



void load_dw1_pool_from_DDR( uint512* ddr_dw1_pool_burst,
							 FIX_FM buf[32][44][84],
							 int ch, int col, int row, int offset_h, int offset_w)
{
	uint512* ddr_dw1_pool_burst_ptr =ddr_dw1_pool_burst + ch*82*2*162*2 + (col*40 + offset_h*2)*162*2 + (row*80 + offset_w*2);

	for(int h = 0; h < 42; h++) {
		for(int w = 0; w < 82; w++) {
#pragma HLS pipeline
			uint512 DATA = 0;
			DATA.range(511, 0) = ddr_dw1_pool_burst_ptr[w].range(511, 0);
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll

				buf[c][h][w].range(FM_RG, 0) = DATA.range(FM_RG + c*16, c*16);
//				buf1[c][h][w] = buf[c][h][w];
//				buf2[c][h][w] = buf[c][h][w];

			}
		}
		ddr_dw1_pool_burst_ptr += 162*2;
	}
}



void load_dw2_pool_from_DDR( uint512* ddr_dw2_pool_burst,
							 FIX_FM buf[32][44][84],
							 int ch, int col, int row, int offset_h, int offset_w)
{
	uint512* ddr_dw2_pool_burst_ptr = ddr_dw2_pool_burst + ch*42*2*82*2 + (col*40 + offset_h*2)*82*2 + (row*80 + offset_w*2);

	for(int h = 0; h < 42; h++) {
		for(int w = 0; w < 82; w++) {
#pragma HLS pipeline
			uint512 DATA = 0;
			DATA.range(511, 0) = ddr_dw2_pool_burst_ptr[w].range(511, 0);
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				buf[c][h][w].range(FM_RG, 0) = DATA.range(FM_RG + c*16, c*16);
//				buf1[c][h][w] = buf[c][h][w];
//				buf2[c][h][w] = buf[c][h][w];
			}
		}
		ddr_dw2_pool_burst_ptr += 82*2;
	}
}




void clear_buffer( FIX_FM_acc buf[32][44][84] )
{
	for(int h = 0; h < 44; h+=2) {
		for(int w = 0; w < 84; w++) {
#pragma HLS pipeline
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				buf[c][h  ][w] = 0;
				buf[c][h+1][w] = 0;
			}
		}
	}
}


FIX_FM img_norm_ch[256] = {
		-2.000000, -1.984314, -1.968627, -1.952941, -1.937255, -1.921569, -1.905882, -1.890196, -1.874510, -1.858824, -1.843137, -1.827451, -1.811765, -1.796078, -1.780392, -1.764706, -1.749020,
		-1.733333, -1.717647, -1.701961, -1.686275, -1.670588, -1.654902, -1.639216, -1.623529, -1.607843, -1.592157, -1.576471, -1.560784, -1.545098, -1.529412, -1.513725, -1.498039,
		-1.482353, -1.466667, -1.450980, -1.435294, -1.419608, -1.403922, -1.388235, -1.372549, -1.356863, -1.341176, -1.325490, -1.309804, -1.294118, -1.278431, -1.262745, -1.247059,
		-1.231373, -1.215686, -1.200000, -1.184314, -1.168627, -1.152941, -1.137255, -1.121569, -1.105882, -1.090196, -1.074510, -1.058824, -1.043137, -1.027451, -1.011765, -0.996078,
		-0.980392, -0.964706, -0.949020, -0.933333, -0.917647, -0.901961, -0.886275, -0.870588, -0.854902, -0.839216, -0.823529, -0.807843, -0.792157, -0.776471, -0.760784, -0.745098,
		-0.729412, -0.713725, -0.698039, -0.682353, -0.666667, -0.650980, -0.635294, -0.619608, -0.603922, -0.588235, -0.572549, -0.556863, -0.541176, -0.525490, -0.509804, -0.494118,
		-0.478431, -0.462745, -0.447059, -0.431373, -0.415686, -0.400000, -0.384314, -0.368627, -0.352941, -0.337255, -0.321569, -0.305882, -0.290196, -0.274510, -0.258824, -0.243137,
		-0.227451, -0.211765, -0.196078, -0.180392, -0.164706, -0.149020, -0.133333, -0.117647, -0.101961, -0.086275, -0.070588, -0.054902, -0.039216, -0.023529, -0.007843, 0.007843,
		0.023529, 0.039216, 0.054902, 0.070588, 0.086275, 0.101961, 0.117647, 0.133333, 0.149020, 0.164706, 0.180392, 0.196078, 0.211765, 0.227451, 0.243137, 0.258824,
		0.274510, 0.290196, 0.305882, 0.321569, 0.337255, 0.352941, 0.368627, 0.384314, 0.400000, 0.415686, 0.431373, 0.447059, 0.462745, 0.478431, 0.494118, 0.509804,
		0.525490, 0.541176, 0.556863, 0.572549, 0.588235, 0.603922, 0.619608, 0.635294, 0.650980, 0.666667, 0.682353, 0.698039, 0.713725, 0.729412, 0.745098, 0.760784,
		0.776471, 0.792157, 0.807843, 0.823529, 0.839216, 0.854902, 0.870588, 0.886275, 0.901961, 0.917647, 0.933333, 0.949020, 0.964706, 0.980392, 0.996078, 1.011765,
		1.027451, 1.043137, 1.058824, 1.074510, 1.090196, 1.105882, 1.121569, 1.137255, 1.152941, 1.168627, 1.184314, 1.200000, 1.215686, 1.231373, 1.247059, 1.262745,
		1.278431, 1.294118, 1.309804, 1.325490, 1.341176, 1.356863, 1.372549, 1.388235, 1.403922, 1.419608, 1.435294, 1.450980, 1.466667, 1.482353, 1.498039, 1.513725,
		1.529412, 1.545098, 1.560784, 1.576471, 1.592157, 1.607843, 1.623529, 1.639216, 1.654902, 1.670588, 1.686275, 1.701961, 1.717647, 1.733333, 1.749020, 1.764706,
		1.780392, 1.796078, 1.811765, 1.827451, 1.843137, 1.858824, 1.874510, 1.890196, 1.905882, 1.921569, 1.937255, 1.952941, 1.968627, 1.984314, 2.000000
};


void load_image_chunk_norm(hls::stream<dtype_ar> &axi_ar, hls::stream<dtype_r> &axi_r,
							FIX_FM img_buf[32][44][84], dtype_mem image_in_raw_pad_burst,
							int col, int row, int offset_h = 0, int offset_w = 0)
{
	dtype_mem image_in_raw_pad_burst_ptr;
	dtype_ar ar_pack;
	dtype_r r_pack;

	ap_uint<8> p=0;
	dtype_pipe pipe_pack[3];

	image_in_raw_pad_burst_ptr = image_in_raw_pad_burst + (col*40 + offset_h*2)*322*2 + row*80 + offset_w*2;


	for(int i = 0; i < 44; i++) {
		ap_uint<2> ch=0;

		ar_pack.arlen=3-1;
		ar_pack.araddr=image_in_raw_pad_burst_ptr;
		axi_ar.write(ar_pack);

		for(int ii=0;ii<=ar_pack.arlen;ii++)
		{
#pragma HLS PIPELINE
			r_pack=axi_r.read();
			pipe_pack[ii]=r_pack.rdata;
		}

		p=(image_in_raw_pad_burst_ptr - image_in_raw_pad_burst)%64;

		for(int j = 0; j < 84; j=j+2) {
#pragma HLS pipeline
			img_buf[0][i][j] =	img_norm_ch[(pipe_pack[ch].range(7  + p*8,     p*8)).to_uint()];
			img_buf[0][i][j+1]= img_norm_ch[(pipe_pack[ch].range(15 + p*8, 8 + p*8)).to_uint()];
			if(p==62)
			{
				p=0;
				ch++;
			}
			else
				p=p+2;
		}
		image_in_raw_pad_burst_ptr += 322*2;
	}

	image_in_raw_pad_burst_ptr = image_in_raw_pad_burst + 1*162*2*322*2 + (col*40 + offset_h*2)*322*2 + row*80 + offset_w*2;

	for(int i = 0; i < 44; i++) {
		ap_uint<2> ch=0;

		ar_pack.arlen=3-1;
		ar_pack.araddr=image_in_raw_pad_burst_ptr;
		axi_ar.write(ar_pack);

		for(int ii=0;ii<=ar_pack.arlen;ii++)
		{
#pragma HLS PIPELINE
			r_pack=axi_r.read();
			pipe_pack[ii]=r_pack.rdata;
		}

		p=(image_in_raw_pad_burst_ptr - image_in_raw_pad_burst)%64;

		for(int j = 0; j < 84; j=j+2) {
#pragma HLS pipeline
			img_buf[1][i][j] =	img_norm_ch[(pipe_pack[ch].range(7  + p*8,     p*8)).to_uint()];
			img_buf[1][i][j+1]= img_norm_ch[(pipe_pack[ch].range(15 + p*8, 8 + p*8)).to_uint()];
			if(p==62)
			{
				p=0;
				ch++;
			}
			else
				p=p+2;
		}
		image_in_raw_pad_burst_ptr += 322*2;
	}

	image_in_raw_pad_burst_ptr = image_in_raw_pad_burst + 2*162*2*322*2 + (col*40 + offset_h*2)*322*2 + row*80 + offset_w*2;

	for(int i = 0; i < 44; i++) {
		ap_uint<2> ch=0;

		ar_pack.arlen=3-1;
		ar_pack.araddr=image_in_raw_pad_burst_ptr;
		axi_ar.write(ar_pack);

		for(int ii=0;ii<=ar_pack.arlen;ii++)
		{
#pragma HLS PIPELINE
			r_pack=axi_r.read();
			pipe_pack[ii]=r_pack.rdata;
		}

		p=(image_in_raw_pad_burst_ptr - image_in_raw_pad_burst)%64;

		for(int j = 0; j < 84; j=j+2) {
#pragma HLS pipeline
			img_buf[2][i][j] =	img_norm_ch[(pipe_pack[ch].range(7  + p*8,     p*8)).to_uint()];
			img_buf[2][i][j+1]= img_norm_ch[(pipe_pack[ch].range(15 + p*8, 8 + p*8)).to_uint()];

			if(p==62)
			{
				p=0;
				ch++;
			}
			else
				p=p+2;
		}
		image_in_raw_pad_burst_ptr += 322*2;
	}
}

void Relu6_3x3( FIX_FM buf[32][44][84])
{
	for(int h = 1; h <= 42; h+=2) {
		for(int w = 1; w <= 82; w++) {
#pragma HLS pipeline
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				buf[c][h  ][w] = relu_single(buf[c][h  ][w]);
				buf[c][h+1][w] = relu_single(buf[c][h+1][w]);
			}
		}
	}
}





inline FIX_FM relu_max(FIX_FM a, FIX_FM b, FIX_FM c, FIX_FM d)
{
	FIX_FM t1, t2;

	if(a > b) t1 = relu_single(a);
	else t1 = relu_single(b);

	if(c > d) t2 = relu_single(c);
	else t2 = relu_single(d);

	if(t1 > t2) return t1;
	else return t2;
}




void Relu_Max_Pooling_to_DDR(
		 FIX_FM_acc buf_in[32][44][84],
		 uint512* ddr_pw1_pool_burst,
		 uint512* ddr_pw2_pool_burst,
		 uint512* ddr_buf, int buf_id,
		 int ch, int col, int row, int offset_h, int offset_w, int layer)
{

	uint512* buf_in_ptr = ddr_buf + buf_id*44*84 + (1 + offset_h*22)*84 + offset_w*42;
	uint512* ddr_pw1_pool_burst_ptr = ddr_pw1_pool_burst + ch*82*2*162*2 + (1 + col*20 + offset_h*2)*162*2 + (row*40 + offset_w*2);
	uint512* ddr_pw2_pool_burst_ptr = ddr_pw2_pool_burst + ch*42*2*82*2 + (1 + col*20 + offset_h*2)*82*2 + (row*40 + offset_w*2);

#pragma HLS array_partition variable=buf_in dim=1 complete

	for(int h = 1; h <= 20; h++) {
		for(int w = 1; w <= 40; w++) {
#pragma HLS pipeline II=2
			uint512 DATA = 0;
			for(int c = 0; c < 32; c++) {
#pragma HLS unroll
				FIX_FM d = relu_max(buf_in[c][h*2-1][w*2-1], buf_in[c][h*2-1][w*2],
							   buf_in[c][h*2][w*2-1], buf_in[c][h*2][w*2]);

				DATA.range(FM_RG + c*16, c*16) = d.range(FM_RG, 0);
			}

			if( layer == 1 ) {
				ddr_pw1_pool_burst_ptr[w].range(511, 0) = DATA.range(511, 0);
			}
			else if( layer == 2 ) {
				ddr_pw2_pool_burst_ptr[w].range(511, 0) = DATA.range(511, 0);
			}
			else if( layer == 3 ) {
				buf_in_ptr[w].range(511, 0) = DATA.range(511, 0);
			}
		}

		buf_in_ptr += 84;
		ddr_pw1_pool_burst_ptr += 162*2;
		ddr_pw2_pool_burst_ptr += 82*2;
	}
}


void load_and_reorg_part( uint512* buf_in, int buf_id,
						  FIX_FM buf_out_1[32][44][84],
						  FIX_FM buf_out_2[32][44][84],
						  FIX_FM buf_out_3[32][44][84],
						  FIX_FM_acc buf_out_4[32][44][84],	// borrow one
						  int offset_h, int offset_w)
{
	uint512* buf_in_ptr = buf_in + buf_id*44*84;

	for(int h = 1; h <= 40; h+=4) {
		for(int w = 1; w <= 80; w+=4) {
#pragma HLS PIPELINE
			uint512 DATA[16] = {0};
			DATA[0].range(511, 0)  = buf_in_ptr[(h  )*84 + w  ].range(511, 0);
			DATA[1].range(511, 0)  = buf_in_ptr[(h+2)*84 + w  ].range(511, 0);
			DATA[2].range(511, 0)  = buf_in_ptr[(h  )*84 + w+2].range(511, 0);
			DATA[3].range(511, 0)  = buf_in_ptr[(h+2)*84 + w+2].range(511, 0);
			DATA[4].range(511, 0)  = buf_in_ptr[(h  )*84 + w+1].range(511, 0);
			DATA[5].range(511, 0)  = buf_in_ptr[(h+2)*84 + w+1].range(511, 0);
			DATA[6].range(511, 0)  = buf_in_ptr[(h  )*84 + w+3].range(511, 0);
			DATA[7].range(511, 0)  = buf_in_ptr[(h+2)*84 + w+3].range(511, 0);
			DATA[8].range(511, 0)  = buf_in_ptr[(h+1)*84 + w  ].range(511, 0);
			DATA[9].range(511, 0)  = buf_in_ptr[(h+3)*84 + w  ].range(511, 0);
			DATA[10].range(511, 0) = buf_in_ptr[(h+1)*84 + w+2].range(511, 0);
			DATA[11].range(511, 0) = buf_in_ptr[(h+3)*84 + w+2].range(511, 0);
			DATA[12].range(511, 0) = buf_in_ptr[(h+1)*84 + w+1].range(511, 0);
			DATA[13].range(511, 0) = buf_in_ptr[(h+3)*84 + w+1].range(511, 0);
			DATA[14].range(511, 0) = buf_in_ptr[(h+1)*84 + w+3].range(511, 0);
			DATA[15].range(511, 0) = buf_in_ptr[(h+3)*84 + w+3].range(511, 0);

			un:for(int c = 0; c < 8; c++) {
#pragma HLS UNROLL

				buf_out_1[c*4][(h+1)/2     + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[0].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[1].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4][(h+1)/2     + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[2].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[3].range(FM_RG + c * 16, c * 16);

				buf_out_1[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[4].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[5].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[6].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[7].range(FM_RG + c * 16, c * 16);

				buf_out_1[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[8].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[9].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[10].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[11].range(FM_RG + c * 16, c * 16);

				buf_out_1[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[12].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[13].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[14].range(FM_RG + c * 16, c * 16);
				buf_out_1[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[15].range(FM_RG + c * 16, c * 16);

				///////////////////
				buf_out_2[c*4][(h+1)/2     + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[0].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[1].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4][(h+1)/2     + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[2].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[3].range(FM_RG + (c + 8) * 16, (c + 8) * 16);

				buf_out_2[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[4].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[5].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[6].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[7].range(FM_RG + (c + 8) * 16, (c + 8) * 16);

				buf_out_2[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[8].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[9].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[10].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[11].range(FM_RG + (c + 8) * 16, (c + 8) * 16);

				buf_out_2[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[12].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[13].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[14].range(FM_RG + (c + 8) * 16, (c + 8) * 16);
				buf_out_2[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[15].range(FM_RG + (c + 8) * 16, (c + 8) * 16);

				buf_out_3[c*4][(h+1)/2     + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[0].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[1].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4][(h+1)/2     + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[2].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[3].range(FM_RG + (c + 16) * 16, (c + 16) * 16);

				buf_out_3[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[4].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[5].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[6].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[7].range(FM_RG + (c + 16) * 16, (c + 16) * 16);

				buf_out_3[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[8].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[9].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[10].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[11].range(FM_RG + (c + 16) * 16, (c + 16) * 16);

				buf_out_3[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[12].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(FM_RG, 0) = DATA[13].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[14].range(FM_RG + (c + 16) * 16, (c + 16) * 16);
				buf_out_3[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(FM_RG, 0) = DATA[15].range(FM_RG + (c + 16) * 16, (c + 16) * 16);

				/////////////////////
				buf_out_4[c*4][(h+1)/2     + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[0].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[1].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4][(h+1)/2     + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[2].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4][(h+1)/2+1   + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[3].range(WT_RG + (c + 24) * 16, (c + 24) * 16);

				buf_out_4[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[4].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[5].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+1][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[6].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+1][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[7].range(WT_RG + (c + 24) * 16, (c + 24) * 16);

				buf_out_4[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[8].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[9].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+2][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[10].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+2][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[11].range(WT_RG + (c + 24) * 16, (c + 24) * 16);

				buf_out_4[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[12].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2   + offset_w*42].range(WT_RG, 0) = DATA[13].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+3][(h+1)/2   + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[14].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
				buf_out_4[c*4+3][(h+1)/2+1 + offset_h*22][(w+1)/2+1 + offset_w*42].range(WT_RG, 0) = DATA[15].range(WT_RG + (c + 24) * 16, (c + 24) * 16);
			}
		}
	}
}



void load_and_reorg( uint512* buf_1, int buf_id_1, uint512* buf_2, int buf_id_2,
					 uint512* buf_3, int buf_id_3, uint512* buf_4, int buf_id_4,
					 FIX_FM buf_out_1[32][44][84],
					 FIX_FM buf_out_2[32][44][84],
					 FIX_FM buf_out_3[32][44][84],
					 FIX_FM_acc buf_out_4[32][44][84])
{
	load_and_reorg_part( buf_1, buf_id_1, buf_out_1, buf_out_2, buf_out_3, buf_out_4, 0, 0);
	load_and_reorg_part( buf_2, buf_id_2, buf_out_1, buf_out_2, buf_out_3, buf_out_4, 0, 1);
	load_and_reorg_part( buf_3, buf_id_3, buf_out_1, buf_out_2, buf_out_3, buf_out_4, 1, 0);
	load_and_reorg_part( buf_4, buf_id_4, buf_out_1, buf_out_2, buf_out_3, buf_out_4, 1, 1);
}


void local_buf_copy( FIX_FM dest[32][44][84], FIX_FM_acc src[32][44][84])
{
	for(int h = 0; h < 44; h+=2) {
		for(int w = 0; w < 84; w++) {
#pragma HLS pipeline
			for(int c = 0; c < 32; c++) {
				dest[c][h  ][w].range(FM_RG, 0) = src[c][h  ][w].range(FM_RG, 0);
				dest[c][h+1][w].range(FM_RG, 0) = src[c][h+1][w].range(FM_RG, 0);
			}
		}
	}
}

void send_ini(hls::stream<dtype_aw> &axi_aw, hls::stream<dtype_w> &axi_w, hls::stream<dtype_b> &axi_b,
					 dtype_mem base_addr)
{
	dtype_w w_pack;
	ap_uint<8> burst_len;

	dtype_aw aw_pack;
	dtype_mem addr_tp=base_addr;


	w_pack.wstrb=-1;

	for(int c=0;c<1;c++)
	{
		#pragma HLS LOOP_TRIPCOUNT min=4 max=4 avg=4
		for(int h=0;h<2;h++)
		{
			#pragma HLS LOOP_TRIPCOUNT min=10 max=10 avg=10
			for(int b=0;b<1;b=b+1)
			{
				#pragma HLS LOOP_TRIPCOUNT min=10 max=10 avg=10


					aw_pack.awlen=0;
					burst_len=0;

				aw_pack.awaddr=addr_tp+b*(AXI_DATA_WIDTH/8);
				axi_aw.write(aw_pack);
				for(int i=0;i<=burst_len;i++)
				{
#pragma HLS PIPELINE
					#pragma HLS LOOP_TRIPCOUNT min=256 max=256 avg=256
					w_pack.wdata=0;  //pipe.read()
					if(i==burst_len)
						w_pack.wlast=1;
					else
						w_pack.wlast=0;
					axi_w.write(w_pack);
				}
				axi_b.read();
			}
			addr_tp+=1*(AXI_DATA_WIDTH/8);;
		}
		addr_tp=2*1*(AXI_DATA_WIDTH/8);

	}

}

void SEUer(
				hls::stream<dtype_aw> &axi_aw,
				hls::stream<dtype_w> &axi_w,
				hls::stream<dtype_b> &axi_b,
				hls::stream<dtype_ar> &axi_ar,
				hls::stream<dtype_r> &axi_r,

				dtype_mem image_in_raw_pad,
				dtype_mem output_ini,

				uint512 conv_weight_1x1_all[1000][32],
				uint512 conv_weight_3x3_all[1000][9],
				uint512 bias_all[500],

				uint512 DDR_pw1_pool_out_PL_burst[64/32*82*2*162*2],
				uint512 DDR_pw2_pool_out_PL_burst[96/32*42*2*82*2],
				uint512 DDR_buf_burst[128*44*84],

				int *debug_pin,
				float predict_boxes[4][5],
				int constant[4][3]
)
{
#pragma HLS INTERFACE ap_hs port=axi_r
#pragma HLS INTERFACE ap_hs port=axi_ar
#pragma HLS DATA_PACK variable=axi_r
#pragma HLS DATA_PACK variable=axi_ar
#pragma HLS INTERFACE ap_hs port=axi_b
#pragma HLS INTERFACE ap_hs port=axi_aw
#pragma HLS INTERFACE ap_hs port=axi_w
#pragma HLS DATA_PACK variable=axi_w
#pragma HLS DATA_PACK variable=axi_aw


#pragma HLS INTERFACE m_axi depth=413*32		port=conv_weight_1x1_all		offset=slave	bundle=INPUT //306*32*32
#pragma HLS INTERFACE m_axi depth=64*3*3		port=conv_weight_3x3_all		offset=slave	bundle=INPUT //24*32*3*3
#pragma HLS INTERFACE m_axi depth=106			port=bias_all					offset=slave	bundle=INPUT //63*32

#pragma HLS INTERFACE m_axi depth=106272		port=DDR_dw1_pool_out_PL_burst	offset=slave	bundle=INPUT
#pragma HLS INTERFACE m_axi depth=41328			port=DDR_dw2_pool_out_PL_burst	offset=slave	bundle=INPUT
#pragma HLS INTERFACE m_axi depth=473088		port=DDR_buf_burst				offset=slave	bundle=INPUT

#pragma HLS INTERFACE m_axi depth=4*5			port=predict_boxes				offset=slave	bundle=OUTPUT
#pragma HLS INTERFACE m_axi depth=4*3			port=constant					offset=slave	bundle=OUTPUT
#pragma HLS INTERFACE m_axi depth=5				port=debug_pin					offset=slave	bundle=OUTPUT

#pragma HLS INTERFACE s_axilite port=image_in_raw_pad
#pragma HLS INTERFACE s_axilite port=output_ini
#pragma HLS INTERFACE s_axilite register	port=return


#pragma HLS ALLOCATION instances=Conv2D				 		limit=1 function
#pragma HLS ALLOCATION instances=Relu_Max_Pooling	    	limit=1 function
#pragma HLS ALLOCATION instances=load_image_chunk_norm		limit=1 function



		int CI_N, CO_N;
		int weight_3x3_index, weight_1x1_index, bias_3x3_index, bias_1x1_index;

		/////////////////////////////// DW1_CONV_3x3 + PW1_CONV_1x1 + POOL ////////////////////////////
		/// DW1_CONV_3x3
		debug_pin[0]=0;

		weight_3x3_index = 0;
		bias_3x3_index = 0;
		weight_1x1_index = 0;
		bias_1x1_index = 1;

		CI_N = 32 / 32;
		CO_N = 64 / 32;

		load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index]);
		load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index]);
		load_bias_from_axi(bias_buf[1], bias_all[bias_1x1_index + 0]);
		load_bias_from_axi(bias_buf[2], bias_all[bias_1x1_index + 1]);
		load_weight_1x1_from_axi(weight_buf[1], conv_weight_1x1_all[weight_1x1_index + 0]);
		load_weight_1x1_from_axi(weight_buf[2], conv_weight_1x1_all[weight_1x1_index + 1]);

		for(int row = 0; row < 8; row++) {

			load_image_chunk_norm(axi_ar, axi_r, FM_buf1, image_in_raw_pad, 0, row, 0/4, row/4);
			for(int col = 0; col < 8; col++) {
				set_bias_3x3(FM_buf4, bias_buf[0]);

				if( col % 2 == 0 ) {
					Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);
					load_image_chunk_norm(axi_ar, axi_r, FM_buf3, image_in_raw_pad, col+1, row, (col+1)/4, row/4);
				}
				else {
					Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf3, 0, 1, 2);
					load_image_chunk_norm(axi_ar, axi_r, FM_buf1, image_in_raw_pad, col+1, row, (col+1)/4, row/4);
				}


				for(int co = 0; co < CO_N; co++) {
					set_bias_1x1(FM_buf_acc, bias_buf[1 + co]);
					Conv2D(FM_buf4, FM_buf_acc, weight_buf[1 + co], FM_buf2, 1, 0, 1);
					Relu_Max_Pooling_to_DDR(FM_buf_acc, DDR_pw1_pool_out_PL_burst, DDR_pw2_pool_out_PL_burst, DDR_buf_burst, 0, co, col, row, col/4, row/4, 1);

				}
			}
		}

		/////////////////////////////// DW2_CONV_3x3 + PW2_CONV_1x1 + POOL ////////////////////////////
		/// DW2_CONV_3x3

		weight_3x3_index += CI_N;
		bias_3x3_index += CI_N + CO_N;
		weight_1x1_index += CO_N * CI_N;
		bias_1x1_index += CO_N + CO_N;

		load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + 0]);
		load_weight_3x3_from_axi(weight_buf[1], conv_weight_3x3_all[weight_3x3_index + 1]);
		load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + 0]);
		load_bias_from_axi(bias_buf[1], bias_all[bias_3x3_index + 1]);

		CI_N = 64 / 32;
		CO_N = 96 / 32;

		for(int row = 0; row < 4; row++) {
			for(int col = 0; col < 4; col++) {

				load_dw1_pool_from_DDR(DDR_pw1_pool_out_PL_burst, FM_buf1, 0, col, row, col/2, row/2);
				set_bias_3x3(FM_buf2, bias_buf[0]);
				Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);


				load_dw1_pool_from_DDR(DDR_pw1_pool_out_PL_burst, FM_buf3, 1, col, row, col/2, row/2);
				set_bias_3x3(FM_buf4, bias_buf[0 + 1]);
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[1], FM_buf3, 0, 1, 2);

				for(int co = 0; co < CO_N; co++) {
					load_bias_from_axi(bias_buf[2], bias_all[bias_1x1_index + co]);
					set_bias_1x1(FM_buf_acc, bias_buf[2]);

					load_weight_1x1_from_axi(weight_buf[2], conv_weight_1x1_all[weight_1x1_index + 0 + co * CI_N]);
					Conv2D(FM_buf2, FM_buf_acc, weight_buf[2], FM_buf1, 1, 0, 2);

					load_weight_1x1_from_axi(weight_buf[2], conv_weight_1x1_all[weight_1x1_index + 1 + co * CI_N]);
					Conv2D(FM_buf4, FM_buf_acc, weight_buf[2], FM_buf3, 1, 0, 1);

					Relu_Max_Pooling_to_DDR(FM_buf_acc, DDR_pw1_pool_out_PL_burst, DDR_pw2_pool_out_PL_burst, DDR_buf_burst, 0, co, col, row, col/2, row/2, 2);
				}
			}
		}

		/////////////////////////////// DW3_CONV_3x3 + PW3_CONV_1x1 + POOL ////////////////////////////


		/// DW3_CONV_3x3
		// output in DDR_buf[0] - DDR_buf[2]

		weight_3x3_index += CI_N;
		bias_3x3_index += CI_N + CO_N;
		weight_1x1_index += CO_N * CI_N;
		bias_1x1_index += CO_N + CO_N;

		load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + 0]);
		load_weight_3x3_from_axi(weight_buf[1], conv_weight_3x3_all[weight_3x3_index + 1]);
		load_weight_3x3_from_axi(weight_buf[2], conv_weight_3x3_all[weight_3x3_index + 2]);
		load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + 0]);
		load_bias_from_axi(bias_buf[1], bias_all[bias_3x3_index + 1]);
		load_bias_from_axi(bias_buf[2], bias_all[bias_3x3_index + 2]);

		CI_N = 96 / 32;
		CO_N = 192 / 32;


		for(int row = 0; row < 2; row++) {
			for(int col = 0; col < 2; col++) {

				load_dw2_pool_from_DDR(DDR_pw2_pool_out_PL_burst, FM_buf1, 0, col, row, col/1, row/1);
				set_bias_3x3(FM_buf2, bias_buf[0]);
				Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);

				load_dw2_pool_from_DDR(DDR_pw2_pool_out_PL_burst, FM_buf1, 1, col, row, col/1, row/1);
				set_bias_3x3(FM_buf3, bias_buf[0 + 1]);
				Conv2D(FM_buf3, FM_buf_acc, weight_buf[1], FM_buf1, 0, 1, 2);

				load_dw2_pool_from_DDR(DDR_pw2_pool_out_PL_burst, FM_buf1, 2, col, row, col/1, row/1);
				set_bias_3x3(FM_buf4, bias_buf[0 + 2]);
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[2], FM_buf1, 0, 1, 2);


				/// PW3_CONV_1x1
				for(int co = 0; co < CO_N; co++) {

					load_bias_from_axi(bias_buf[3], bias_all[bias_1x1_index + co]);
					set_bias_1x1(FM_buf_acc, bias_buf[3]);


					load_weight_1x1_from_axi(weight_buf[3], conv_weight_1x1_all[weight_1x1_index + 0 + co * CI_N]);
					Conv2D(FM_buf2, FM_buf_acc, weight_buf[3], FM_buf1, 1, 0, 2);

					load_weight_1x1_from_axi(weight_buf[3], conv_weight_1x1_all[weight_1x1_index + 1 + co * CI_N]);
					Conv2D(FM_buf3, FM_buf_acc, weight_buf[3], FM_buf1, 1, 0, 2);

					load_weight_1x1_from_axi(weight_buf[3], conv_weight_1x1_all[weight_1x1_index + 2 + co * CI_N]);
					Conv2D(FM_buf4, FM_buf_acc, weight_buf[3], FM_buf1, 1, 0, 2);

					relu_copy_buf_to_DDR_acc(DDR_buf_burst, 100 + co + (col*2 + row) * CO_N, FM_buf_acc, 0, 0);
					Relu_Max_Pooling_to_DDR(FM_buf_acc, DDR_pw1_pool_out_PL_burst, DDR_pw2_pool_out_PL_burst, DDR_buf_burst, 6 + co, co, col, row, col, row, 3 );
				}
			}
		}

		printf("DW3 Done\n");


		/////////////////////////////// DW4_CONV_3x3 + PW4_CONV_1x1 ////////////////////////////

		/// DW4_CONV_3x3
		// input in DDR_buf[6] - DDR_buf[11]
		// output in DDR_buf[12] - DDR_buf[17]

		weight_3x3_index += CI_N;
		bias_3x3_index += CI_N + CO_N;
		weight_1x1_index += CO_N * CI_N;
		bias_1x1_index += CO_N + CO_N;

		CI_N = 192 / 32;

		/// conv3x3: ping-pong in: FM_buf1 and FM_buf3
		/// conv3x3: out: FM_buf2

		load_buf_from_DDR(FM_buf1, DDR_buf_burst, 6 + 0);
		for(int c = 0; c < CI_N; c++) {
			load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + c]);
			load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + c]);
			set_bias_3x3(FM_buf4, bias_buf[0]);


			if( c % 2 == 0 ) {
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);
				load_buf_from_DDR(FM_buf3, DDR_buf_burst, 6 + c+1);
			}
			else {
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf3, 0, 1, 2);
				load_buf_from_DDR(FM_buf1, DDR_buf_burst, 6 + c+1);

			}



			relu_copy_buf_to_DDR(DDR_buf_burst, 12 + c, FM_buf4, 0, 0);
		}

		/// PW4_CONV_1x1
		// input in DDR_buf[12] - DDR_buf[17]
		// output in DDR_buf[18] - DDR_buf[29]

		CO_N = 384 / 32;
		for(int co = 0; co < CO_N; co++) {

			load_bias_from_axi(bias_buf[0], bias_all[bias_1x1_index + co]);
			set_bias_1x1(FM_buf_acc, bias_buf[0]);

			load_buf_from_DDR(FM_buf1, DDR_buf_burst, 12 + 0);
			for(int ci = 0; ci < CI_N; ci++) {
				load_weight_1x1_from_axi(weight_buf[1], conv_weight_1x1_all[weight_1x1_index + ci + co * CI_N]);
				if( ci % 2 == 0) {
					Conv2D(FM_buf1, FM_buf_acc, weight_buf[1], FM_buf2, 1, 0, 2);
					load_buf_from_DDR(FM_buf3, DDR_buf_burst, 12 + ci+1);
				}
				else {
					Conv2D(FM_buf3, FM_buf_acc, weight_buf[1], FM_buf4, 1, 0, 2);
					load_buf_from_DDR(FM_buf1, DDR_buf_burst, 12 + ci+1);
				}
			}


			relu_copy_buf_to_DDR_acc(DDR_buf_burst, 18 + co, FM_buf_acc, 0, 0);
		}


		/////////////////////////////// DW5_CONV_3x3 + PW5_CONV_1x1 ////////////////////////////

		/// DW5_CONV_3x3
		// input in DDR_buf[18] - DDR_buf[29]
		// output in DDR_buf[30] - DDR_buf[41]

		weight_3x3_index += CI_N;
		bias_3x3_index += CI_N + CO_N;
		weight_1x1_index += CO_N * CI_N;
		bias_1x1_index += CO_N + CO_N;

		CI_N = 384 / 32;

		load_buf_from_DDR(FM_buf1, DDR_buf_burst, 18 + 0);
		for(int c = 0; c < CI_N; c++) {
			load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + c]);
			load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + c]);
			set_bias_3x3(FM_buf4, bias_buf[0]);

			if( c % 2 == 0) {
				load_buf_from_DDR(FM_buf3, DDR_buf_burst, 18 + c+1);
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);
			}
			else {
				load_buf_from_DDR(FM_buf1, DDR_buf_burst, 18 + c+1);
				Conv2D(FM_buf4, FM_buf_acc, weight_buf[0], FM_buf3, 0, 1, 2);
			}
			relu_copy_buf_to_DDR(DDR_buf_burst, 30 + c, FM_buf4, 0, 0);
		}

		/// PW5_CONV_1x1
		// input in DDR_buf[30] - DDR_buf[41]
		// output in DDR_buf[42] - DDR_buf[57]

		CO_N = 512 / 32;
		for(int co = 0; co < CO_N; co++) {

			load_bias_from_axi(bias_buf[0], bias_all[bias_1x1_index + co]);
			set_bias_1x1(FM_buf_acc, bias_buf[0]);

			load_buf_from_DDR(FM_buf2, DDR_buf_burst, 30 + 0);
			for(int ci = 0; ci < CI_N; ci++) {
				load_weight_1x1_from_axi(weight_buf[1], conv_weight_1x1_all[weight_1x1_index + ci + co * CI_N]);

				if( ci % 2 == 0) {
					load_buf_from_DDR(FM_buf1, DDR_buf_burst, 30 + ci+1);
					Conv2D(FM_buf2, FM_buf_acc, weight_buf[1], FM_buf4, 1, 0, 2);
				}
				else {
					load_buf_from_DDR(FM_buf2, DDR_buf_burst, 30 + ci+1);
					Conv2D(FM_buf1, FM_buf_acc, weight_buf[1], FM_buf4, 1, 0, 2);
				}
			}

			relu_copy_buf_to_DDR_acc(DDR_buf_burst, 42 + co, FM_buf_acc, 0, 0);
		}


		/////////////////////////////// CONCAT PW3_CONV_1x1_OUT & DWP_CONV_1x1_OUT /////////////
		/////////////////////////////// DW6_CONV_3x3 + PW6_CONV_1x1 ////////////////////////////

		//// DW6_CONV_3x3

		weight_3x3_index += CI_N;
		bias_3x3_index += CI_N + CO_N;
		weight_1x1_index += CO_N * CI_N;
		bias_1x1_index += CO_N + CO_N;


		// First half: 0~767 channels from DW3_conv_1x1_output
		// Output of DW3_CONV_1x1_OUT are stored in DDR_buf[100] to DDR_buf[123]
		// Output of first half are stored in DDR_buf[58] to DDR_buf[81]
		CI_N = 768 / 32;
		for(int c = 0; c < CI_N; c+=4) {

			// From DDR_buf[100] to DDR_buf[123]
			// Img 0: 100 ~ 105
			// Img 1: 106 ~ 111
			// Img 2: 112 ~ 117
			// Img 3: 118 ~ 123

			load_and_reorg(DDR_buf_burst, 100 + c/4,         DDR_buf_burst, 100 + c/4 + 6,
						   DDR_buf_burst, 100 + c/4 + 6 * 2, DDR_buf_burst, 100 + c/4 + 6 * 3,
	                       FM_buf1, FM_buf3, FM_buf4, FM_buf_acc);

			//// 1/4 channels
			load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + c + 0]);
			load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + c + 0]);
			set_bias_3x3(FM_buf2, bias_buf[0]);
			Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);
			local_buf_copy(FM_buf1, FM_buf_acc);
			relu_copy_buf_to_DDR(DDR_buf_burst, 58 + c + 0, FM_buf2, 0, 0);

			//// 2/4 channels
			load_weight_3x3_from_axi(weight_buf[1], conv_weight_3x3_all[weight_3x3_index + c + 1]);
			load_bias_from_axi(bias_buf[1], bias_all[bias_3x3_index + c + 1]);
			set_bias_3x3(FM_buf2, bias_buf[1]);
			Conv2D(FM_buf2, FM_buf_acc, weight_buf[1], FM_buf3, 0, 1, 2);
			relu_copy_buf_to_DDR(DDR_buf_burst, 58 + c + 1, FM_buf2, 0, 0);

			//// 3/4 channels
			load_weight_3x3_from_axi(weight_buf[2], conv_weight_3x3_all[weight_3x3_index + c + 2]);
			load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + c + 2]);
			set_bias_3x3(FM_buf2, bias_buf[0]);
			Conv2D(FM_buf2, FM_buf_acc, weight_buf[2], FM_buf4, 0, 1, 2);
			relu_copy_buf_to_DDR(DDR_buf_burst, 58 + c + 2, FM_buf2, 0, 0);

			//// 4/4 channels
			load_weight_3x3_from_axi(weight_buf[3], conv_weight_3x3_all[weight_3x3_index + c + 3]);
			load_bias_from_axi(bias_buf[1], bias_all[bias_3x3_index + c + 3]);
			set_bias_3x3(FM_buf2, bias_buf[1]);
			Conv2D(FM_buf2, FM_buf_acc, weight_buf[3], FM_buf1, 0, 1, 2);
			relu_copy_buf_to_DDR(DDR_buf_burst, 58 + c + 3, FM_buf2, 0, 0);
		}

		// Second half: 768~1280 channels from PW5_conv_1x1_output
		// Output of DW5_CONV_1x1_OUT are stored in DDR_buf[42] - DDR_buf[57]
		// Output of first half are stored in DDR_buf[82] to DDR_buf[97]
		CI_N = 512 / 32;

		load_buf_from_DDR(FM_buf1, DDR_buf_burst, 42 + 0);
		for(int c = 0; c < CI_N; c++) {
			load_weight_3x3_from_axi(weight_buf[0], conv_weight_3x3_all[weight_3x3_index + c + 24]);
			load_bias_from_axi(bias_buf[0], bias_all[bias_3x3_index + c + 24]);
			set_bias_3x3(FM_buf2, bias_buf[0]);

			if( c % 2 == 0) {
				load_buf_from_DDR(FM_buf3, DDR_buf_burst, 42 + c+1);
				Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf1, 0, 1, 2);
			}
			else {
				load_buf_from_DDR(FM_buf1, DDR_buf_burst, 42 + c+1);
				Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf3, 0, 1, 2);
			}
			relu_copy_buf_to_DDR(DDR_buf_burst, 82 + c, FM_buf2, 0, 0);
		}

		/// PW6_CONV_1x1
		// input in DDR_buf[58] - DDR_buf[97]
		// output in DDR_buf[98] - DDR_buf[100]

		bias_1x1_index += 24;
		CO_N = 96 / 32;
		CI_N = 1280 / 32;
		for(int co = 0; co < CO_N; co++) {

			load_bias_from_axi(bias_buf[0], bias_all[bias_1x1_index + co]);
			set_bias_1x1(FM_buf_acc, bias_buf[0]);

			load_buf_from_DDR(FM_buf2, DDR_buf_burst, 58 + 0);
			for(int ci = 0; ci < CI_N; ci++) {
				load_weight_1x1_from_axi(weight_buf[0], conv_weight_1x1_all[weight_1x1_index + ci + co * CI_N]);

				if( ci % 2 == 0) {
					load_buf_from_DDR(FM_buf1, DDR_buf_burst, 58 + ci+1);
					Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf3, 1, 0, 2);
				}
				else {
					load_buf_from_DDR(FM_buf2, DDR_buf_burst, 58 + ci+1);
					Conv2D(FM_buf1, FM_buf_acc, weight_buf[0], FM_buf3, 1, 0, 2);
				}
			}

			relu_copy_buf_to_DDR_acc(DDR_buf_burst, 98 + co, FM_buf_acc, 0, 0);
		}


		printf("DW6 Done\n");


		/////////////////////////////// PW7_CONV_1x1 ////////////////////////////
		weight_1x1_index += CO_N * CI_N;
		// input in DDR_buf[98] - DDR_buf[100]
		// output in FM_buf_acc

		CO_N = 32 / 32;
		CI_N = 96 / 32;
		for(int co = 0; co < CO_N; co++) {
			clear_buffer(FM_buf_acc);
			for(int ci = 0; ci < CI_N; ci++) {
				load_weight_1x1_from_axi(weight_buf[0], conv_weight_1x1_all[weight_1x1_index + ci + co * CI_N]);
				load_buf_from_DDR(FM_buf2, DDR_buf_burst, 98 + ci);
				Conv2D(FM_buf2, FM_buf_acc, weight_buf[0], FM_buf1, 1, 0, 2);
			}
		}


		printf("PW7 Done\n");

		compute_bounding_box(predict_boxes, constant);

		send_ini(axi_aw, axi_w,axi_b,
					output_ini);

		debug_pin[0]=0;

		return;




}
