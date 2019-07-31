# Qt 异常处理

## 名词解释
1. QQuickView 提供了一个窗体用于显示UI
2. QQuickEngine 提供QML运行环境
3. QQuickWindow 显示窗体，以及对item对象的管理及用户交互

## Qt开发QtQuick程序在编译时报错：0x00007FFE4E60BB6B (ig9icd64.dll) 处有未经处理的异常: 0xC0000005: 读取位置 0xFFFFFFFFFFFFF
这个问题最近困扰的好久，查遍百度都找不到解决方案，一直以为是显卡驱动的问题，因为编译显示ig9icd64.dll这个库是属于intel显卡驱动的一个渲染库。但是更新之后还是无效，就去谷歌搜索，找到了这个链接：QtBugReports里面针对这个问题的描述，本人亲测方法好用，现在记录一下方便其他开发者查询使用：

1. 在工程的Main函数第一行增加下述代码即可：
  `QQuickWindow::setSceneGraphBackend(QSGRendererInterface::Software);`
2. 根据Qt官方bugreports的说法，这是硬件驱动渲染出了问题，可以开启软件渲染来回避这个报错的。

## QtCreator：error LNK2001: 无法解析的外部符号
1. 没有写 Q_OBJECT，或者在 pro文件中没有包含相应的模块。
2. 如果你发现，同样的代码在其他头文件就能编译通过，而在某个头文件出偏偏编译错误。有时修改完 pro文件以后，也会出现这种错误。
  - 关闭 QCreator
  - 删除debug-release，makefile，makefiledebug等所有编译产生的文件，然后重新编译就会通过了

## 设置应用程序图标
设置应用程序图标
1. 创建一个图标格式的文件，可以网上在线将普通的图形格式转成.ico 格式的图标文件 http://www.faviconico.org/
2. 将转换好的图标文件放到源码目录，就是.Pro所在的文件夹啦
3. 在.pro项目文件中添加一行代码：RC_ICONS = myico.ico

## 鼠标滑动效果
``` QML
hoverEnabled: true
onEntered: {
    parent.opacity = 0.7
}
onExited: {
    parent.opacity = 1
}
```

## QT ChartView
- 必须将默认 `include <QGuiApplication>` 替换为 `include <QApplication>`，pro文件中添加 `QT += widgets`
- 如果提示异常，清除项目后重新编

### ChartView legend 错误 legend does not have members(M17)
``` QML
ChartView {
  legend {
    visible: false
  }
}
```

## 无法打开包括文件<QApplication> No such file or directory  这一问题
解决办法，使用QApplication时必须在项目pro文件中添加一句 `QT += widgets`

## QQmlListModel
- ListView 绑定数据使用 QQmlListModel 类型
- 获取数组长度使用 object.count 而不是 length
- 获取 item 使用 object.get(index) 而不能使用 object[index]

## error c2243:"类型转换" 转换存在，但无法访问
c++ 默认的是 private 继承，无法进行转换，检查一下 `class` 是否继承后面都有一个 public

## QML 后面元素会覆盖之前的元素，写时注意对象创建的先后循序

## QML中 C++ signal 链接 JavaScript 方法
``` QML
$backEnd.onDataChange.connect(dataChange)

function dataChange() {

}
```

