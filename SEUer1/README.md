# DAC-SDC-SEUer-2020


This is a repository for FPGA-based neural network inference for DAC'2020-SDC. 

SEUer Group, ASIC cneter, Southeast University, Nnajing, China

Guoqing Li*, Jingwei Zhang*, Ruixia Wu, Jiaojie Li, Yu Zhang,

li_guopqing@seu.edu.cn   zhangjingwei@seu.edu.cn 

In DAC'2020-SDC, Our design bases on SkyNet (https://github.com/TomG008/SkyNet), the champion design of the 56th IEEE/ACM Design Automation Conference System Design Contest (DAC-SDC), obtained the 6th place. We deliver 72.4% Intersection over Union (IoU), 36.53fps and 8399J energy consumption on Ultra96v2. 


Some useful tools：

1. conv_bn_fusing.py
   The conv_bn_fusing file can fuse conv layer and BN layer. You can modify this file to be applied to other networks. It can convert .weights file to .bin file.
   


