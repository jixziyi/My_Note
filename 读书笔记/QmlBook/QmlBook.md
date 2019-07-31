# QmlBook

## 第01章 Qt5 概述
教程侧重于讲解新的 Qt Quick 开发技巧，在讲解 Qt Quick 扩展内容时会涉及部分 Qt C++ 内容

## 第03章 Qt Creator 集成开发环境

### 3.7 快捷键 Shortcuts
- `Ctrl+ B`：构建项目
- `Ctrl + R`：运行项目
- `Ctrl + Tab`：切换已打开文档
- `Ctrl + k`：打开定位器
- `ESC`：返回
- `F2`：查找对应的符号解释
- `F4`：在头文件与源文件之间切换


## 第04章 QML 快速入门 Quick Starter
QtQuick中非常重要的概念，输入处理与可视化显示分开。
你的交互区域可以比你显示的区域大很多。

### 4.1 QML 语法 QML Syntax
- `import` 声明导入一个指定的模块版本。一般导入 `QtQuick 2.0` 来作为初始元素的引用
- 使用 `//` 单行注释，使用 `/**/` 多行注释
- 每一个 QML 文件都需要一个根元素，就像 `HTML` 一样
- 一个元素使用它的类型声明，然后使用 `{}` 进行包含
- 元素拥有属性，按照 `name: value` 格式来赋值
- 任何在 QML 文档中的元素都可以通过使用它们的 id 进行访问，(id 是一个任意的标识符
- 元素可以嵌套，这意味着一个父元素可以拥有多个子元素，子元素可以通过访问 `parent` 关键字来访问它们的父元素

**一个比较好的命名方式，将你的根元素对象命名为 root `id: root`**

#### 4.1.1 属性 Properties
- 元素使用它们的元素类型名进行声明，使用它们的属性或者创建自定义属性来定义。
- 一个属性对应一个值
- 一个属性有一个类型定义并需要一个初始值

``` QML
Text {
  id: thisLable
  x: 24; y: 16
  height: 2 * width
  property int times: 24
  property alias anotherTimes: thisLabel.times
  focus: true
  color: focus?"red":"black"
}
```

#### 4.1.2 脚本 Scripting


### 4.2 基本元素 Basic Elements
基础可视化元素 Item (基础元素对象)、Rectangle(矩形框)、Text(文本框)、Image(图像)、Mouse Area(鼠标区域)

#### 4.2.1 基础元素对象 Item Element
- Item 是所有可视化元素的基础对象，所有其它可视化元素都继承自 Item。
- 它本身不会有任何绘制操作，但定义了所有可视化元素共有的属性
- Item 通常被用来作为其它元素的容器使用，类似于 HTML 语言中的 div 元素

- Geometry 集合属性
  - x/y 定义元素左上角位置
  - width/height 定义元素的显示范围
  - z 定义元素间重叠顺序
- Layout handling 布局操作
  - anchors(锚定)，包括 left/right/top/bottom/vertical center(垂直居中)/horizontal center(水平居中)/margins(间距)
- Key handling 按键操作
  - 附加 key(按键)/keyNavigation(按键定位) 属性来控制按键操作，处理输入焦点 focus 可用
- Transformation 转换
  - scale(缩放) 和 rotate(旋转) 转换，通用的 x/y/z 属性列表转换 transform，旋转基点设置 transformOrigin
- Visual 可视化
  - opacity(不透明度)
  - visible(是否可见)
  - clip(裁剪)，限制元素边界
  - smooth(平滑)，提高渲染质量
- State definition 状态定义
  - states(状态列表属性)，提供了元素当前所支持的状态列表，当前属性的改变也可以使用 transitions(转变) 属性列表来定义状态转变动画

#### 4.2.2 矩形框元素 Rectangle Element
一个矩形如果没有定义 width/height 将不可见

- border
  - color 边界颜色
  - width 边界宽度
- gradient 渐变色
  - GradientStop(倾斜点) 的颜色标记了颜色的位置
- radius 圆角

#### 4.2.3 文本元素 Text Element
一个没有设置宽度或者文本的文本元素（Text Element）将不可见，默认的初始宽度是0。

- text 文本
- font.family 字体
- font.pixelSize 大小
- font.weight : enumeration 粗细
- horizontalAlignment 水平对齐
- verticalAlignment 垂直对齐  `Text.AlignTop`
- style 外框效果 浮雕/凹陷 `style: Text.Sunken`
- styleColor 
- elide 长文字省略显示 `elide: Text.ElideMiddle`
- wrapMode 换行显示，需要先设置宽度 `Text.WordWrap`

#### 4.2.4 图像元素 Image Element
一个图像元素能够显示不同格式的图像

- source 提供图像文件的链接信息
- fillMode 文件模式，能够控制元素对象的大小调整行为 `fillMode: Image.PreserveAspectCrop`

#### 4.2.5 鼠标区域元素 MouseArea Element
矩形的非可视化元素对象，你可以通过它来捕捉鼠标事件。
当用户与可视化端口交互时，mouseArea通常被用来与可视化元素对象一起执行命令。

#### 4.2.6 滚动条 ScrollView
- verticalScrollBarPolicy 是否显示滚动栏 `Qt.ScrollBarAsNeeded`

#### 4.2.7 拖拽 Flickable 
``` QML
Flickable {
    width: 200; height: 200
    contentWidth: image.width; contentHeight: image.height

    Image { id: image; source: "bigImage.png" }
}
```

### 4.3 组件 Components
组件是可以重复使用的元素，三次使用相同的代码描述一个用户界面最好可以抽象为一个组件

QML 提供了几种不同的方式来创建组件。最常见，一个文件就是一个基础组件。

- 只有根级目录的属性才能够被其他文件的组件所访问
- QML alias(别名) 功能，可以将内部嵌套的 QML 元素的属性导出到外面使用
- 可以使用基础元素 Item 作为根元素，可以防止用户改变自定义设计，而且可以提供更多相关控制的 API

### 4.4 简单的转换 Simple Transformations
转换操作改变了一个对象的几何形状

- QML 元素对象通常能够被平移、旋转、缩放


### 4.5 定位元素 Positioning Element
有一些 QML 元素被用于放置元素对象，他们被称为定位器，QtQuick 提供了 Row/Column/Grid/Flow用来做定位器


