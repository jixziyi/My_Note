# Qt 学习之路 2

## 跨平台 GUI 实现策略
- API 映射：界面库使用同一套 API，其映射到不同的底层平台上面。代表 wxWidgets
- API 模拟：应用程序无需重新编译，即可运行到特定的平台上。不同平台的有差异 API，将使用工具库自己的代码用于模拟出来。代表 wine / DirectX
- GUI 模拟：任何平台都提供了图形绘制函数，例如画点、画线、画面等。有些工具库利用这些基本函数，在不同绘制出自己的组件，这就是 GUI 模拟。GUI 模拟的工作量无疑是很大的，因为需要使用最基本的绘图函数将所有组件画出来；并且这种绘制很难保证和原生组件一模一样。但是，这一代价带来的优势是，可以很方便的修改组件的外观 - 只要修改组件绘制函数即可。很多跨平台的 GUI 库都是使用的这种策略，例如 gtk+（这是一个 C 语言的图形界面库。使用 C 语言很优雅地实现了面向对象程序设计。不过，这也同样带来了一个问题——使用大量的类型转换的宏来模拟多态，并且它的函数名一般都比较长，使用下划线分割单词，看上去和 Linux 如出一辙。gtk+ 并不是模拟的原生界面，而有它自己的风格，所以有时候就会和操作系统的界面格格不入。）代表 Swing / Qt

