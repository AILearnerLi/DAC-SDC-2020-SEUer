# DAC-SDC-SEUer2


This is a repository for FPGA-based neural network inference for DAC-SDC. 

SEUer Group, ASIC cneter, Southeast University, Nnajing, China

Guoqing Li*, Jingwei Zhang*, Xinye Cao, Yu Zhang

li_guopqing@seu.edu.cn   zhangjingwei@seu.edu.cn 

This design bases on the quantization of Srskr (the 2nd place of DAC'2020-SDC, https://github.com/jiangwx/SkrSkr), you will get a better result. 

You need to update the PMIC of Ultra96V2(old version). (https://github.com/AILearnerLi/Ultra96-V2-PMIC-Programming-Update-Procedure). Otherwise, the design cannot run at 300MHz, but can run at 290M.

You can modify the TCL files of Skrskr to run our design.



1. conv_bn_fusing.py
   The conv_bn_fusing file can fuse conv layer and BN layer. You can modify this file to be applied to other networks. It can convert .weights file to .bin file.
   


