# Qt 发布

## Win
### quick2 程序
windeployqt QTX.app -qmldir=../QTX -dmg

Qt 程序在 Windows 下的发布
本文讨论在 Windows 平台下编译成功的 Qt 程序，如何在未配置 Qt 开发环境的 Windows 平台下独立运行的方法。

经过验证发现，在 Ubuntu 平台下编译成功的程序可在未安装 Qt 开发环境下的 Ubuntu16.04 中运行，所以，本文仅讨论，在 Windows 平台下编译成功的 Qt 程序，在未配置 Qt 开发环境的 Windows 平台下独立运行的方法。

## 编译模式选择
如若想要发布程序，在 IDE 中编译一定要选择 release 而不是 debug，编译成 release 版本相比于 debug 版本，程序体积「可执行文件和 dll 文件」大大减小；

编译模式选择
## 集成所需 dll 文件及其他依赖库
编译为 release 版本之后，找到生成的目录，其中只有 exe 扩展名的可执行文件是有用的。

编译生成目录
直接打开可执行文件，会提示找不到 dll 文件，解决方法如下：

### 使用 Qt 自带的 windeployqt.exe 寻找依赖文件
在 cmd 中，运行如下命令：

<Qt目录>\Qt5.5.1\5.5\mingw492_32\bin\windeployqt.exe   <*.exe>
程序会找到该可执行程序所需的所有依赖文件，并集成进该可执行文件所在的目录：

windeployqt 寻找依赖
有时程序会提示找不到所需的 gcc.exe，只需要将随 Qt 安装的 mingw 的 bin 目录添加到系统的环境变量中即可。之后执行可执行文件即可成功运行。

### 手动集成所需的依赖文件
这里，我们可以用 Process Explore 来获取所依赖的 dll 文件「Dependency Walker软件也是不错的选择」

打开 procexp.exe，选择菜单 -> View -> Lower Pane View ->DLLs 勾选此选项，显示 dll 窗口。

在 Qt Creater 中，调试运行要发布的程序，在 Process Explore 中，找到该 exe 文件并选中，在下面就看到依赖的 dll 了。

Process Explore寻找依赖

Process Explore寻找依赖
Dependency Walker寻找依赖

Dependency Walker寻找依赖
系统目录下的，一般不用关心，按 Path 排序，寻找 Qt 目录及 mingw 目录下的 dll 文件，将这些 dll 拷贝至发布程序目录下。

以 mingw 版 Qt 为例「VS版本安装目录有些许不同」，dll 文件在 Qt 安装目录下：

<Qt安装目录>\Qt5.5.1\5.5\mingw492_32\bin
找到所有所需的 dll 文件，复制到要发布程序的目录下

Qt运行目录
例如，本程序需要如下依赖：

该程序所需依赖
### 打包为单个可执行文件
打包工具，这里选用 Enigma Virtual Box，运行软件，选择发布程序的可执行文件路径以及生成文件的路径，左下角的“添加”按钮添加所有的 dll 文件，不包含刚才选择的 exe 文件。点击右下角的「文件选项」，选中「启用文件虚拟化」以及「压缩文件」，如图所示：

Enigma Virtual Box的使用
最后点击右下角的“执行封包”，生成的 exe 文件的容量小了很多，并且这是一个纯粹的「绿色软件」，直接复制就能在任何存储介质上运行了。

### Qt5 主要依赖链接库说明
#### Qt 模块库
Qt5Core.dll #QT核心库
Qt5Gui.dll #QT Gui库
Qt5Widgets.dll #QT Widgets库，QT 5中GUI程序基本都需要此dll
还有其他程序用到的Qt5XXX.dll

#### ICU 依赖库「International Component for Unicode，Unicode工具」
icudt51.dll
icuin51.dll
icuuc51.dll

#### Qt 插件库「新增库，路径必须正确」
根据不同的程序，需要不同的插件库。例如 QT_DIR/plugins/*/*.dll，需要将 platforms/*.dll , accessible/*.dll 的文件结构保留，放在你所编译的程序所在目录，例如：

plugins/platforms/qwindows.dll
plugins/accessible/qtaccessiblewidgets.dll

#### EGL 依赖库，为 OpenGL, OpenGLes 提供接口
libEGL.dll
libGLESv2.dll

#### mingw 依赖库「msvc 编译则无需这些库」
libgcc_s_dw2-1.dll
libstdc++-6.dll
libwinpthread-1.dll

#### VC 运行库「mingw 编译则无需这些库」
msvcr110.dll「对应VS2012」
msvcp110.dll

## Mac
- 设置环境变量
export PATH="/Users/apple/Qt5.8.0/5.8/clang_64/bin:$PATH"

- 设置执行权限
chmod 755 fileName.sh

### widgets 程序
macdeployqt /Users/Ocean/Desktop/build-untitled-Desktop_5_5_1_64bit-Release/QTX.app -dmg

### quick2 程序
macdeployqt QTX.app -qmldir=../QTX -dmg
`qmldir` 指定 QML 文件所在文件夹路径


- app 文件结构
``` txt
xxx.app
    - Contents
        - Frameworks
        - MacOS
            - xxx
        - Resources
        - PlugIns
        - SharedFrameWorks
        - info.plist
        - PkgInfo
```

- otool 使用
``` bash
otool -L xxx.dylib
```

- 引用路径修改
``` bash
install_name_tool -change /usr/local/opt/opencv@3/lib/libopencv_core.3.4.dylib @executable_path/libopencv_core.3.4.dylib /df/StationX.app/Contents/MacOS/XClientEditor
install_name_tool -change /usr/local/opt/opencv@3/lib/libopencv_imgproc.3.4.dylib @executable_path/libopencv_imgproc.3.4.dylib /df/StationX.app/Contents/MacOS/XClientEditor
install_name_tool -change /usr/local/opt/opencv@3/lib/libopencv_imgcodecs.3.4.dylib @executable_path/libopencv_imgcodecs.3.4.dylib /df/StationX.app/Contents/MacOS/XClientEditor

install_name_tool -change /Users/df/Qt5.4.2/5.4/clang_64/lib/QtWidgets.framework/Versions/5/QtWidgets @executable_path/../Frameworks/QtWidgets.framework/Versions/5/QtWidgets /df/StationX.app/Contents/MacOS/XClientEditor
install_name_tool -change /Users/df/Qt5.4.2/5.4/clang_64/lib/QtGui.framework/Versions/5/QtGui @executable_path/../Frameworks/QtGui.framework/Versions/5/QtGui /df/StationX.app/Contents/MacOS/XClientEditor
install_name_tool -change /Users/df/Qt5.4.2/5.4/clang_64/lib/QtCore.framework/Versions/5/QtCore @executable_path/../Frameworks/QtCore.framework/Versions/5/QtCore /df/StationX.app/Contents/MacOS/XClientEditor
```

- 系统文件不需要修改路径
```
/System/Library/ ...
/usr/lib/ ...
```












