############ FOR HLS##########run about 30min 
cd HLS
vivado_hls -f script.tcl

########### FOR VIVADO ########run about several hours
cd RTL_and_Vivado
vivado -mode batch -source script.tcl
