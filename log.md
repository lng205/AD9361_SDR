# Zedboard+AD9361 SDR开发日志

## 10/3

配置课题组PMPC-03主机, 数据存于D:\zedboard. 安装potplayer.

启动模式跳线设置(MIO[6:2])：SD(5'B01100), QSPI FLASH(5'B01000), JTAG(5'B00000)

AD9361板卡型号[AD-FMCOMMS3-EBZ](https://wiki.analog.com/resources/eval/user-guides/ad-fmcomms3-ebz)

参考视频：ZED9361发布视频1-3，升级至2018

参考页面：[AD板卡官方文档](https://wiki.analog.com/resources/eval/user-guides/ad-fmcomms3-ebz), [HDL仓库](https://github.com/analogdevicesinc/hdl/tree/master/projects/fmcomms2/zed), [no-OS软件驱动仓库](https://github.com/analogdevicesinc/no-OS/tree/master/projects/fmcadc2)

计划指标：1ms, 1Mbps。计划下一步先跑通最新版no-OS官方代码，之后开发射端分支，优先理解AD板卡驱动。可在基带加速通过PL端实现后用OS实现GUI。

学习DMA(Direct Memory Access)。通过释放内存总线使外部硬件可以不同频率读写内存，同时CPU可执行其他操作。

---

## 10/4

![AD板卡结构图](p1.jpg)

[特性曲线](https://wiki.analog.com/resources/eval/user-guides/ad-fmcomms3-ebz/hardware/card_specification)(LO=Local Oscillator)

[**no-OS软件驱动文档**](https://wiki.analog.com/resources/eval/user-guides/ad-fmcomms2-ebz/software/baremetal)

Zedboard板卡厂Digilent为NI子公司，为Xilinx合作伙伴。

[AD家的HDL文档1](https://wiki.analog.com/resources/fpga/docs/build#windows_environment_setup), [2](https://wiki.analog.com/resources/fpga/docs/hdl)

AD家的HDL代码仓两年发布一次正式更新，主分支为最新开发版，目前的最新正式版为2021第一版(2021_r1)。由于Vivado版本间不兼容，需使用对应的Vivado版本(2021.1)进行开发。代码仓库中提供了顶层设计代码、IP核代码及tcl脚本。

安装Vivado 2021.1于C:\Xilinx。
