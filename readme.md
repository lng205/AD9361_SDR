# zynq7020+ad9361 sdr平台

- 本项目使用的zynq7020开发板为zedboard，ad9361板卡为fmcomms3。

- 平台基于[openwifi](https://github.com/open-sdr/openwifi)实现。

- 平台目前实现了低时延连续数据传输，接收端输出的连续波时延小于3毫秒（ping命令测量的往返时延小于1毫秒）。

- 测量本地转发时延，估计网络转发带来的时延。[TODO]

## 配置方法

### 初始化

1. 将开发板上的MIO4, MIO5跳线置高（使开发板通过SD卡启动）。

2. 下载最新的openwifi[镜像](https://drive.google.com/file/d/12egFLT9TclmY8m3vCMHmUuSne3qK0SWc/view?usp=sharing)，并使用刻录工具烧录至sd卡内。

3. 将\BOOT\openwifi\zed_fmcs2（板卡名称文件夹）目录下的.dtb和.BIN文件复制到根目录(\BOOT)，将根目录下的uImage文件替换为本项目的zedboard/uImage文件（需要Linux系统以识别\BOOT分区使用的MS-DOS文件系统）。

4. **弹出**SD卡。拔出SD卡并将其插入开发板。

5. 使用网线连接PC和开发板，设置PC的以太网IP地址为192.168.10.1（也可使用[串口](#其他)）。

6. 在终端中使用`ssh root@192.168.10.122`命令连接至开发板（推荐使用VScode的remote插件），密码为openwifi。

7. 输入命令`~/openwifi/setup_once.sh`。

此时平台完成了初始化设置。

### 通信模块启动

通过`cd openwifi; ./wgd.sh`命令启动无线网卡。

- AP: `~/openwifi/fosdem.sh`

- client: `wpa_supplicant -i sdr0 -c ~/openwifi/wpa-openwifi.conf &`，其中-i指定网卡，-c指定配置文件，&指定在后台运行。之后通过`dhclinet`获取ip。

- 关闭：查看fosdem.sh，发现其中使用了hostapd命令使网卡工作在模拟AP模式，因此可通过`killall hostapd`和`killall wpa_supplicant`关闭。

## Python转发脚本

- [client.py](./zedboard/client.py): 获取单片机通过串口发来的采样数据，并使用UDP协议转发至AP。

- [server.py](./zedboard/server.py): 监听UDP端口，将收到的数据通过串口转发至单片机。

## esp32程序

程序介绍：调用Arduino库，发射端通过定时器循环采样并通过串口发送。接收机等待串口数据并通过DA输出。

当尝试等待多个采样值合并发送，并在接收机通过定时器匀速输出时，平台的时延变得十分不稳定。原因尚不确定。[TODO]

## 其他

- **read-only file system**报错：可能是文件系统挂载时出错，重启可解决。

- 串口连接：将开发板的UART接口连接至PC，之后输入`sudo screen \dev\ttyUSB0 115200`即可。其中screen为串口软件（可用CTRL+A, ESC观察输出，CTRL+A, K退出）。\dev\ttyUSB0为设备串口路径，可通过`ls \dev\ttyUSB*`观察插拔前后输出的变化确定。115200为波特率。出现**乱码**问题时可尝试重新插拔USB数据线。

- clinet连接其他wifi: 修改wpa-connect.conf并使用`wpa_supplicant -i sdr0 -c openwifi/wpa-connect.conf`运行。

- 添加驱动：本项目提供的linux内核文件uImage是在openwifi的内核基础上，添加了CP210x驱动模块，重新编译得到。如需添加其他linux内核模块，需克隆openwifi项目源码，修改kernel_boot/kernel_config并启用所需模块，然后执行`cd openwifi/user_space; ./prepare_kernel.sh $Xilinx_PATH 32`命令（$Xilinx_PATH为Vitis安装目录，目前需要Vitis2021.1版本），编译生成的内核为openwifi/adi-linux/arch/arm/boot/uImage文件。使用新内核替换原有内核，之后重新输入命令`openwifi/setup_once.sh`，完成内核模块的添加（尚无法直接在板子上安装模块，该问题已报为[issues/295](https://github.com/open-sdr/openwifi/issues/295)）。

- 使用`shutdown`命令关闭内核后可能出现无法启动的问题，建议保持开机或者`poweroff`。

- zedboard的读卡器可能出问题，如果上电后蓝灯(DONE)不亮，可尝试反复插拔SD卡。