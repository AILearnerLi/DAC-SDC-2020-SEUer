# DAC-SDC-2020-SEUer


This is a repository for FPGA-based neural network inference for DAC'2020-SDC. 

SEUer Group, ASIC cneter, Southeast University, Nnajing, China

Guoqing Li*, Jingwei Zhang*, Ruixia Wu, Jiaojie Li, Feng Lv

li_guopqing@seu.edu.cn

In DAC'2020-SDC, Our design bases on SkyNet (https://github.com/TomG008/SkyNet), the champion design of the 56th IEEE/ACM Design Automation Conference System Design Contest (DAC-SDC). We deliver 72.2% Intersection over Union (IoU), 36.53fps and 8399J energy consumption on Ultra96v2. Our contributions are as follows:

1. Spatial to Channel (S2C)

  S2C can improve the utilization rate of bandwidth when read image. Also, it can improve the utilization rate of PE when computing the first Depthwise convolution (DWC).

2. Regulable Parallel (R-paralle)

  When computing pointwise convolution (PWC), sometimes, 16 input channels is enough. The parallelism of input channel and output channel is regulable, which is very suiltable for MobileNetV2.
  
3. Share PE and line buf.

  DWC and PWC share PE, which can sppedup DWC and reduce the number of used DSP. Line buf can speedup DWC.

4. Workflow

  After the first layer done, the next batch image is put to the right address of DDR, whcih can reduce the time of PL waiting PS.
  


Furethermoe, we deploy our approaches to Skrskr (https://github.com/jiangwx/SkrSkr), the second place of DAC'2020-SDC, which also based on SkyNet. We achieve 73.1 IOU, 68fps and 5000J.
