C++和QML混合编程：QML中调用C++

## QML 中注册 C++
- qmlRegisterType
``` C++
qmlRegisterType("an.qt.Message", 1, 0, "Message");
```

- rootContext
``` C++
qmlRegisterType<QtxTester>();
engine.rootContext()->setContextProperty("$data", &data);
```

## 使用属性
- 使用 Q_PROPERTY() 宏
	- Q_PROPERTY() 宏在所有 QObject 派生类中使用
``` C++
#include <QObject>

class AuthorClass: public QObject 
{
	Q_OBJECT
	Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged);
	
public:
	AuthorClass(QObject *parent = nullptr): QObject(parent) {};
	virtual ~AuthorClass();
	QString author() const { return m_author; }
	void setAuthor(cosnt QString &author) { m_author = author; emit authorChanged(); }
	
signals:
	void authorChanged();
	
private:
	QString m_author;
}
```

## QML 中调用 C++ 方法
- 使用 Q_INVOKABLE() 宏
- 直接定义函数为槽函数
``` C++
// 使用 Q_INVOKABLE() 宏
public:
	Q_INVOKABLE bool postMessage(const QString &);

// 直接定义函数为槽函数
public slots:
	bool postMessage(const QString &);
```

## 使用枚举类型
在 C++ 中需要使用到 Q_ENUMS() 宏
``` C++
Q_ENUMS(MESSAGE_COLOR)

enum MESSAGE_COLOR {
	MESSAGE_COLOR_YELLOW,
	MESSAGE_COLOR_RED,
	MESSAGE_COLOR_BLUE
}
```

## 使用信号槽
直接将 C++ 函数定义为槽函数，供 QML 调用
``` QML
// C++ 定义 signal 
// void sendresfresh(QDate sendvalue);
Connections {
	target: $data
	onSendresfresh: {
		console.log("C++ signal to QML")
	}
}
```

## C++ 使用 QML对象成员
使用 QQmlProperty 的 read() / write() 或 QObject::setProperty() / QObject::Property()
``` C++
QQmlApplicationEngine engine;
QObject *object = engine.rootObjects().at(0)
qDebug() << "Property value:" << QQmlProperty::read(object, "someValue").toInt();
```