## Qt 版本
[Qt官方网站](#https://www.qt.io/developers/) 下载页面存在几个版本：
- Qt SDK：包含了Qt库以及Qt开发工具（IDE、i18n 等工具），是一套完整的开发环境
- Qt Library：仅包含Qt库
- Qt Creator：基于Qt构建的轻量级IDE

## Qt 模块
Qt 5 模块分为 Essentials Modules (基础模块) 和 Add-on Modules (扩展模块) 两部分

### Qt 基础模块
- `Qt Core`, 提供核心非 GUI 功能，所有模块都需要这个模块。包含：动画框架、定时器、各个容器类、时间日期类、事件、IO、JSON、插件机制、智能指针、图形(矩形、路径等)、线程、XML等。通过`<QtCore>`头文件引入。
- `Qt Gui`，提供 GUI 程序的基本功能，包括与窗口系统的集成、事件处理、OpenGL 和 OpenGL ES 集成、2D图像、字体、拖放等。
- `Qt Multimedia`，提供视频、音频、收音机、摄像头等功能。通过`<QtMultimedia>`引入，需要在pro文件中添加 `Qt += multimedia`。
- `Qt Network`，提供跨平台网络功能。通过`<QtNetwork>`引入，需要在pro文件中添加 `QT += network`。
- `Qt Qml`，提供QML(一种脚本语言，也提供JavaScript的交互机制)使用C++ API。通过`<QtXml>`引入，需要在pro文件中添加 `QT += qml`。
- `Qt Quick`，允许在 Qt/C++ 程序中嵌入 Qt Quick (一种基于Qt的高度动画的用户界面，适合于移动平台开发)。通过`<QtQuick>`引入，需要在pro文件中添加 `QT += quick`。
- `Qt SQL`，允许使用SQL访问数据库。通过`<QtSql>`引入，需要在pro文件中添加 `QT += sql`。
- `Qt Test`，提供Qt程序的单元测试功能。通过`QtTest`，引入，需要在pro文件中添加 `QT += testlib`。
- `Qt Webkit`，基于 Webkit2 的实现以及一套全新的 QML API。

### Qt 扩展模块
- `Qt 3D`，提供声明式语法，在Qt程序中可以简单地嵌入3D图像。
- `Qt Bluetooth`，提供用于访问蓝牙无线设备的C++和QML API。
- `Qt Contacts`，用于访问地址簿或者联系人数据库的C++和QML API。
- `Qt Concurrent`，封装了底层线程技术的类库，方便开发多线程程序。
- `Qt D-Bus`，用于Unix平台，利用D-Bus协议进行进程间交互。
- `Qt Graphical Effects`，提供一系列用于实现图像特效的库，如模糊、锐化等。
- `Qt Image Formats`，支持图片格式的一系列插件，包括TIFF、MNG、TGA和WBMP。
- `Qt JS Backend`，V8引擎的移植，仅供QtQml模块内部使用。
- `Qt Location`，提供定位机制、地图和导航技术、位置搜索等功能的QML和C++ API。
- `Qt OpenGL`，方便在Qt应用程序中使用OpenGL。
- `Qt Organizer`，使用 QML 和 C++ API 访问组织事件（organizer event）。organizer API 是 Personal Information Management API 的一部分，用于访问 Calendar 信息。通过 Organizer API 可以实现：从日历数据库访问日历时间、导入 iCalendar 事件或者将自己的事件导出到 iCalendar。
- `Qt Print Support`，提供对打印功能的支持。
- `Qt Publish and Subscribe`，为应用程序提供对项目值的读取、导航、订阅等的功能。
- `Qt Quick 1`，从 Qt 4 移植过来的 QtDeclarative 模块，用于提供与 Qt 4 的兼容。如果你需要开发新的程序，需要使用 QtQuick 模块。
- `Qt Script`，提供脚本化机制。这也是为提供与 Qt 4 的兼容性，如果要使用脚本化支持，请使用 QtQml 模块的 QJS* 类。
- `Qt Script Tools`，为使用了 Qt Script 模块的应用程序提供的额外的组件。
- `Qt Sensors`，提供访问各类传感器的 QML 和 C++ 接口。
- `Qt Service Framework`，提供客户端发现其他设备的服务。Qt Service Framework 为在不同平台上发现、实现和访问服务定义了一套统一的机制。
- `Qt SVG`，提供渲染和创建 SVG 文件的功能。
- `Qt System Info`，提供一套 API，用于发现系统相关的信息，比如电池使用量、锁屏、硬件特性等。
- `Qt Tools`，提供了 Qt 开发的方便工具，包括 Qt CLucene、Qt Designer、Qt Help 以及 Qt UI Tools 。
- `Qt Versit`，提供了对 Versit API 的支持。Versit API 是 Personal Information Management API 的一部分，用于 QContacts 和 vCard 以及 QOrganizerItems 和 iCalendar 之间的相互转换。
- `Qt Wayland`，仅用于 Linux 平台，用于替代 QWS，包括 Qt Compositor API（server）和 Wayland 平台插件（clients）。
- `Qt WebKit`，从 Qt 4 移植来的基于 WebKit1 和 QWidget 的 API。
- `Qt Widgets`，使用 C++ 扩展的 Qt Gui 模块，提供了一些界面组件，比如按钮、单选框等。
- `Qt XML`，SAX 和 DOM 的 C++ 实现。该模块已经废除，请使用 QXmlStreamReader/Writer。
- `Qt XML Patterns`，提供对 XPath、XQuery、XSLT 和 XML Schema 验证的支持。

## QML 和 QtQuick 2
QML (Qt Meta Language / Qt Modeling Language)是一种 JavaScript 的声明式语言，作为 C++ 语言的一种替代，而 Qt Quick 就是使用 QML 构建的一套类库。

在 Qt 5 中，QML 有了长足进步，并且同 C++ 并列成为 Qt 的首选编程语言。

QML 文档描述了一个对象树，QML 元素包含那了其构造块、图形元素(矩形、图片等)和行为(动画、切换等)。这些 QML 元素按照一定的嵌套关系构成复杂的组件，供用户交互。

- 首先，使用 Qt Creator 创建一个 `Qt Quick Application`
- 一个 QML 文档分为 `import` 和 `declaration` 两部分，前者用于引入文档中所需要的组件(类库、JavaScript 文件或其他 QML 文件)，后者用于声明文档中的 QML 元素
- 每一个 QML 有且只有一个根元素


