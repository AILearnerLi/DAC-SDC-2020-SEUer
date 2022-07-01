
open_project SEUer_HLS
set_top SEUer

add_files srdw_pw_share_conv.cc
add_files seuer.cc
add_files seuer.h

open_solution "solution1"
set_part {xczu3eg-sbva484-1-e} -tool vivado
create_clock -period 5 -name default

## Our design uses C and Verilog co-design, So it can not run csim.

## C code synthesis to generate Verilog code
csynth_design


## export synthesized Verilog code
export_design -format ip_catalog

exit
