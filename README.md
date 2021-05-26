# DAC-SDC-2020-SEUer

<!--
This is a repository for FPGA-based neural network inference for DAC'2020-SDC. 

SEUer Group, ASIC cneter, Southeast University, Nnajing, China

Guoqing Li*, Jingwei Zhang*, Ruixia Wu, Jiaojie Li, Feng Lv

li_guopqing@seu.edu.cn

In DAC'2020-SDC, Our design bases on SkyNet (https://github.com/TomG008/SkyNet), the champion design of the 56th IEEE/ACM Design Automation Conference System Design Contest (DAC-SDC), obtained the 6th place. We deliver 72.4% Intersection over Union (IoU), 36.53fps and 8399J energy consumption on Ultra96v2. The spped is limited by PS. If you can write a better python file or using the python file of Srskr (the 2nd place of DAC'2020-SDC, https://github.com/jiangwx/SkrSkr), you will get a better result. 

Our improvement methods are also effective for skrskr. The performance of Skrskr is better than iSmart3, so we deploy our approaches to Skrskr and obtaind the best performance for SkyNet, 73.1 IOU, 76fps and 4300J. We release code of the design based on Skrsrk.

You need to update the PMIC of Ultra96V2. (https://github.com/AILearnerLi/Ultra96-V2-PMIC-Programming-Update-Procedure). Otherwise, the design cannot run at 300MHz, but can run at 290M.

You can modify the TCL files of Skrskr to run our design.


Our contributions are as follows:

1. Spatial to Channel (S2C)

  S2C can improve the utilization rate of bandwidth when read image. Also, it can improve the utilization rate of PE when computing the first Depthwise convolution (DWC).

2. Regulable Parallel (R-paralle)

  When computing pointwise convolution (PWC), sometimes, 16 input channels is enough. The parallelism of input channel and output channel is regulable, which is very suiltable for MobileNetV2.
  
3. Share PE and line buf.

  DWC and PWC share PE, which can sppedup DWC and reduce the number of used DSP. Line buf can speedup DWC. The weights buffees also can be shared.

4. Workflow

  After the first layer done, the next batch image is put to the right address of DDR, whcih can reduce the time of PL waiting PS.
  
Some useful tools：

1. conv_bn_fusing.py
   The conv_bn_fusing file can fuse conv layer and BN layer. You can modify this file to be applied to other networks. It can convert .weights file to .bin file.
   
2. The code for quantization is coming.
-->
now, only bitfile. 
paper has been submitted. code will be open after acceptence.


