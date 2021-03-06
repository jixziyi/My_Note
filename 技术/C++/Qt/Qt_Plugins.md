# Qt Plugins

Qt 提供两种 API 用于创建插件
- 一种高级 API，用于将扩展名写入 Qt 本身：自定义数据库驱动程序、图像格式、文本编解码器、自定义样式等。
- 一种用于扩展 Qt 应用程序的低级 API。

由于较高级别的 API 构建在低级别的 API 上，因此一些问题对于两者都很常见。

## 低级 API：扩展 Qt 应用程序
不仅 Qt 本身，Qt 应用程序同样能通过插件扩展。这需要应用使用 `QPluginLoader` 来检测和加载插件。此时，插件可以提供任意功能，并且不限于数据库驱动程序、图像格式、文本编解码器、自定义样式等。

通过插件使应用程序可扩展步骤：
- 定义一组用于插件通信的接口(仅具有纯虚函数的类)
- 使用 `Q_DECLARE_INTERFACE()` 宏告诉 Qt 元对象系统有关接口的信息
- 在应用程序中使用 QPluginLoader 来加载插件
- 使用 `qobject_cast()` 来测试插件是否实现给定的接口

编写插件步骤：
- 声明一个从 QObject 继承的插件类，以及插件想要提供的接口
- 使用 Q_INTERFACES() 宏告诉 Qt 的元对象系统有关接口的信息
- 使用 Q_PLUGIN_METADATA() 宏导出插件
- 使用合适的 .pro 文件构建插件
