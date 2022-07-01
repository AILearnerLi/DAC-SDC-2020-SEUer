create_project seuer ./vivado/seuer -part xczu3eg-sbva484-1-e
set_property board_part em.avnet.com:ultra96v2:part0:1.0 [current_project]
create_bd_design "design_1"
update_compile_order -fileset sources_1
startgroup
create_bd_cell -type ip -vlnv xilinx.com:ip:zynq_ultra_ps_e:3.3 zynq_ultra_ps_e_0
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:zynq_ultra_ps_e -config {apply_board_preset "1" }  [get_bd_cells zynq_ultra_ps_e_0]
set_property -dict [list CONFIG.PSU__CRL_APB__PL0_REF_CTRL__DIVISOR0 {7}] [get_bd_cells zynq_ultra_ps_e_0]
set_property -dict [list CONFIG.PSU__USE__S_AXI_GP2 {1} CONFIG.PSU__USE__S_AXI_GP3 {1} CONFIG.PSU__USE__S_AXI_GP4 {1}] [get_bd_cells zynq_ultra_ps_e_0]
add_files -norecurse ./axi_bridge.v
update_compile_order -fileset sources_1
create_bd_cell -type module -reference axi_bridge axi_bridge_0
set_property  ip_repo_paths  ../HLS/SEUer_HLS/solution1 [current_project]
update_ip_catalog
startgroup
create_bd_cell -type ip -vlnv xilinx.com:hls:SEUer:1.0 SEUer_0
endgroup
startgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/axi_bridge_0/M_AXI} Slave {/zynq_ultra_ps_e_0/S_AXI_HP0_FPD} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP0_FPD]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/SEUer_0/m_axi_INPUT_r} Slave {/zynq_ultra_ps_e_0/S_AXI_HP1_FPD} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP1_FPD]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/SEUer_0/m_axi_OUTPUT_r} Slave {/zynq_ultra_ps_e_0/S_AXI_HP2_FPD} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/S_AXI_HP2_FPD]
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {Auto} Clk_xbar {Auto} Master {/zynq_ultra_ps_e_0/M_AXI_HPM0_FPD} Slave {/SEUer_0/s_axi_AXILiteS} intc_ip {New AXI Interconnect} master_apm {0}}  [get_bd_intf_pins SEUer_0/s_axi_AXILiteS]
endgroup
apply_bd_automation -rule xilinx.com:bd_rule:axi4 -config { Clk_master {Auto} Clk_slave {/zynq_ultra_ps_e_0/pl_clk0 (214 MHz)} Clk_xbar {/zynq_ultra_ps_e_0/pl_clk0 (214 MHz)} Master {/zynq_ultra_ps_e_0/M_AXI_HPM1_FPD} Slave {/SEUer_0/s_axi_AXILiteS} intc_ip {/ps8_0_axi_periph} master_apm {0}}  [get_bd_intf_pins zynq_ultra_ps_e_0/M_AXI_HPM1_FPD]
onnect_bd_net [get_bd_pins SEUer_0/axi_r_V] [get_bd_pins axi_bridge_0/axi_r_V]
connect_bd_net [get_bd_pins SEUer_0/axi_b_V_bresp_V] [get_bd_pins axi_bridge_0/axi_b_V_bresp_V]
connect_bd_net [get_bd_pins SEUer_0/axi_r_V_ap_vld] [get_bd_pins axi_bridge_0/axi_r_V_ap_vld]
connect_bd_net [get_bd_pins SEUer_0/axi_ar_V_ap_ack] [get_bd_pins axi_bridge_0/axi_ar_V_ap_ack]
connect_bd_net [get_bd_pins SEUer_0/axi_b_V_bresp_V_ap_vld] [get_bd_pins axi_bridge_0/axi_b_V_bresp_V_ap_vld]
connect_bd_net [get_bd_pins SEUer_0/axi_w_V_ap_ack] [get_bd_pins axi_bridge_0/axi_w_V_ap_ack]
connect_bd_net [get_bd_pins SEUer_0/axi_aw_V_ap_ack] [get_bd_pins axi_bridge_0/axi_aw_V_ap_ack]
connect_bd_net [get_bd_pins SEUer_0/axi_ar_V] [get_bd_pins axi_bridge_0/axi_ar_V]
connect_bd_net [get_bd_pins SEUer_0/axi_w_V] [get_bd_pins axi_bridge_0/axi_w_V]
connect_bd_net [get_bd_pins SEUer_0/axi_aw_V] [get_bd_pins axi_bridge_0/axi_aw_V]
connect_bd_net [get_bd_pins SEUer_0/axi_r_V_ap_ack] [get_bd_pins axi_bridge_0/axi_r_V_ap_ack]
connect_bd_net [get_bd_pins SEUer_0/axi_ar_V_ap_vld] [get_bd_pins axi_bridge_0/axi_ar_V_ap_vld]
connect_bd_net [get_bd_pins SEUer_0/axi_b_V_bresp_V_ap_ack] [get_bd_pins axi_bridge_0/axi_b_V_bresp_V_ap_ack]
connect_bd_net [get_bd_pins SEUer_0/axi_w_V_ap_vld] [get_bd_pins axi_bridge_0/axi_w_V_ap_vld]
connect_bd_net [get_bd_pins SEUer_0/axi_aw_V_ap_vld] [get_bd_pins axi_bridge_0/axi_aw_V_ap_vld]
regenerate_bd_layout -routing
validate_bd_design
make_wrapper -files [get_files ./vivado/seuer/seuer.srcs/sources_1/bd/design_1/design_1.bd] -top
add_files -norecurse ./vivado/seuer/seuer.srcs/sources_1/bd/design_1/hdl/design_1_wrapper.v
update_compile_order -fileset sources_1
update_compile_order -fileset sources_1
set_property synth_checkpoint_mode None [get_files  ./vivado/seuer/seuer.srcs/sources_1/bd/design_1/design_1.bd]
generate_target all [get_files ./vivado/seuer/seuer.srcs/sources_1/bd/design_1/design_1.bd]
export_ip_user_files -of_objects [get_files ./vivado/seuer/seuer.srcs/sources_1/bd/design_1/design_1.bd] -no_script -sync -force -quiet
launch_runs impl_1 -to_step write_bitstream -jobs 4
