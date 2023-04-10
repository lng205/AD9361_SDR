s# Zedboard+AD9361 SDR开发日志

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

![AD板卡结构图](pic/p1.jpg)

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

![运行结果](pic/p2.jpg)

---

发现Vivado默认不包含Vitis, [追加安装Vitis](https://blog.csdn.net/tcjy1000/article/details/126567610).

[driverDoc](http://analogdevicesinc.github.io/no-OS/dir_4ed417a91f9ccc543343a95aa671159a.html)

复制2021_r1源码至D:\zedboard\no-OS-2021_R1. 复制.xsa文件至projects\ad9361目录。

以管理员模式运行cmd, 运行setting64.bat后运行make.

![运行结果](pic/p3.jpg)

运行make sdkopen在Vitis中打开项目。

## 10/7

尝试在Vivado连接设备，报错。发现是设备中安装了Hyper-V虚拟机所致，参考[此页](https://fpgacoding.com/to-v-or-not-to-v/)解决。执行了以下操作：

> So I disabled Hyper-V in Settings | Apps & Features | Programs and Features | Windows Features.

解决了连接问题。后续如果要用Hyper-V虚拟机需重新启用此项。

---

串口跑不通，新建一个hello world也不行。力不从心，歇了。

## 2/22

烧录linux镜像至SD卡。

https://wiki.analog.com/resources/tools-software/linux-software/zynq_images

根据BOOT盘根目录的readme，将zynq项目所需文件复制至根目录。

## 2/23

点亮系统，等待OTG转接头，学习设计通信参数配置。

## 2/24

测试传输效果，单音及双音收发正常。

## 2/25

测试QPSK。

## 2/26

测试QPSK。samba服务不可用，怀疑是网线直连没有DHCP的原因，等待网线快递。

## 2/27

通过路由器连接至同一局域网依然无法使用samba软件在Windows系统和ZYNQ的Linux系统间传送文件，重新安装samba服务。配置成功，可以通过网络共享文件。

参考页面：

[1](https://www.cnblogs.com/shellstudio/p/10756419.html#:~:text=%E5%90%AF%E5%8A%A8%E6%A0%91%E8%8E%93%E6%B4%BE%E4%BB%A5%E5%90%8E%EF%BC%8C%E5%9C%A8%E5%91%BD%E4%BB%A4%E8%A1%8C%E8%BE%93%E5%85%A5%EF%BC%9A%20sudo%20apt%20-get%20update%20sudo%20apt,-get%20install%20samba%20samba%20-%20common%20-%20bin)

[2](https://forum.ubuntu.com.cn/viewtopic.php?t=275853)

[3](https://www.cnblogs.com/yunmeng-shi/p/16215277.html)

生成QPSK数据输入板卡并接收。

## 2/28

测试QPSK，发现IQ两路间存在串扰。起初以为IQ两路基带信号需要正交，但这样QPSK的实现会十分复杂。

向刘博求助后发现可能是收发端载波本振存在相差。调节IIO软件内的接收机相位旋转参数，可以较好地接收NRZ信号。

断电后相差发生变化，需要设计相位同步方法。

## 3/2

设计相差估计算法，IQ均发送1信号，通过接收信号可估计载波相位差φ = arctan((I-Q)/(I+Q))。

学习pyadi和numpy，将matlab程序搬移至python。

查询ADI论坛及Oscilloscope插件源码，发现板内射频本振无法实现硬件相位同步，须通过软件对基带采样值进行矫正。

发现基带存在DC滤波，需发送零均值信号进行相差估计。IQ发送相同信号[1,1,1,-1,-1,1,-1,-1]，设接收机载波相位-发射机载波相位=φ。

## 3/3

平台使用的AD9361射频芯片的接收机本振无法通过硬件实现载波同步，因此需要实现相位差补偿程序来消除载波相位差带来的影响。

对于QPSK信号，其发送信号可表示为$s(t) = I(t)\cos(\omega_Ct)+Q(t)\sin(\omega_Ct)$。而接收信号可以表示为

$$I_R(t) = LPF\{s(t)\cos(\omega_Ct+\phi)\}=I(t)\cos(\phi)-Q(t)\sin(\phi)\\Q_R(t) = LPF\{s(t)\sin(\omega_Ct+\phi)\}=Q(t)\cos(\phi)+I(t)\sin(\phi)$$

其中，φ为接收信号相对于发送信号的载波相位差。

为了实现相位差补偿，首先需要进行相位同步，这里使用训练序列进行同步。可以发送相同的训练序列，由于此时I(t)=Q(t)，因此可以通过计算得到相位差$\phi=\arctan(\frac{Q-I}{Q+I})$。接着，通过以下公式计算出发送信号：

$$I(t) = I_R(t)\cos(\phi)+Q_R(t)\sin(\phi)
\\Q(t) = Q_R(t)\cos(\phi)-I_R(t)\sin(\phi)$$
然而，由于arctan函数以pi为周期，存在相位模糊问题。为了解决这个问题，可以设计特殊的训练序列，例如[1,1,1,0,0,1,0,0]，该序列具有零均值且可用于判断极性。
最后，可以通过实验验证相位差补偿算法的效果，并对算法进行优化和调整。

# 3/22

install [openwifi](https://github.com/open-sdr/openwifi)

set ip(restart the ethernet)

![ip](pic/ip_set.png)

# 3/24

## openofdm notes

(all according to 802.11)

> input: samples\
> output: data

### packet detection

- power trigger
  
    wait for large enough signal samples to avoid fake positive.

- short preamble
  
  use auto correlation to sync package and do freq correction

  (20MHz BW, 18ppm(0.0018%) LO precision->deltaF=90kHz for 5G)

### Frequency offset  correction

- coarse
  
  short preamble

- fine
  
  long preamble(omitted)

- pilot

  use pilot symbol in each OFDM frame to correct SFO(sample freq offset)

### symbol alignment

- In 802.11, each OFDM symbol is 4 μs long. At 20 MSPS sampling rate, this means each OFDM symbol contains 80 samples. The task is to group the incoming streaming of samples into 80-sample OFDM symbols. This can be achieved using the long preamble following the short preamble.

  ![OFDM_frame](pic/OFDM_frame.png)

- FFT

  Xilinx IP core.(64 data symbol per OFDM symbol)

### equailization

![subcarrier](pic/subcarrier.webp)

- use pilot symbol to equalize channel fading.

### decoding

- demod

  QAM to bits


- demodulation
  
  complex number to bits
    
- deinterleaving
  
  shuffle the bits inside each OFDM symbol
    
- Convolution decoding

  remove redundancy and correct potential bit errors
    
- Descramble.

### SIGNAL

- the first OFDM symbol after long preamble is the SIGNAL field, which contains the modulation rate and length of the packet. These information are needed to determine how many OFDM symbols to decode and how to decode them.

### Verilog Hacks

- Because of the limited capability of FPGA computation, compromises often need to made in the actual Verilog implementation. The most used techniques include quantization and look up table. In OpenOFDM, these approximations are used.

For example, the magnitude of complex number <I, Q> is estimated as:

$$ M \approx \alpha*max(|I|, |Q|) + \beta*min(|I|, |Q|) $$

and we set alpha = 1 beta = 0.25 so that only simple bit-shift is needed.

# 3/28

Try to make a low latency video streaming demo based on openwifi.

Connect cellphone and board through wireless network, and stream video from cellphone camera to the board.

Install streamlabs on cellphone. First try to stream to PC.Install ffmpeg on PC. Works well with latency at ~1 sec.

Try to stream to the board. Run into an error indicating the lack of video driver on board. Need to push the data to PC via ethernet.

Set route to the board via ethernet on PC. Therefore, the connection is PC->(wired)->board->(wireless)->cellphone. When the board is serving as AP, the packet loss rate is so high that the video quality is poor.

- Latency of wired connection

![ethernet](pic/ethernet.png)

Set cellphone as AP. Now the board and cellphone is in a subnet, and PC and the board is in another subnet.

Connect board to cellphone AP(set wpa first):

`wpa_supplicant -i sdr0 -c wpa-connect.conf & dhclient sdr0`

Set NAT on board to connect two subnet:

- enable ip forward

`sudo sysctl -w net.ipv4.ip_forward=1`

- set cellphone subnet in iptable

`sudo iptables -t nat -A POSTROUTING -o NICY -j MASQUERADE`

- set route

`sudo ip route add 192.168.13.0/24 via 192.168.10.1 dev eth0`

Test connection from PC to cellphone:

![pic](pic/PC2phoneViaBoard.png)

Use ffmpeg to decode video on PC:

`ffplay http://192.168.33.195:9060/1/v.flv -fflags nobuffer`

![streaming](pic/streaming.png)

## wave sending

transmit data via application layer using telnet.

use [python script](https://pythonspot.com/python-network-sockets-programming-tutorial/)

set ip as local ip on subnet.

![telnet](pic/telnet.png)

# 4/2

Try to build analog wave transmit demo.

Follow the instruction of [esp32](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32/get-started/index.html)

Set dev enviroments on zedboard.

The time setting of openwifi firmware is incorrect, which would results error in SSL validation. Set system time manualy with precision of 1s.

Unable to find the correct serial port on zedboard. The name of tty* files dosen't change after plug in the USB OTG port.

Try to see if this method work on a normal PC.

# 4/4

The ttyUSB0 shows up after plugging in the USB on PC. So the problem might comes from the lack of driver on zedboard.

Try to install the driver, and the make file run into an error.

[similar problem](https://forums.raspberrypi.com/viewtopic.php?t=255114)

The problem seems to be caused by [kernel headers](https://ez.analog.com/linux-software-drivers/f/q-a/565120/kuiper-kernel-version-number-causing-module-loading-and-compiling-issues).

The solution seems to be too hard. Try to use MSP430f5529 instead.

MSP430 runs into the same problem.

# 4/5

Rebuild the kernel to generate header files.

Install cross compiler.

Open a [issue](https://github.com/open-sdr/openwifi/issues/295).

# 4/9

Install ubuntu LTS 20.

Install vitis 2021.1. [Solve an enviroment problem](https://blog.csdn.net/aatu/article/details/124404439).

Rebuild kernel using openwifi script.

Set enviroment variable to proxy for the script:

`export HTTP_PROXY="http://127.0.0.1:7890`

Install [make](https://www.ruanyifeng.com/blog/2015/02/make.html):

`sudo apt install -y make`

# 4/10

SSH server doesn't work after UART serial connection. Reinstall openwifi image.

[TODO] Modify prepare_kernel.sh

Set proxy on board:

`export HTTPS_PROXY="http://192.168.10.1:7890"`

Download driver on board:

`curl https://www.silabs.com/documents/login/software/Linux_3.x.x_4.x.x_VCP_Driver_Source.zip --output -driver.zip`

Modify the prepare_kernel.sh in openwifi/user_space:

```shell
make -j 8 modules
sudo make modules_install INSTALL_MOD_PATH=/media/yb/rootfs/
sudo make headers_install INSTALL_HDR_PATH=/media/yb/rootfs/usr
```

Try to find advice:
 
我遇到了一个关于linux内核编译的问题。

我在开发板上使用USB OTG接口作为串口主机与单片机进行通信时遇到了问题。我希望能够利用开发板上的USB OTG接口与单片机进行通信，但是在使用ADI的Kuiper Linux 2021_R1固件时，系统无法在设备目录中识别到单片机。经过分析，我猜测是因为系统缺少串口驱动。

单片机的串口芯片是CP2102，我下载了官网提供的linux驱动，但是在编译驱动时出现了问题。编译命令是“make -C /lib/modules/uname -r/build M=/root/esp/driver modules”，但是出现了“/lib/modules/5.10.0-98248-g1bbe32fa5182-dirty/build: No such file or directory” 的错误信息，提示缺少所需的内核模块目录。
 
我搜索到了一个相似的问题：https://ez.analog.com/linux-software-drivers/f/q-a/565120/kuiper-kernel-version-number-causing-module-loading-and-compiling-issues

我尝试自行编译内核，但是出现了内核版本不正确的问题，且其中包含指向内核源目录的软连接，该目录不在SD卡内。在更改Makefile为编译得到的内核版本5.10.0，且手动替换软连接后，仍然无法解决问题。现在我正在尝试在SD卡中重新编译内核，但是固件的编译过程十分繁琐和复杂。

这个问题已经占用了我数天的时间，我想请教您有什么建议可以帮助我解决这个问题。