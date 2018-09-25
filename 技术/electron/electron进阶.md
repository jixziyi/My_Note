# electron 进阶

- [electron发布](#electron发布)
    - [electron资源文件替换](#electron资源文件替换)
    - [electron打包二进制文件](#electron打包二进制文件)
    - [electron发布exe](#electron发布exe)


##  electron发布

### electron资源文件替换
将应用程序文件夹命名为app并放在electron的资源文件夹下
win/linux目录：
```
electron/resources/app
  |- package.json
  |- main.js
  |- index.html
```

### electron打包二进制文件

1. 全局安装
``` bash
cnpm install -g asar
```
2. 打包
``` bash
C:>asar pack <path> app.asar
```


### electron发布exe
注意：electron-packager是打包发布工具
electron-prebuilt是运行环境

1. 安装electron-packager:
``` bash
npm install --save-dev electron-packager
```

2. package.json中添加打包命令
``` javascript
"scripts": {
  "start": "electron .",
  "package": "electron-packager ./ app --win --out presenterTool --arch=x64 --version 1.3.4 --overwrite --ignore=node_modules" 
}
/*
electron-packager <location of project> <name of project> <platform> <architecture> <electron version> <optional options>
参数说明：
location of project:应用目录
name of project:应用名称
platform:要打包的平台
architecture:X86或X64平台
electron version:electron版本(使用的electron的版本不是应用程序的版本)
optional options:其他选项
*/
```

3. 执行
``` bash
npm run-script package
```

**使用electron-builder**
