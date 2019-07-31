# Qt 基础
Qt 是一个用标准 C++ 编写的跨平台开发类库，它对标准 C++ 进行了扩展，引入了元对象系统、信号与槽、属性等特性

## Qt 元对象和属性系统详解

### Qt 的元对象系统
Qt 的元对象系统 Meta-Object System 提供了对象之间通信的信号与槽机制、运行时类型信息和动态属性系统。

元对象系统由以下三个基础组成
- QObject 类是所有使用元对象系统的类的基类
- 在一个类的 private 部分声明 Q_OBJECT 宏，使得类可以使用元对象的特性，如动态属性、信号与槽
- MOC (元对象编译器) 为每个 QObject 的子类提供必要的代码来实现元对象系统的特性

除了信号与槽机制外，元对象还提供如下一些功能：
- QObject::metaObject() 函数返回类关联的元对象，元对象类 QMetaObject 包含了访问元对象的一些接口函数，例如：
	QMetaObject::className() 函数可以在运行时返回类的名称字符串
``` C++
QObject *obj = new QPushButton；
obj->metaObject()->className();	// 返回 "QPushButton"
```
- QMetaObject::newInstance() 函数创建类的一个新的实例
- QObject::inherits(const char \*className) 函数判断一个对象实例是否是名称为 className 的类或 QObject 的子类的实例，例如：
``` C++
QTimer *timer = new QTimer;	// QTimer 是 QObject 的子类
timer->inherits("QTimer");	// 返回 true
timer->inherits("QObject");	// 返回 true
timer->inherits("QAbstractButton");	// 返回 false
```
- QObject::tr() 和 QObject::trUtf8() 函数可以翻译字符串，用于多语言界面设计，后续章节会专门介绍多语言界面设计
- QObject::setProperty() 和 QObject::property() 函数用于通过属性名称动态设置和获取属性值

对于 QObject 及其子类，还可以使用 qobject_cast() 函数进行动态投射 dynamic cast。投射失败，则返回指针为 NULL
``` C++
QObject *obj = new QMyWidget;
QWidget *widget = qobject_cast<QWidget *>(obj);
```

### 属性系统
- Qt 提供一个 Q_PROPERTY() 宏可以定义属性，它也是基于元对象系统实现的，使用格式如下：
``` txt
// MEMBER 指定一个成员变量与属性关联，成为可读可写的属性，无需再设置 READ 和 WRITE
Q_PROPERTY(type name (READ getFunction [WRITE setFunction] | MEMBER memberName [(READ getFunction | WRITE setFunction)]) 
	[RESET resetFunction] 	// 用于指定一个设置属性默认值的函数
	[NOTIFY notifySignal] 	// 用于设置一个信号，当属性变化是发出信号
	[REVISION int]	
	[DESIGNABLE bool]		// 表述属性是否在 Qt Designer 中可见，默认 true
	[SCRIPTABLE bool]
	[STORED bool]
	[USER bool]
	[CONSTANT]				// 表示一个常数，对于一个对象实例，READ 指定的函数返回值是常数，不能有 WRITE 和 NITIFY 关键字
	[FINAL]					// 表示定义的属性不能被子类重载
)
```

``` C++


```
