# KMS

cubieboard中使用py-kms与dnsmasq搭建局域网内全自动KMS激活环境。
众所周知，KMS激活方式是当前广大网民“试用”windows，office的最广泛的激活方式。几乎可以用于微软的全线产品。

<!-- more -->

但是在本机使用KMS类的激活工具总是有些不放心，一方面每隔180天都要重新激活，另外是这些工具来源不一，经常被杀软查杀，这些激活工具到底有没有安全问题？只能全靠信仰了。
因此，当前最能体现技术宅们不折腾不死心的做法就是在非本机环境下搭建kms激活模拟器，对局域网内机器进行远程激活。

### KMS激活服务器搭建

目前常用的KMS激活服务器程序为py-kms与vlmcsd，分别为python和C语言版本。可运行于各大freebsd/linux/openwrt/windows...环境中。

vlmcsd发布地址：

http://forums.mydigitallife.info/threads/50234-Emulated-KMS-Servers-on-non-Windows-platforms

py-kms发布地址：

https://github.com/myanaloglife/py-kms

个人更喜欢py-kms一些，依赖少，跨平台，不用编译。可以对windows全系列(7/8/8.1/10)，office全系列(~2013)进行激活。

我在局域网内cubietruck（一个类似树莓派的ARM主机）中安装py-kms的流程如下：

1. 安装依赖
``` bash
sudo apt-get install python-argparse
```
2. 下载代码
``` bash
git clone https://github.com/myanaloglife/py-kms
```
3. 运行激活服务器
``` bash
cd /py-kms
python server.py
```
这时候看到提示消息
``` bash
TCP server listening at 0.0.0.0 on port 1688.
```
就是说KMS服务已经在1688端口上打开了，没有错误。这就搭建完毕了。

4. 使用supervisor管理py-kms服务（非必须步骤）

为了让py-kms长期24小时运行于我的cubieboard中，我写了个supervisor脚本 pykms.conf 如下：

[program:pykms]
command=python /root/py-kms/server.py
autorestart=true
user=root
重启下supervisor，看到pykms正常运行，收工。

5.手动激活office 2013

参考：http://learner7.blog.51cto.com/1340889/1597515

我的office 是32位的2013版本，所以首先打开有管理员权限的命令行工具，进入程序安装目录：

CD "%ProgramFiles(x86)%\MICROSOFT OFFICE\OFFICE15"
运行激活命令：

``` bash
CSCRIPT OSPP.VBS /SETHST:192.168.0.xxx
CSCRIPT OSPP.VBS /ACT
CSCRIPT OSPP.VBS /DSTATUS
```
以上三行的大意是：1.设置激活服务器地址为192.168.0.xxx，即你的内网kms服务器地址；2.激活；3.查看激活状态。

完事，收工。

参考：

http://wrlog.com/activate-kms-vlmcsd.html
http://stdioa.github.io/2015/09/02/%E6%90%AD%E5%BB%BA%E7%A7%81%E6%9C%89KMS%E6%9C%8D%E5%8A%A1%E5%99%A8/
http://learner7.blog.51cto.com/1340889/1597515
http://forums.mydigitallife.info/threads/50234-Emulated-KMS-Servers-on-non-Windows-platforms

设置openwrt-dnsmasq使局域网用户自动发现kms激活服务器

py-kms与vlmcsd的适用性真的非常之广，不管你在windows，linux下甚至安卓下都可以搭建私有的kms服务。但是最后都会遇到的问题是需要在被激活主机上运行批处理命令，不免有些繁琐。

曾闻中国某高等学府批量购买企业windows许可，你的电脑只要连入校园网，不需要任何配置就可以激活系统，不免神往。查资料发现，这是通过配置DNS服务器的SRV项实现局域网内主机自动发现kms激活服务器的。

刚好我的路由器跑着openwrt系统，可以配置dnsmasq提供SRV功能，于是ssh进入路由器后台，在/etc/dnsmasq.conf中添加配置：

srv-host=_vlmcs._tcp.lan,cubietruck.lan,1688,0,100
其中 _vlmcs._tcp 为服务名；lan 为我的内网域名；cubietruck.lan为我的cubieboard在内网的地址；1688为kms激活服务默认端口号；0为优先级；100为权重。

然后在路由器中重启dnsmasq服务

/etc/init.d/dnsmasq restart
切换至windows验证dns配置是否正确，打开命令提示符，运行命令：

nslookup -type=srv _vlmcs._tcp.lan
其中 _vlmcs._tcp 表示kms服务类型，lan为我的局域网域名称。

看到返回信息：

_vlmcs._tcp.lan SRV service location:
          priority       = 0
          weight         = 100
          port           = 1688
          svr hostname   = cubietruck.lan
cubietruck.lan  internet address = 192.168.1.126
说明dns配置正确。


这时候看看我自己电脑上的office能不能成功发现kms服务器，还是在管理员权限下运行命令：

``` bash
CD "%ProgramFiles(x86)%\MICROSOFT OFFICE\OFFICE15"
CSCRIPT OSPP.VBS /remhst
CSCRIPT OSPP.VBS /act
CSCRIPT OSPP.VBS /dstatus
其中第一行表示清除之前设置的kms激活服务器地址，第二行手动激活，第三行显示激活状态。最终看到信息

REMAINING GRACE: 180 days  (259200 minute(s) before expiring
Last 5 characters of installed product key: XTGCT
Activation Type Configuration: ALL
        KMS machine name from DNS: cubietruck.lan:1688
        Activation Interval: 120 minutes
        Renewal Interval: 10080 minutes
        KMS host caching: Enabled
---------------------------------------
---------------------------------------
---Exiting-----------------------------
```
其中

 KMS machine name from DNS: cubietruck.lan:1688
表示能够根据DNS自动发现局域网内的kms激活服务器为cubietruck.lan。

说明office可以完全免配置自动激活。

以后任何电脑只要连接入我的局域网，即可对其VOL版本的office以及windows进行自动激活工作。cool~

参考：

http://blog.14401.cn/post-166.html
http://www.cnblogs.com/zhuangxuqiang/archive/2009/04/28/1445113.html
https://support.microsoft.com/en-us/kb/816587