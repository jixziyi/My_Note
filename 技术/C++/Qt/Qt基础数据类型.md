# Qt 基础数据类型

## QString
- arg
``` C++
// 字符串拼接，输出：AA-BB-CC
QString rlt = "%1-%2-%3".arg("AA", "BB", "CC");

// 补零，输出：00002
QString rlt = "%1".arg(2, 5, 10, QLatin1Char('0'));

// 进制转换，输出：Af
QString rlt = "%1".arg(10, 0, 16);
```

## QByteArray
``` C++
// QString to QByteArray
QString str("hello");
QByteArray bytes = str.toUtf8();

QString str("hello");
QByteArray bytes = str.toLatin1();

// QByteArray to QString
QByteArray bytes("hello world");
QString str = bytes;
```

## 正则
Qt 使用 QRegExp 来封装正则表达式。如：`QRegExp rx("^[0-9]+(\\.\\d+)?$")`
``` C++
QRegExp rx(tr("(\\w*:){3}(\\w*:\\w*)+"));
int pos(0)

while((pos = rx.indexIn(str, pos)) != -1)
{
    strList.push_back(rx.capturedTexts().at(0));
    pos += rx.matchedLength();
}
```


