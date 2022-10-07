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

[**no-OS软件驱动文档**](https://wiki.analog.com/resources/eval/user-guides/ad-fmcomms2-ebz/software/baremetal)（此文档最后更新于2018, 所用软件开发工具为SDK而非后来推出的Vitis）

Zedboard板卡厂Digilent为NI子公司，为Xilinx合作伙伴。另一板卡厂AVNET也提供了完整的[文档支持](https://www.avnet.com/wps/portal/us/products/avnet-boards/avnet-board-families/zedboard/)。

[AD家的HDL文档1](https://wiki.analog.com/resources/fpga/docs/build#windows_environment_setup), [2](https://wiki.analog.com/resources/fpga/docs/hdl)

AD家的HDL代码仓两年发布一次正式更新，主分支为最新开发版，目前的最新正式版为2021第一版(2021_r1)。由于Vivado版本间不兼容，需使用对应的Vivado版本(2021.1)进行开发。代码仓库中提供了顶层设计代码、IP核代码及tcl脚本。

安装Vivado 2021.1于C:\Xilinx。

## 10/5

学习[GNU Make](https://csdiy.wiki/%E5%BF%85%E5%AD%A6%E5%B7%A5%E5%85%B7/GNU_Make/)。GNU是一套软件集，其名字源自递归缩写等文字游戏（还neta了Unix）。GNU Make可以调用不同的编译器，对源码进行编译或是更新输出文件。虽然Vivado SDK也提供了Tcl脚本支持，但还是不如Make方便高效。

Windows下运行类Unix的GNU Make程序可以选择安装Cygwin，一套在Windows中运行的GNU。

安装Cygwin于C:\cygwin64，安装make和git包。

## 10/6

### 学习AD代码仓提供的项目食用教程

于Cygwin根目录bashrc文件(C:\cygwin64\home\IntelLab)添加环境变量: export PATH=$PATH:/cygdrive/c/Xilinx/Vivado/2021.1/bin:/cygdrive/c/Xilinx/Vitis/2021.1/bin

通过Cygwin，于D:\zedboard\hdl-2021_r1\projects\fmcomms2\zed运行make, 得到.xpr项目文件，在Vivado中打开即可（no-OS开发需要的.xsa文件（即Vivado2019.3前的.hdf文件）位于sdk目录）。

![运行结果](p2.jpg)

---

发现Vivado默认不包含Vitis, [追加安装Vitis](https://blog.csdn.net/tcjy1000/article/details/126567610).

[driverDoc](http://analogdevicesinc.github.io/no-OS/dir_4ed417a91f9ccc543343a95aa671159a.html)

复制2021_r1源码至D:\zedboard\no-OS-2021_R1. 复制.xsa文件至projects\ad9361目录。

以管理员模式运行cmd, 运行setting64.bat后运行make.

![运行结果](p3.jpg)

运行make sdkopen在Vitis中打开项目。

10/7

尝试在Vivado连接设备，报错。发现是设备中安装了Hyper-V虚拟机所致，参考[此页](https://fpgacoding.com/to-v-or-not-to-v/)解决。执行了以下操作：

> So I disabled Hyper-V in Settings | Apps & Features | Programs and Features | Windows Features.

解决了连接问题。后续如果要用Hyper-V虚拟机需重新启用此项。

---

串口跑不通，新建一个hello world也不行。力不从心，歇了。
