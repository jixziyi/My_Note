
```
Node.js 就是运行在服务器端的 JavaScript 
```
<!--more-->

# ![logo](http://127.0.0.1:5000/node.png)  Node.js 学习笔记

#### GNVM Node.js 多版本管理工具

##### 特色

```
单文件，不依赖于任何环境。
下载即用，无需配置。
彩色日志输出。
支持多线程下载。
内置 TAOBAO，方便切换，也支持自定义。
支持 NPM 下载/安装/配置。
```

##### 功能

```tex
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


#### CNPM 淘宝NPM镜像

##### 命令

```shell
$ npm install -g cnpm --registry=https://registry.npm.taobao.org
```



#### yarn 使用

##### 命令

```shell
cnpm install -g yarn
yarn config get registry
yarn config set registry=https://registry.npm.taobao.org
```

