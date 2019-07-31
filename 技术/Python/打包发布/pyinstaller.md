# pyinstaller

## 安装
``` bash
# 会安装在pip相同目录，安装后系统可以直接找到pyinstaller
pip install pyinstaller
```

## 打包发布
``` bash
# 发布可以使用 pyinstaller 直接调用脚本生成
pyinstaller -F simple.py

# 也可以使用python调用 pyinstaller-script 脚本再调用程序脚本生成

```

## 命令说明
- -w指令: 直接发布的exe应用带命令行调试窗口，指令内加-w可以屏蔽
- -F指令: 将应用打包为单独的exe文件
- -p指令: 后面可以增加pyinstaller搜索模块的路径
``` bash 
pyinstaller.ese -F -w -p D:\python27\lib\site-paceages C:\simple.py
```

## 卸载
``` bash
pip remove pyinstaller
```

