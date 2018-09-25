# CentOS 7 网络设置

1. 使用root登录服务器:
``` bash
nmcli d
# STATE disconnected 即为未连接
```

2. 打开网络管理界面:
``` bash
nmtui
# 打开UI管理界面
# 使用tab键操作，enter进入
# 勾选ipv4的自动连接选项
```

3. 重启网络服务
``` bash
service network restart
# CentOS 安装网络工具
# 原有ifconfig 等命令已经不再使用，后续将使用 ip add 替代
# 如果仍要使用输入下面命令安装
yum install net-tools
```