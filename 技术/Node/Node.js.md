# Node.js 学习笔记

Node.js 就是运行在服务器端的 JavaScript 

## npm-check 版本检查
``` bash
# 安装
npm install -g npm-check

# 运行
npm-check -u -g # 检查全局包更新
```

## gnvm node.js 多版本管理工具

>特色
- 单文件，不依赖于任何环境。
- 下载即用，无需配置。
- 彩色日志输出。
- 支持多线程下载。
- 内置 taobao，方便切换，也支持自定义。
- 支持 npm 下载/安装/配置。

``` bash
# 使用
gnvm install latest
gnvm npm global
```


>功能
``` text
config       配置 .gnvmrc
use          使用某个本地已存在的 Node.js 版本
ls           输出 [local] [remote] Node.js 版本
install      下载/安装任意已知版本的 Node.js
uninstall    删除任意本地已存在的 Node.js
update       下载 Node.js latest 版本并更新到 .gnvmrc 里面
npm          NPM 下载/安装/删除 管理
session      临时设定本地某个已存在的 Node.js 为 全局 Node.js
search       查询并且输出符合查询条件的 Node.js 版本详细信息的列表
node-version 输出 [global] [latest] Node.js 版本
reg          设定 .gnvmrc 属性值 [noderoot] 为 环境变量 [NODE_HOME]，并加入到 Path 中
version      查看 gnvm 版本
```


## cnpm 淘宝NPM镜像

>命令
``` bash
npm install -g cnpm --registry=https://registry.npm.taobao.org
```



## yarn 使用

>命令

``` bash
cnpm install -g yarn
yarn config get registry
yarn config set registry=https://registry.npm.taobao.org
```

## nrm
``` bash
# 安装
npm install nrm -g

# 使用
nrm use taobao
```

