# PFX 证书

使用VS交叉工具命令提示行
``` bat
makecert -r -n "CN=Dingflow" -b 01/01/2018 -e 01/01/2020 -sv MyKey.pvk MyKey.cer

cert2spc MyKey.cer MyKey.spc

pvk2pfx -pvk MyKey.pvk -spc MyKey.spc -pfx MyKey.pfx -pi Password -f
```