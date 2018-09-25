
```
Ubuntu特殊使用技巧
```
<!--more-->

**虚拟机中网络映射**

错误内容：
```
Unable To Connect To Upstart: Failed To Connect ToSocket /Com/Ubuntu/Upstart: Connection Refused
```

```
sudo dpkg-divert --local --rename --add /sbin/initctl
```
```
ln -s /bin/true /sbin/initctl
```


**进程处理**

``` shell
ps #查看所有进程
kill XXX #杀掉指定PID进程
killall XXX #杀掉指定名字进程
jobs #显示使用&运行后台进程
grep XXX #查询命令: ls |grep XXX
```

