# Vue + Element-UI 环境搭建

1. 安装基础环境
``` bash
# install cnpm
npm install -g cnpm --registry=https://registry.npm.taobao.org

# install webpack
cnpm install -g webpack

# install vue-Cli
cnpm install -g vue-cli

# install vue-init
cnpm install -g @vue/cli-init
```

2. 初始化vue页面
``` bash
# init vue
vue init webpack vueadmin

# run vue admin
cd vueadmin
cnpm install
cnpm run dev
```

3. 安装第三方库
``` bash
# install axios
cnpm install --save axios

# install element-ui
cnpm install --save element-ui

# install font-awesome
cnpm install --save font-awesome

# install sass
cnpm install --save-dev node-sass
cnpm install --save-dev sass-loader

## npm install stylus --save-dev
## npm install stylus-loader css-loader style-loader --save-dev

# install mock.js
cnpm install --save-dev mockjs

# axios-mock-adapter 能拦截http请求的同时模拟需要的数据
cnpm install --save-dev axios-mock-adapter

# install normalize.css 清除浏览器默认样式
npm install normalize.css --save-dev
```

4. 更新 element-ui 主题

访问 [ElementUI](https://elementui.github.io/theme-chalk-preview/#/zh-CN)
 下载主题，放到 src\assets\theme 文件夹中

5. 修改main.js文件，增加引用

