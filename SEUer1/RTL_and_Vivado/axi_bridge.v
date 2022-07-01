module axi_bridge #
(
    parameter AXI_ID_WIDTH=2,
    parameter AXI_DATA_WIDTH=512
)
(
    input ACLK,
    input ARESETN,
    input  [39:0] axi_aw_V,
    input   axi_aw_V_ap_vld,
    output   axi_aw_V_ap_ack,
    input  [AXI_DATA_WIDTH+(AXI_DATA_WIDTH/8):0] axi_w_V,
    input   axi_w_V_ap_vld,
    output   axi_w_V_ap_ack,
    output  [1:0] axi_b_V_bresp_V,
    output   axi_b_V_bresp_V_ap_vld,
    input   axi_b_V_bresp_V_ap_ack,
    input   axi_ar_V_ap_vld,
    output   axi_ar_V_ap_ack,
    input  [39:0] axi_ar_V,
    output   axi_r_V_ap_vld,
    input   axi_r_V_ap_ack,
    output  [AXI_DATA_WIDTH:0] axi_r_V,

	//AW channel
    output [AXI_ID_WIDTH-1 : 0] M_AXI_AWID,
    output [32-1 : 0] M_AXI_AWADDR,
    output [8-1 : 0] M_AXI_AWLEN,
    output [2 : 0] M_AXI_AWSIZE,//=clogb2((`AXI_DATA_WIDTH/8)-1);
    output [1 : 0] M_AXI_AWBURST,//=2'b01;
    output  M_AXI_AWLOCK,//1'b0;
    output [3 : 0] M_AXI_AWCACHE,//=4'b0010
    output [2 : 0] M_AXI_AWPROT,//=3'h0;
    output [3 : 0] M_AXI_AWQOS,//=4'h0;
    output  M_AXI_AWVALID,
    input  M_AXI_AWREADY,
    
    //Wr channel
    output [AXI_DATA_WIDTH-1 : 0] M_AXI_WDATA,
    output [AXI_DATA_WIDTH/8-1 : 0] M_AXI_WSTRB,
    output  M_AXI_WLAST,
    output  M_AXI_WVALID,
    input  M_AXI_WREADY,
    input [AXI_ID_WIDTH-1 : 0] M_AXI_BID,//ignore
    input [1 : 0] M_AXI_BRESP,//ignore
    input  M_AXI_BVALID,//Bvalid and Bread means a a write response.
    output  M_AXI_BREADY,//Bvalid and Bread means a a write response.
    
    //AR channel
    output [AXI_ID_WIDTH-1 : 0] M_AXI_ARID,
    output [32-1 : 0] M_AXI_ARADDR,
    output [8-1 : 0] M_AXI_ARLEN,
    output [2 : 0] M_AXI_ARSIZE,//=clogb2((`AXI_DATA_WIDTH/8)-1);
    output [1 : 0] M_AXI_ARBURST,//=2'b01;
    output  M_AXI_ARLOCK,//=1'b0;
    output [3 : 0] M_AXI_ARCACHE,//=4'b0010;
    output [2 : 0] M_AXI_ARPROT,//=3'h0;
    output [3 : 0] M_AXI_ARQOS,//=4'h0;
    output  M_AXI_ARVALID,
    input  M_AXI_ARREADY,
    
    //Rd channel
    input [AXI_ID_WIDTH-1 : 0] M_AXI_RID,
    input [AXI_DATA_WIDTH-1 : 0] M_AXI_RDATA,
    input [1 : 0] M_AXI_RRESP,//ignore
    input  M_AXI_RLAST,
    input  M_AXI_RVALID,
    output  M_AXI_RREADY
);

function integer clogb2 (input integer bit_depth);              
begin                                                           
for(clogb2=0; bit_depth>0; clogb2=clogb2+1)                   
  bit_depth = bit_depth >> 1;                                 
end                                                           
endfunction

//AW channel
assign M_AXI_AWSIZE=clogb2((AXI_DATA_WIDTH/8)-1);
assign M_AXI_AWBURST=2'b01;
assign M_AXI_AWLOCK=1'b0;
assign M_AXI_AWCACHE=4'b0010;
assign M_AXI_AWPROT=3'h0;
assign M_AXI_AWQOS=4'h0;
assign M_AXI_AWID=0;
assign M_AXI_AWADDR=axi_aw_V[31:0];
assign M_AXI_AWLEN=axi_aw_V[39:32];
assign M_AXI_AWVALID=axi_aw_V_ap_vld;
assign axi_aw_V_ap_ack=M_AXI_AWREADY;

//Wr channel
assign M_AXI_WDATA=axi_w_V[AXI_DATA_WIDTH-1:0];
assign M_AXI_WSTRB=axi_w_V[AXI_DATA_WIDTH+:(AXI_DATA_WIDTH/8)];
assign M_AXI_WLAST=axi_w_V[AXI_DATA_WIDTH+(AXI_DATA_WIDTH/8)];
assign M_AXI_WVALID=axi_w_V_ap_vld;
assign axi_w_V_ap_ack=M_AXI_WREADY;

//B channel
assign axi_b_V_bresp_V=M_AXI_BRESP;//ignore
assign axi_b_V_bresp_V_ap_vld=M_AXI_BVALID;//Bvalid and Bread means a a write response.
assign M_AXI_BREADY=axi_b_V_bresp_V_ap_ack;//Bvalid and Bread means a a write response.

//AR channel
assign M_AXI_ARSIZE=clogb2((AXI_DATA_WIDTH/8)-1);
assign M_AXI_ARBURST=2'b01;
assign M_AXI_ARLOCK=1'b0;
assign M_AXI_ARCACHE=4'b0010;
assign M_AXI_ARPROT=3'h0;
assign M_AXI_ARQOS=4'h0;
assign M_AXI_ARID=0;
assign M_AXI_ARADDR=axi_ar_V[31:0];
assign M_AXI_ARLEN=axi_ar_V[39:32];
assign M_AXI_ARVALID=axi_ar_V_ap_vld;
assign axi_ar_V_ap_ack=M_AXI_ARREADY;
    
//Rd channel
assign axi_r_V[AXI_DATA_WIDTH-1:0]=M_AXI_RDATA;
//input [1 : 0] M_AXI_RRESP,//ignore
assign axi_r_V[AXI_DATA_WIDTH]=M_AXI_RLAST;
assign axi_r_V_ap_vld=M_AXI_RVALID;
assign M_AXI_RREADY=axi_r_V_ap_ack;

endmodule
