
**webpack做什么**
一句简单的话解释就是处理模块依赖，并将他们合并为可用的静态资源。

<!--more-->

**为什么选用webpack**
webpack的特点是它的依赖模块可以是js文件，也可以是css文件，只要配置对应的webpack-loader
.coffee、.sass、.jade等等静态资源文件都可以被引用，并解析。

## 上手
**安装**
1. 使用`npm install`命令创建`package.json`文件
2. 安装webpack`npm install webpack`，添加一个配置文件`webpack.config.js`
``` javascript
module.exports = {
  entry:"./entry.js",
  output: {
    path:__dirname,
    filename:"bundle.js"
  },
  module:{
    loaders:[
      {test: /\.css$/, loader:"style!css"}
    ]
  }
};
```
3. 执行webpack命令
如果全局安装了webpack，直接执行webpack命令就可以依赖`webpack.config.js`文件中的配置
分析entry.js中的依赖，打包输出`bundle.js`
使用`npm scripts`启动任务，在`package.json`中添加:
``` javascript
{
  ...
  "scripts":{
    "build":"NODE_ENV=production webpack --watch"
  }
  ...
}
```
执行`npm run build`，其中--watch参数表示持续的监听文件变化进行打包。


## 入口文件配置
**配置多个入口文件**

``` javascript
module.exports = {
  entry:{
    entry1_bundle:"./entry1.js",
    entry2_bundle:"./entry2.js"
  },
  output:{
    path:__dirname,
    filename:"[name].js"
  },
  module:{
    loaders:[
      {test:/\.css$/, loader:"style!css"}
    ]
  }
}
```