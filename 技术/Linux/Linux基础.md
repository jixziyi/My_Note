
# Linux基础

记录常用Liunx操作内容
<!-- more -->

## 查看CPU温度
下面介绍Linux下查看CPU温度的方法

CentOS系列:

``` bash
1.yum install lm_sensors;
2.sensors-detect
3.sensors
```

Ubuntu系列:
``` bash
1.apt-get install lm-sensors
2.sensors-detect
3.service kmod start
4.sensors
```


## 解压
tar -xzvf .tar.gz