# Linux CentOS 7安装GNOME图形界面并设置默认启动方式

1. 电脑太渣，安装了CentOS 7 Minimal版本。 
2. 启动linux操作系统，进入后没有图形界面，但是有时候还是希望有图形界面的。输入root账户以及root密码登陆进linux系统。 
3. 安装图形用户接口X Window System，在命令窗口输入：
``` bash
yum groupinstall "X Window System"
yum groupinstall "GNOME Desktop"
```
安装完成会提示complete!

提示： X Window System本身是一个非常复杂的图形化作业环境，我们可以将它分成3个部分，分别是X Server、X Client和X Protocol。X Server主要是处理输入输出的信息，X Client执行大部分应用程序的运算功能，X Protocol则是建立X Server和X Client的沟通管道。 

X Window通过软件工具及架构协议来建立操作系统所用的图形用户界面，此后则逐渐扩展适用到各形各色的其他操作系统上，几乎所有的操作系统都能支持与使用X Window，GNOME和KDE也都是以X Window为基础建构成的。

提示：检查已经安装的软件以及可以安装的软件，用命令yum grouplist

4. 同样在root用户权限下，设置centos系统默认的启动方式，输入命令如下：

``` bash
systemctl set-default multi-user.target  # 设置成命令模式
systemctl set-default graphical.target   # 设置成图形模式
```
注意：centos7和centos6设置方式不同！

5. 重启系统即可。

6. 修改分辨率，重启就好了
``` bash
grubby --update-kernel=ALL --args="video=hyperv_fb:1280x768"
```
