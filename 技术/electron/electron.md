# electron

Build cross platform desktop apps with JavaScript, HTML, and CSS

Electron提供了丰富的本地（操作系统）的API，使你能够使用纯JavaScript来创建桌面应用程序。与其它各种的Node.js运行时不同的是Electron专注于桌面应用程序而不是Web服务器。

这并不意味着Electron是一个绑定图形用户界面（GUI）的JavaScript库。取而代之的是，Electron使用Web页面作为它的图形界面，所以你也可以将它看作是一个由JavaScript控制的迷你的Chrominum浏览器。

<!--more-->

**主进程**

在Electron里，运行package.json里的main脚本的进程被称为 主进程 ，运行在主进程里的脚本能够通过创建Web页面来显示GUI。

**渲染进程**

因为Electron使用Chrominum来显示Web页面，所以Chrominum的多进程架构也同样被使用。每个页面在Electron里是运行在自己的进程里，这些进程被称为 渲染进程 。

在浏览器里，Web页面通常运行在一个沙盒环境里，它不能访问本地的资源。但在Electron里，在Web页面中通过使用Node.js API可以进行底层的操作系统交互。

**主进程与渲染进程的不同**

主进程通过构造 BrowserWindow 实例来创建Web页面。每个 BrowserWindow 实例在自己的渲染进程里运行Web页面。当一个 BrowserWindow 被销毁后，相应的渲染进程也同样被终止。

主进程管理所有的Web页面以及相关的渲染进程。每个渲染进程都是互相隔离的，并且只知道运行在该进程里的Web页面。

在Web页面里，调用本地GUI是不允许的，因为在Web页面里管理本地GUI资源是非常危险的而且非常容易导致资源泄露。如果你想在Web页面进行GUI操作，该Web页面的渲染进程必须通过和主进程通信来请求主进程处理这些操作。

在Electron里，主进程和渲染进程有很多通信的方法。

**Electron目录结构**
```
your-app/
|- package.json
|- main.js
|- index.html
```

1. package.json 内容：
``` json
// 如果main没有指定，默认位index.js
{
	"name"		: "your-app",
	"version"	: "0.1.0",
	"main"		: "main.js"	
}
```

2. main.js 内容：
``` javascript
const electron = require('electron');
// 控制应用生命周期模块
const {app} = electron;
// 创建本地浏览器窗口的模块
const {BrowserWindow} = electron;

// 指向窗口对象的一个全局引用，如果没有这个引用，
// 当javascript对象被垃圾回收时，该窗口会自动关闭
let win;

function createWindow(){
	// 创建一个新的浏览器窗口
	win = new BrowserWindow({width:800, height:600});
	// 装载应用的index.html页面
	win.loadURL('file://${__dirname}/index.html');
	
	// 打开开发工具页面
	win.webContents.openDevTools();
	
	// 当窗口关闭时调用方法
	win.on('closed', ()=>{
		// 解除窗口对象的引用，通常如果应用支持多窗口
		// 窗口对象会存放在数组中，窗口关闭时应删除数组对应元素
		win = null;
	});
	
	// 当Electron初始化并且创建了浏览器窗口，该方法被调用
	app.on('ready', createWindow);
	
	// 当所有的窗口被关闭时退出应用
	app.on('window-all-closed', ()=>{
		// 对于OS X系统，应用和相应菜单栏会一直激活，知道用户通过Cmd + Q显示退出
		if (process.platform !== 'darwin'){
			app.quit();
		}
	});
	
	app.on('activate', ()=》{
		// 对于OS X系统，当dock图标被点击会重新创建一个app窗口
		// 并且不会有其他窗口打开
		if (win === null){
			createWindow();
		}
	});
	
	// 在文件后面可以包含应用特定的由主程序运行的代码
	// 也可以把代码放在另一个文件中然后导入
}

```

3. index.html 内容：
``` html
<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <title>Hello World!</title>
  </head>
  <body>
    <h1>Hello World!</h1>
    We are using node <script>document.write(process.versions.node)</script>,
    Chrome <script>document.write(process.versions.chrome)</script>,
    and Electron <script>document.write(process.versions.electron)</script>.
  </body>
</html>
```

**运行你的应用**

一旦你建立了你的 main.js , index.html , 以及 package.json 文件，你也许会想要尝试在本地运行应用来测试它，确保应用是按照你预期的方式工作。

**electron-prebuilt**
electron-prebuilt 是一个 npm 的模块，它包含了一个预编译的Electron版本。

如果你已经通过 npm 将该模块全局安装了，那么你只需要在你应用的源代码目录西下运行下面的命令：

``` bash
electron .
```
如果你只是在本地安装了该模块，那么运行：

``` bash
./node_modules/.bin/electron .
```

手动下载Electron二进制包
如果手动下载了Electron二进制包，你可以通过执行其中包含的二进制文件来直接执行你的应用。

``` bash
# Windows
$ .\electron\electron.exe your-app\
# Linux
$ ./electron/electron your-app/
# OS X
$ ./Electron.app/Contents/MacOS/Electron your-app/
```

这里的 Electron.app 是Electron发布包的一部分，你可以在 这里 下载。

运行发布
在完成应用开发之后，你可以按照 应用发布 指导创建一个发布，然后执行打包的应用。

尝试例子
通过使用 atom/electron-quick-start 来克隆并且运行教程的代码。

注意 运行该例子需要在你的系统中安装 Git 以及 Node.js （它也包含了 npm )。

``` bash
# 克隆仓库
$ git clone https://github.com/electron/electron-quick-start
# 进入克隆的仓库
$ cd electron-quick-start
# 安装依赖然后运行应用
$ npm install && npm start
```

[原文](http://electron.atom.io/docs/tutorial/quick-start/)
