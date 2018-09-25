# Express

Express 是基于Node.js平台，快速、开放、极简的web开发框架。

<!--more-->

**Express应用生成器**

``` bash
npm install express-generator -g
express myapp
cd myapp
npm install
set DEBUG=myapp & npm start # port:3000
```

**Express路由**
路由定义有以下结构组成：app.Method(path, handler)
``` javascript
app.get('/:id',function(req, res){
  res.send('Hello World!');
}
```

**Express静态文件**
利用express.static可以方便的托管静态文件，例如：图片，css，javascript等。
``` javascript
//所有静态文件路径都是相对存放路径的，可以指定多个目录
//访问 http://localhost:3000/css/style.css
app.use(express.static('public'));
app.use(express.static('files'));
//也可以指定虚拟路径 http://localhost:3000/static/css/style.css
app.use('/static', express.static('public'))
```
