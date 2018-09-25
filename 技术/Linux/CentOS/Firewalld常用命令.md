
## Linux防火墙之具有命令行的FirewallD的基本操作

**启动FirewallD服务：**
``` bash
systemctl enable firewalld.service        #设置开机启动
systemctl start firewalld.service            #开启服务
```

**查看防火墙状态：**
``` bash
systemctl status firewalld
```

1. 区域管理

1.1. 网络区域简介

通过将网络划分成不同的区域，制定出不同区域之间的访问控制策略来控制不同程序区域间传送的数据流。例如，互联网是不可信任的区域，而内部网络是高度信任的区域。网络安全模型可以在安装，初次启动和首次建立网络连接时选择初始化。该模型描述了主机所连接的整个网络环境的可信级别，并定义了新连接的处理方式。有如下几种不同的初始化区域：

阻塞区域（block）：任何传入的网络数据包都将被阻止。

工作区域（work）：相信网络上的其他计算机，不会损害你的计算机。

家庭区域（home）：相信网络上的其他计算机，不会损害你的计算机。

公共区域（public）：不相信网络上的任何计算机，只有选择接受传入的网络连接。

隔离区域（DMZ）：隔离区域也称为非军事区域，内外网络之间增加的一层网络，起到缓冲作用。对于隔离区域，只有选择接受传入的网络连接。

信任区域（trusted）：所有的网络连接都可以接受。

丢弃区域（drop）：任何传入的网络连接都被拒绝。

内部区域（internal）：信任网络上的其他计算机，不会损害你的计算机。只有选择接受传入的网络连接。

外部区域（external）：不相信网络上的其他计算机，不会损害你的计算机。只有选择接受传入的网络连接。

注：FirewallD的默认区域是public。

1.2. 显示支持的区域列表
``` bash
firewall-cmd --get-zones
```
1.3. 设置为家庭区域
``` bash
firewall-cmd --set-default-zone=home
```
1.4. 查看当前区域
``` bash
firewall-cmd --get-active-zones
```
1.5. 设置当前区域的接口
``` bash
firewall-cmd --get-zone-of-interface=enp03s
```
1.6. 显示所有公共区域（public）
``` bash
firewall-cmd --zone=public --list-all
```
1.7. 临时修改网络接口（enp0s3）为内部区域（internal）
``` bash
firewall-cmd --zone=internal --change-interface=enp03s
```
1.8. 永久修改网络接口enp03s为内部区域（internal）
``` bash
firewall-cmd --permanent --zone=internal --change-interface=enp03s
```
2. 服务管理

2.1. 显示服务列表

Amanda, FTP, Samba和TFTP等最重要的服务已经被FirewallD提供相应的服务，可以使用如下命令查看：
``` bash
firewall-cmd --get-services
```
2.2. 允许SSH服务通过
``` bash
# firewall-cmd --enable service=ssh 无效
firewall-cmd --add-service=ssh
```
2.3. 禁止SSH服务通过
``` bash
# firewall-cmd --disable service=ssh
firewall-cmd --remove-service=ssh
```
2.4. 打开TCP的8080端口
``` bash
firewall-cmd --enable ports=8080/tcp
```
2.5. 临时允许Samba服务通过600秒
``` bash
firewall-cmd --enable service=samba --timeout=600
```
2.6. 显示当前服务
``` bash
firewall-cmd --list-services
```
2.7. 添加HTTP服务到内部区域（internal）
``` bash
firewall-cmd --permanent --zone=internal --add-service=http
firewall-cmd --reload     #在不改变状态的条件下重新加载防火墙
```

3. 端口管理

3.1. 打开端口

``` bash
#打开443/TCP端口
firewall-cmd --add-port=443/tcp
#永久打开3690/TCP端口
firewall-cmd --permanent --add-port=3690/tcp
#永久打开端口好像需要reload一下，临时打开好像不用，如果用了reload临时打开的端口就失效了
#其它服务也可能是这样的，这个没有测试
firewall-cmd --reload
#查看防火墙，添加的端口也可以看到
firewall-cmd --list-all
```

4. 直接模式
FirewallD包括一种直接模式，使用它可以完成一些工作，例如打开TCP协议的9999端口
``` bash
firewall-cmd --direct -add-rule ipv4 filter INPUT 0 -p tcp --dport 9000 -j ACCEPT
firewall-cmd --reload
```
5. 关闭服务的方法

你也可以关闭目前还不熟悉的FirewallD防火墙，而使用iptables，命令如下：

``` bash
systemctl stop firewalld
systemctl disable firewalld
yum install iptables-services
systemctl start iptables
systemctl enable iptables
```