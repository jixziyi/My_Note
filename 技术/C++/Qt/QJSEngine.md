# QJSEngine

## 详细描述
QJSEngine 类提供了 JavaScript 代码执行环境

### 执行脚本
使用 `evaluate()` 来执行脚本
``` C++
QJSEngine myEngine;
QJSValue three = myEngine.evaluate("1 + 2");
```

evaluate() 返回一个 `QJSValue` 类型用于保存执行结果， `QJSValue` 类提供一些将结果转换为多种 C++ 类型的函数，如： `QJSValue::toString()`，`QJSValue::toNumber()`

下面代码展示怎样使用 `QJSValue::call()` 调用脚本中函数
``` C++
QJSValue fun = myEngine.evaluate("(function(a, b) { return a + b; })");
QJSValueList args;
args << 1 << 2;
QJSValue threeAgain = fun.call(args);
```

上面例子中，我们通过 string 将脚本传给 引擎，但通常我们读取文件内容并传递给 evaluate() 来加载脚本
``` C++
QString fileName = "helloworld.qs";
QFile scriptFile(fileName);
if (!scirptFile.open(QIODevice::ReadOnly))
  // handle error
QTextStream stream(&scriptFile);
QString contents = stream.readAll();
scriptFile.close();
myEngine.evaluate(contents, fileName);
```
这里我们传递了一个文件名作为第二个参数到 `evaluate()`。这并不影响脚本执行，第二个参数是存储在错误对象中用于调试的通用字符串

对于更大的功能，可能需要将代码和数据封装到模块中。模块是一个包含脚本代码、变量等的文件，并使用 export 语句描述其与应用程序其余部分的接口。在 import 语句的帮助下，模块可以使用其他模块的功能。这允许以安全的方式从较小的连接构建块构建脚本化应用程序。相反，使用 `evaluate()` 的方法会带来一个 `evaluate()` 调用中局部变量或函数意外污染全局对象并影响后续执行的风险。

``` JavaScript
export function sum(left, right) {
  return left + right;
}
```

``` C++
QJSValue module = engine.importModule(":/math.mjs");
QJSValue sumFunction = module.property("sum");
QJSValue valueModule = sumFunction.call(args);
qDebug() << valueModule.toString();
```

使用 `import` 关键字，模块还可以使用其他模块的功能
``` JavaScript
import { sum } from './sum.mjs';

export function addTwice(left, right)
{
    return sum(left, right) * 2;
}
```

### 脚本引擎设置
函数 `globalObject()` 的作用是返回与脚本引擎相关联的全局对象。全局对象的属性可以从任何脚本代码访问(即它们是全局变量)。通常，在执行"用户"脚本之前，需要向全局对象添加一个或多个属性来配置脚本引擎
``` C++
engine.globalObject().setProperty("myNumber", 1243);
QJSValue myNumberPlusOne = engine.evaluate("myNumber + 2");
qDebug() << myNumberPlusOne.toString();
```

向脚本环境添加自定义属性是提供特定应用程序脚本 API 的标准方法之一。通常，这些自定义属性是由 `newQObject()` 或 `newObject()` 函数创建的对象

### 脚本异常
`evaluate()` 能够抛出脚本异常，例如由于语法错误。此时，`evaluate()` 返回抛出的值，通常是 Error 对象。使用 `QJSValue::isError()` 来做异常检查

有关错误的详细信息，可以使用 `QJSValue::toString()` 获取错误消息，使用 `QJSValue::property()` 来查询错误对象的属性，有如下属性可以使用 name、message、fileName、lineNumber、stack

``` C++
if (errorResult.isError())
{
    qDebug() << "Uncaught exception at line"
              << errorResult.property("lineNumber").toInt()
              << ":" << errorResult.toString();
}
// Uncaught exception at line 10 : "ReferenceError: invalidFun is not defined"
```

### 脚本对象创建
使用 C++ `newObject()` 来创建一个 JavaScript 对象，这是脚本声明 `new Object()` 是等价的。可以使用 `QJSValue` 中的对象特定的功能来操作脚本对象，如：`QJSValue::setProperty()`。同样可以使用 `newArray()` 来创建 JavaScript 数组对象。

### QOBject 整合
使用 `newQObject()` 来包装 `QObject` 或子类指针。`newQObject()` 返回代理脚本对象，属性、子对象、QObject的信号和槽可用作代理对象的属性。不需要额外绑定代码，因为它是使用 Qt 元对象系统动态完成的。

``` C++
// class Say
class Say: public QObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QString about MEMBER m_about)

    Say(QObject *parent = nullptr): QObject(parent) {}

public slots:
    void hello();

private:
    QString m_about;
};

// main()
Say *say = new Say();
QJSValue sayScript = engine.newQObject(say);
engine.globalObject().setProperty("say", sayScript);
engine.evaluate("say.about = 'afd'");

qDebug() << say->property("about").toString();
script.property("hello").call();
```

使用 `newQMetaObject()` 封装 `QMetaObject`，将提供脚本表示的基于 `QObject` 类。`newQMetaObject()` 返回代理脚本对象；类的枚举值可用作代理对象的属性。

可以从脚本中调用暴露于元对象系统的构造函数 `Q_INVOKABLE`，以使用 `JavaScriptOwnership` 创建新的 QObject 实例。 staticMetaObject 静态元类型
``` C++
class MyObject: public QObject
{
  Q_OBJECT
  public:
    Q_INVOKABLE MyObject() {}
};
```

类的 staticMetaObject 可以暴露给 JavaScript，如下所示
``` C++
QJSValue jsMetaObject = engine.newQMetaObject(&MyObject::staticMetaObject);
engine.globalObject().setProperty("MyObject", jsMetaObject);
```

然后可以在javascript中创建类的实例：
``` C++
engine.evaluate("var myObject = new MyObject()");
```

**注意**：目前支持使用 `Q_OBJECT` 宏定义的类，不能将 `Q_GADGET` 类的 staticMetaObject 暴露给 JavaScript。

### 动态 `QObject` 属性
**不支持**动态 `QObject` 属性，下面的代码将不能工作
``` C++
QJSEngine engine;
QObject *myQObject = new QObject();
myQObject->setProperty("dynamicProperty", 3);

QJSValue myScriptQObject = engine.newQObject(myQObject);
engine.globalObject().setProperty("myObject", myScriptQObject);

qDebug() << engine.evaluate("myObject.dynamicProperty").toInt();
```

## 扩展
`QJSEngine` 提供了一个兼容 ECMAScript 实现。默认情况下，日志等熟悉的实用程序不可用，但可以通过 `installExtensions()` 函数安装它们。
``` C++
installExtensions(QJSEngine::TranslationExtension | QJSEngine::ConsoleExtension);
```

## 其他
在 QML 中 QQmlApplicationEngine 继承自 QJSEngine
``` C++
class Q_QML_EXPORT QQmlApplicationEngine : public QQmlEngine

class Q_QML_EXPORT QQmlEngine : public QJSEngine
```

