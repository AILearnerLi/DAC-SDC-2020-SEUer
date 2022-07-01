# DAC-SDC-SEUer  


This is a repository for FPGA-based neural network inference for DAC-SDC. 

SEUer Group, ASIC cneter, Southeast University, Nnajing, China

Guoqing Li*, Jingwei Zhang*, Xinye Cao, Ruixia Wu, Jiaojie Li, Yu Zhang, Feng Lv 

li_guopqing@seu.edu.cn   zhangjingwei@seu.edu.cn 


## SEUer1 
based on the quantization of iSmart3 (https://github.com/TomG008/SkyNet), the champion design of the 56th IEEE/ACM Design Automation Conference System Design Contest (DAC‘2020-SDC), obtained the 6th place. 

## SEUer2 
based on the quantization of Skrskr (https://github.com/jiangwx/SkrSkr), the 2nd design of the 57th IEEE/ACM Design Automation Conference System Design Contest (DAC‘2021-SDC). It has better performance than SEUer1. 

You need to update the PMIC of Ultra96V2. (https://github.com/AILearnerLi/Ultra96-V2-PMIC-Programming-Update-Procedure). Otherwise, the design cannot run at 300MHz, but can run at 290M.

In SEUer1 and SEUer12 Our contributions are as follows:

1. Spatial to Channel (S2C)

  S2C can improve the utilization rate of bandwidth when read image. Also, it can improve the utilization rate of PE when computing the first Depthwise convolution (DWC).

2. Regulable Parallel (R-paralle)

  When computing pointwise convolution (PWC), sometimes, 16 input channels is enough. The parallelism of input channel and output channel is regulable, which is very suiltable for MobileNetV2.
  
3. Share PE and line buf.

  DWC and PWC share PE, which can sppedup DWC and reduce the number of used DSP. Line buf can speedup DWC. The weights buffees also can be shared.

4. Workflow

  After the first layer done, the next batch image is put to the right address of DDR, whcih can reduce the time of PL waiting PS.
  
# SEUer2022 
Top 3 design in DAC‘2022-SDC
coming soon.
 
# cite
@article{li2022efficient,
  title={Efficient depthwise separable convolution accelerator for classification and UAV object detection},
  author={Li, Guoqing and Zhang, Jingwei and Zhang, Meng and Wu, Ruixia and Cao, Xinye and Liu, Wenzhao},
  journal={Neurocomputing},
  volume={490},
  pages={1--16},
  year={2022},
  publisher={Elsevier}
}


@inproceedings{li2022iscas,
  title={An Efficient FPGA Implementation for Real-Time and Low-Power UAV Object Detection},
  author={Li, Guoqing and Zhang, Jingwei and Zhang, Meng and Corporaal, Henk}
  booktitle={IEEE International Symposium on Circuits and Systems (ISCAS)},
  year={2022}
}

@article{zhang2021efficient,
  title={Efficient Hardware Optimization Strategies for Deep Neural Networks Acceleration Chip},
  author={ZHANG, Meng and ZHANG, Jingwei and LI, Guoqing and WU, Ruixia and ZENG, Xiaoyang},
  journal={电子与信息学报},
  volume={43},
  number={6},
  pages={1510--1517},
  year={2021},
  publisher={电子与信息学报}
}
