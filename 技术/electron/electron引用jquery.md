# electron引用jquery方式汇总

**问题原因：**
Electron 的 Renderer 端因为注入了 Node 环境，存在全局函数 require，导致 jQuery 内部环境判断有问题！

**处理办法**
1. 如果不需要在网页里面使用 node 模块（包括 electron 模块），建议把 BrowserWindow 的webPreferences.nodeIntegration 设置为 false。
在线页面更应该关掉 nodeIntegration，否则如果的页面被黑掉了，是非常危险的。

2. 将jquery文件一并打包进项目 /assets/js/ (自建目录) ，然后如下引用
``` javascript
const APP_PATH = require('path').join(_dirname, '../../../app.asar');
window.$ = window.jQuery = require(path.join(APP_PATH, './assets/js/jquery.min'));
// 或者：
<script>window.$ = window.jQuery = require('jquery.js');</script>
```

3. 在所有js运行之前，重命名并删除对象
``` javascript
window.Myrequire = window.require;//(如果需要)
delete window.require;
delete window.exports;
delete window.module;
```