# Qt 异常处理

## QProcess 无法启动应用程序
必须使用绝对路径
``` C++
QString path = QApplication::applicationDirPath().append("/XClientEditor");
```




