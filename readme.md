# zynq7020+ad9361 sdr平台

- 本项目使用的zynq7020开发板为zedboard，ad9361板卡为fmcomms3。

- 平台基于[openwifi](https://github.com/open-sdr/openwifi)实现。

- 平台目前实现了低时延连续数据传输，收发端输出的连续波时延小于3毫秒。

## 配置方法

### 初始化

1. 将开发板上的MIO4, MIO5跳线置高（使开发板通过SD卡启动）。

2. 下载最新的openwifi镜像，并使用刻录工具烧录至sd卡内。

3. 将\BOOT\openwifi\zed_fmcs2目录下的.dtb和.BIN文件复制到根目录(\BOOT)，将根目录下的uImage文件替换为本项目提供的uImage文件（需要Linux系统以识别\BOOT分区使用的MS-DOS文件系统）。

4. **弹出**SD卡。拔出SD卡并将其插入开发板。

5. 使用网线连接PC和开发板，设置PC的以太网IP地址为192.168.10.1（也可使用[串口](#其他)）。

6. 在终端中使用`ssh root@192.168.10.122`命令连接之开发板（推荐使用VScode的remote插件）。

7. 输入命令`openwifi/setup_once.sh`。

此时平台完成了初始化设置。

### 通信模块启动

- AP: `openwifi/fosdem.sh`

- client: `wpa_supplicant -i sdr0 -c openwifi/wpa-openwifi.conf`

## Python转发脚本

- client.py: 获取单片机通过串口发来的采样数据，并使用UDP协议转发至AP。

- server.py: 监听UDP端口，将收到的数据通过串口转发至单片机。

## esp32程序

[TODO]

## 其他

- **read-only file system**报错：可能是文件系统挂载时出错，重启可解决。

- 串口连接：将开发板的UART接口连接至PC，之后输入`sudo screen \dev\ttyUSB0 115200`即可。其中screen为串口软件。\dev\ttyUSB0为设备串口路径，可通过`ls \dev\ttyUSB*`观察插拔前后输出的变化确定。115200为波特率。出现**乱码**问题时可尝试重新插拔USB数据线。

- clinet连接其他wifi: 修改wpa-connect.conf并使用`wpa_supplicant -i sdr0 -c openwifi/wpa-connect.conf`运行。

- 添加驱动：本项目提供的linux内核文件uImage是在openwifi的内核基础上，添加了CP210x驱动模块，重新编译得到。如需添加其他linux内核模块，需克隆openwifi项目源码，修改kernel_boot/kernel_config并启用所需模块，然后执行`cd openwifi/user_space; ./prepare_kernel.sh $Xilinx_PATH 32`命令（$Xilinx_PATH为Vitis安装目录，目前需要Vitis2021.1版本），编译生成的内核为openwifi/adi-linux/arch/arm/boot/uImage文件。使用新内核替换原有内核，之后重新输入命令`openwifi/setup_once.sh`，完成内核模块的添加（尚无法直接在板子上安装模块，该问题已报为[issues/295](https://github.com/open-sdr/openwifi/issues/295)）。
