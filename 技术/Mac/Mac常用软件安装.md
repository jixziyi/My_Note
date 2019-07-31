# Mac 常用软件安装

## node / nvm
``` bash
# 1. 卸载系统现有 node 和 npm
npm ls -g --depth=0 # 查看已经安装在全局的模块，以便删除这些全局模块后再按照不同的 node 版本重新进行全局安装
sudo rm -rf /usr/local/lib/node_modules # 删除全局 node_modules 目录
sudo rm /usr/local/bin/node # 删除 node
cd  /usr/local/bin && ls -l | grep "../lib/node_modules/" | awk '{print $9}'| xargs rm # 删除全局 node 模块注册的软链

# 2. 安装 nvm
curl -o- https://raw.githubusercontent.com/creationix/nvm/v0.33.8/install.sh | bash

# or Wget:
wget -qO- https://raw.githubusercontent.com/creationix/nvm/v0.33.8/install.sh | bash

# 3. 配置环境变量
# 3.1 系统根目录编辑.bash_profile文件
cd ~
# 3.2 添加内容
export NVM_DIR="$HOME/.nvm"
[ -s "$NVM_DIR/nvm.sh" ] && . "$NVM_DIR/nvm.sh"
# 3.3 更新到系统
source .bash_profile

# 4. 安装 node
nvm install stable # 安装最新稳定版 node，现在是 5.0.0
nvm install 4.2.2 # 安装 4.2.2 版本
nvm install 0.12.7 # 安装 0.12.7 版本
nvm use 4 # 切换至 4.2.2 版本
npm install -g mz-fis # 安装 mz-fis 模块至全局目录，安装完成的路径是 /Users/<你的用户名>/.nvm/versions/node/v0.12.7/lib/mz-fis
nvm use 0 # 切换至 0.12.7 版本
npm install -g react-native-cli #安装 react-native-cli 模块至全局目录，安装完成的路径是 /Users/<你的用户名>/.nvm/versions/node/v4.2.2/lib/react-native-cli
nvm alias default 0.12.7 #设置默认 node 版本为 0.12.7

# 5. 其他指令
# 查看已安装的版本：
$ nvm ls
# 查看可以安装的版本：
$ nvm ls-remote
# 安装指定的版本：
$ nvm install <version> # 指定的版本将会直接安装在 nvm 程序所在的目录下。
# 删除指定的版本：
$ nvm uninstall <version>
# 使用选定的版本：
$ nvm use <version>
```



