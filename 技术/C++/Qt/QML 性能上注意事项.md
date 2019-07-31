# QML 性能上注意事项

## 事件注意事项
努力让渲染引擎实现一致的 60 帧每秒刷新率
- 尽可能使用异步，事件驱动的编程
- 使用工作线程进行重大处理
- 永远不要手动调整事件循环
- 在阻塞功能中，每帧不要花费超过几个毫秒

## 分析
使用 Qt Creator 附带的 QML 分析器

## JavaScript 代码
大多数 QML 应用程序将以动态函数，信号处理程序和属性绑定表达式的形式使用大量的 JavaScript 代码。必须注意确保不必要的处理不会被意外触发。

## 绑定
QML 中有两种类型的绑定：优化和非优化的绑定。最好保持绑定表达式的简单性，因为 QML 引擎使用了一个优化的绑定表达式求值器，它可以评估简单的绑定表达式，而不需要切换到一个完整的 JavaScript 执行环境。与更复杂(非优化的)绑定相比，这些优化的绑定要有效得多。绑定的优化的基本要求是，在编译时必须知道所访问的每个符号的类型信息。
** 为了达到最好的优化效果，我们应该在绑定表达式中避免的如下操作 **：

声明中间 JavaScript 变量
访问 “var” 属性
调用 JavaScript 函数
在绑定表达式中构造闭包或定义函数
访问直接求值域之外的属性
将其写入其他属性，作为副作用

绑定是最快的，当他们知道他们正在处理的对象和属性的类型时。这意味着，在某些情况下，绑定表达式中的非 final 属性查找可能会比较慢，在这种情况下，查找的属性的类型已经被更改(例如，通过派生类型)。
直接求值域可概括为：

表达式作用域对象的属性（对于绑定表达式，这是属性绑定所属的对象）
组件中任何对象的 ID
组件中根项目的属性

从其他组件和任何此类对象的属性，以及从 JavaScript 导入中定义或包含的符号，这些对象的 id 不在直接求值域内，因此访问任何这些对象的绑定将不会被优化。
注意，如果一个绑定不能通过 QML 引擎优化的绑定表达式评估器进行优化，则必须由完整的 JavaScript 环境来评估，那么上面列出的一些技巧将不再适用。例如，在一个非常复杂的绑定中，在一个中间 JavaScript 变量中缓存属性解析的结果有时是有益的。接下来的部分将会介绍更多关于这类优化的信息。
类型转换
使用 JavaScript 的一个主要代价是，在大多数情况下，访问来自 QML 类型的属性时，将创建一个包含底层 C++ 数据（或其引用）的外部资源的 JavaScript 对象。在大多数情况下，这是相当快捷的，但在其他情况下可能相当耗资源。一个很耗资源的例子就是将一个 C++ QVariantMap 属性通过 Q_PROPERTY  宏转换成 QML 中的 “variant” 属性。列表序列（Lists）也可能很耗资源，但是特定类型的序列(如int、qreal、bool、QString和QUrl 的QList 序列)应该很快捷；其他列表序列类型可能会产生高昂的转换成本(创建一个新的 JavaScript 数组，一个一个地添加新类型，从 C++ 类型实例转换为 JavaScript 值)。
某些基本属性类型（如“string”和“url”属性）之间的转换也可能很耗资源。使用最接近的匹配属性类型将避免不必要的转换。
如果您必须向 QML 引入 QVariantMap ，使用 “var” 属性而不是 “variant” 属性可能会更好一些。一般来说，对于 QtQuick 2.0 和更新版本的每个用例，“property var” 应被视为优于 “property variant” （请注意，“property variant” 被标记为已过时），因为它允许存储真正的 JavaScript 引用(这可以减少某些表达式中需要的转换次数)。
解析属性
属性解析需要消耗时间。在某些情况下，如果可能的话我们可以将查找的结果缓存和重用，以避免做不必要的工作。在下面的例子中，我们有一个经常运行的代码块（在这种情况下，它是一个显式循环的内容；但是它可以是一个经常评估的绑定表达式），在这个例子中，我们解析了对象“rect”id及其“color”属性多次：
// bad.qml
import QtQuick 2.3

Item {
    width: 400
    height: 200
    Rectangle {
        id: rect
        anchors.fill: parent
        color: "blue"
    }

    function printValue(which, value) {
        console.log(which + " = " + value);
    }

    Component.onCompleted: {
        var t0 = new Date();
        for (var i = 0; i < 1000; ++i) {
            printValue("red", rect.color.r);
            printValue("green", rect.color.g);
            printValue("blue", rect.color.b);
            printValue("alpha", rect.color.a);
        }
        var t1 = new Date();
        console.log("Took: " + (t1.valueOf() - t0.valueOf()) + " milliseconds for 1000 iterations");
    }
}

我们可以在代码块中解析共同的属性：
// good.qml
import QtQuick 2.3

Item {
    width: 400
    height: 200
    Rectangle {
        id: rect
        anchors.fill: parent
        color: "blue"
    }

    function printValue(which, value) {
        console.log(which + " = " + value);
    }

    Component.onCompleted: {
        var t0 = new Date();
        for (var i = 0; i < 1000; ++i) {
            var rectColor = rect.color; // resolve the common base.
            printValue("red", rectColor.r);
            printValue("green", rectColor.g);
            printValue("blue", rectColor.b);
            printValue("alpha", rectColor.a);
        }
        var t1 = new Date();
        console.log("Took: " + (t1.valueOf() - t0.valueOf()) + " milliseconds for 1000 iterations");
    }
}

正是这种简单的更改导致了显著的性能改进。注意，上面的代码可以进一步改进(因为在循环处理过程中，查找的属性不会改变)，通过将属性解析从循环中提出，如下所述:
// better.qml
import QtQuick 2.3

Item {
    width: 400
    height: 200
    Rectangle {
        id: rect
        anchors.fill: parent
        color: "blue"
    }

    function printValue(which, value) {
        console.log(which + " = " + value);
    }

    Component.onCompleted: {
        var t0 = new Date();
        var rectColor = rect.color; // resolve the common base outside the tight loop.
        for (var i = 0; i < 1000; ++i) {
            printValue("red", rectColor.r);
            printValue("green", rectColor.g);
            printValue("blue", rectColor.b);
            printValue("alpha", rectColor.a);
        }
        var t1 = new Date();
        console.log("Took: " + (t1.valueOf() - t0.valueOf()) + " milliseconds for 1000 iterations");
    }
}

属性绑定
如果其引用的任何属性发生更改，则属性绑定表达式将被重新评估。因此，绑定表达式应尽可能简单。
例如我们有一个循环，我们要做一些处理，但是只有处理的最终结果是我们需要的，通常更好的处理方式是添加一个临时累加器，然后对这个累加器进行处理，而不是逐步更新属性本身，以避免在累加的过程中触发绑定这个属性的地方重新运算。
下面的例子说明了这一点:
// bad.qml
import QtQuick 2.3

Item {
    id: root
    width: 200
    height: 200
    property int accumulatedValue: 0

    Text {
        anchors.fill: parent
        text: root.accumulatedValue.toString()
        onTextChanged: console.log("text binding re-evaluated")
    }

    Component.onCompleted: {
        var someData = [ 1, 2, 3, 4, 5, 20 ];
        for (var i = 0; i < someData.length; ++i) {
            accumulatedValue = accumulatedValue + someData[i];
        }
    }
}

onCompleted 处理程序中的循环使得 “text” 属性绑定重新计算了六次（然后导致依赖于 text 属性的任何其他属性绑定以及 onTextChanged 信号处理程序每次都会被重新评估，并且每次更新文本显示）。 在这种情况下，这显然是不必要的，因为我们真的只关心积加的最终结果。
它可以被改写如下:
// good.qml
import QtQuick 2.3

Item {
    id: root
    width: 200
    height: 200
    property int accumulatedValue: 0

    Text {
        anchors.fill: parent
        text: root.accumulatedValue.toString()
        onTextChanged: console.log("text binding re-evaluated")
    }

    Component.onCompleted: {
        var someData = [ 1, 2, 3, 4, 5, 20 ];
        var temp = accumulatedValue;
        for (var i = 0; i < someData.length; ++i) {
            temp = temp + someData[i];
        }
        accumulatedValue = temp;
    }
}

序列提示（Sequence tips）
如前所述，一些序列类型很快（例如 QList<int>, QList<qreal>, QList<bool>, QList<QString>, QStringList 和 QList<QUrl>），而有些则慢一些。除了使用较快的类型之外，还有其他一些与性能相关的语义，您需要了解这些语义，以达到最佳的性能。
首先，序列类型有两种不同的实现方式：一个是序列是 QObject 的Q_PROPERTY（我们称之为一个参考序列），另一个用于从 QObject 的Q_INVOKABLE 函数返回序列（我们称之为复制序列）。
参考序列通过 QMetaObject::property() 读取和写入，因此被读取并写入 QVariant。这意味着从 JavaScript 中更改序列中的任何元素的值将导致三个步骤：完整的序列将从 QObject 读取（作为 QVariant，然后转换为正确类型的序列）; 指定索引中的元素将在该序列中进行更改; 并且完整的序列将被写回 QObject（作为 QVariant）。
复制序列要简单得多，因为实际序列存储在JavaScript对象的资源数据中，因此不会发生读/修改/写入周期（而是直接修改资源数据）。
因此，对于引用序列的元素的写入速度将比对复制序列元素的写入慢得多。实际上，将 N 元素引用序列的单个元素写入到该引用序列中是等价于将 N 元素复制序列分配给该引用序列的，因此通常最好是修改临时复制序列，然后在计算过程中将结果赋值给引用序列。
假设存在(并预先注册到 “Qt.example 1.0” 名称空间)下面的C++类型：
class SequenceTypeExample : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY (QList<qreal> qrealListProperty READ qrealListProperty WRITE setQrealListProperty NOTIFY qrealListPropertyChanged)

public:
    SequenceTypeExample() : QQuickItem() { m_list << 1.1 << 2.2 << 3.3; }
    ~SequenceTypeExample() {}

    QList<qreal> qrealListProperty() const { return m_list; }
    void setQrealListProperty(const QList<qreal> &list) { m_list = list; emit qrealListPropertyChanged(); }

signals:
    void qrealListPropertyChanged();

private:
    QList<qreal> m_list;
};

以下示例在嵌套循环中写入参考序列的元素，导致性能不佳：
// bad.qml
import QtQuick 2.3
import Qt.example 1.0

SequenceTypeExample {
    id: root
    width: 200
    height: 200

    Component.onCompleted: {
        var t0 = new Date();
        qrealListProperty.length = 100;
        for (var i = 0; i < 500; ++i) {
            for (var j = 0; j < 100; ++j) {
                qrealListProperty[j] = j;
            }
        }
        var t1 = new Date();
        console.log("elapsed: " + (t1.valueOf() - t0.valueOf()) + " milliseconds");
    }
}

由 “qrealListProperty [j] = j” 表达式引起的内部循环中的 QObject 属性读取和写入使得该代码非常不理想。相反，一些功能上相同但速度更快的做法是：
// good.qml
import QtQuick 2.3
import Qt.example 1.0

SequenceTypeExample {
    id: root
    width: 200
    height: 200

    Component.onCompleted: {
        var t0 = new Date();
        var someData = [1.1, 2.2, 3.3]
        someData.length = 100;
        for (var i = 0; i < 500; ++i) {
            for (var j = 0; j < 100; ++j) {
                someData[j] = j;
            }
            qrealListProperty = someData;
        }
        var t1 = new Date();
        console.log("elapsed: " + (t1.valueOf() - t0.valueOf()) + " milliseconds");
    }
}

其次，如果其中的任何元素发生变化，则会发出该属性的更改信号。如果对序列属性中的特定元素有很多绑定，最好创建绑定到该元素的动态属性，并将该动态属性用作绑定表达式中的符号而不是序列元素，因为它将只有当其值发生变化时才会重新评估绑定。
这是一个不寻常的用例，大多数客户都不应该点击它，但是值得注意，以防你发现自己在做这样的事情：
// bad.qml
import QtQuick 2.3
import Qt.example 1.0

SequenceTypeExample {
    id: root

    property int firstBinding: qrealListProperty[1] + 10;
    property int secondBinding: qrealListProperty[1] + 20;
    property int thirdBinding: qrealListProperty[1] + 30;

    Component.onCompleted: {
        var t0 = new Date();
        for (var i = 0; i < 1000; ++i) {
            qrealListProperty[2] = i;
        }
        var t1 = new Date();
        console.log("elapsed: " + (t1.valueOf() - t0.valueOf()) + " milliseconds");
    }
}

请注意，尽管在循环中仅修改索引 2 中的元素，但是由于更改信号的粒度是整个属性已更改，所以三个绑定将全部重新计算。因此，添加中间绑定有时是有益的：
// good.qml
import QtQuick 2.3
import Qt.example 1.0

SequenceTypeExample {
    id: root

    property int intermediateBinding: qrealListProperty[1]
    property int firstBinding: intermediateBinding + 10;
    property int secondBinding: intermediateBinding + 20;
    property int thirdBinding: intermediateBinding + 30;

    Component.onCompleted: {
        var t0 = new Date();
        for (var i = 0; i < 1000; ++i) {
            qrealListProperty[2] = i;
        }
        var t1 = new Date();
        console.log("elapsed: " + (t1.valueOf() - t0.valueOf()) + " milliseconds");
    }
}

在上面的示例中，每次只针对中间绑定的值的变化进行重新评估，从而可以显著地提升性能。
值类型的建议
值类型属性（font, color, vector3d 等）具有类似的 QObject 属性，并将通知语义更改为序列类型属性。因此，上面针对序列给出的提示也适用于值类型属性。虽然它们对于值类型的问题通常不那么严重(因为值类型的子属性的数量通常比序列中的元素数量少得多)，但是重新评估的绑定数量的增加将会对性能产生负面影响。
其他 JavaScript 对象
不同的 JavaScript 引擎提供不同的优化。Qt Quick 2 使用的 JavaScript 引擎针对对象实例化和属性查找进行了优化，但它提供的优化依赖于某些标准。如果您的应用程序不符合标准，则 JavaScript 引擎将恢复到“慢路”模式，性能更差。 因此，始终尽量确保符合以下条件：

尽量避免使用 eval()
不要删除对象的属性

通用接口元素
文本元素
计算文本布局可能是一个缓慢的操作。考虑尽可能使用 PlainText 格式而不是 StyledText，因为这会减少布局引擎所需的工作量。如果我们不能使用 PlainText (因为我们需要嵌入图像，或者使用标记来指定字符的范围以具有某种格式(粗体、斜体等等)，而不是整个文本) 则应使用 StyledText。
如果文本可能（但可能不是）StyledText，则应该仅使用 AutoText，因为 StyledText 模式将导致解析成本。不应使用 RichText 模式，因为 StyledText 几乎可以提供几乎所有功能，并消耗更少的成本。
图片
图像是任何用户界面的重要组成部分。不幸的是，由于加载它们的时间、消耗的内存和使用的方式，它们也是性能问题的一个主要来源。
异步加载图片
图像通常相当大，所以明智的做法是确保加载图像不会阻塞 UI 线程。将 QML Image 元素的 “asynchronous” 属性设置为true以启用从本地文件系统异步加载图像（远程图像总是异步加载），这不会对用户界面的美观产生负面影响。
将 “asynchronous” 属性设置为 true 的 Image 元素将在低优先级的工作线程中加载图像。
显示设置 SourceSize 属性值
如果我们的应用程序将加载大型图像但将其显示在一个小尺寸的元素中，请将 “sourceSize” 属性设置为要渲染的元素的大小，以确保图像的较小缩放版本保存在内存中，而不是较大的那个。
请注意，更改 sourceSize 将导致重新加载图像。
避免运行时的组合
还要记住，您可以通过在应用程序中提供预先组合的图像资源（例如，提供具有阴影效果的元素）来避免在运行时执行构图工作。
使用锚点定位元素
使用锚点而不是相对于彼此绑定来定位元素的效率更高。考虑使用绑定来定位 rect2 相对于 rect1：
Rectangle {
    id: rect1
    x: 20
    width: 200; height: 200
}
Rectangle {
    id: rect2
    x: rect1.x
    y: rect1.y + rect1.height
    width: rect1.width - 20
    height: 200
}

使用锚点可以更有效地实现：
Rectangle {
    id: rect1
    x: 20
    width: 200; height: 200
}
Rectangle {
    id: rect2
    height: 200
    anchors.left: rect1.left
    anchors.top: rect1.bottom
    anchors.right: rect1.right
    anchors.rightMargin: 20
}

使用绑定定位（通过将绑定表达式分配给可视对象的x，y，width和height属性，而不是使用锚点）相对较慢，尽管它允许最大的灵活性。
如果布局不是动态的，那么指定布局的最有效方式就是通过静态初始化x、y、宽度和高度属性。Item 坐标总是相对于它们的父类，所以如果我们想要从 Item 父母的 0,0 坐标中得到一个固定的偏移量，我们就不应该使用锚。在以下示例中，子 Rectangle 对象位于相同的位置，但是显示的锚代码不像通过静态初始化使用固定定位的代码资源有效：
Rectangle {
    width: 60
    height: 60
    Rectangle {
        id: fixedPositioning
        x: 20
        y: 20
        width: 20
        height: 20
    }
    Rectangle {
        id: anchorPositioning
        anchors.fill: parent
        anchors.margins: 20
    }
}

模型和视图
大多数应用程序将至少有一个模型将数据提供给视图。有一些应用程序开发人员需要注意的语义，以实现最大的性能。
自定义 C++ 模型
在 C++ 中编写我们自己的自定义模型，以便在 QML 中的视图中使用。尽管任何此类模型的最佳实现都将严重依赖于它必须实现的用例，但一些一般的指导方针如下：

尽可能异步
在（低优先级）工作线程中执行所有处理
批量后端操作，以使（潜在的缓慢）I/O 和 IPC 最小化
使用滑动切片窗口缓存结果，其参数通过分析来确定

值得注意的是，建议使用低优先级的工作线程来最小化 GUI 线程的性能风险（这可能会导致更糟糕的性能）。另外，请记住，同步和锁定机制可能是性能下降的重要原因，因此应注意避免不必要的锁定。
QML 的 ListModel 类型
QML 提供了一个 ListModel 类型，可用于将数据提供给 ListView。只要正确使用，大多数使用情况就足够了，而且性能相对较高。
在工作线程中填充数据
ListModel 可以在 JavaScript 中的（低优先级）工作线程中进行数据的填充。开发人员必须在WorkerScript 中显式调用  ListModel 上的 “sync()”，以使更改与主线程同步。有关更多信息，请参阅 WorkerScript 的文档。
请注意，使用 WorkerScript  元素将导致创建单独的 JavaScript 引擎线程（因为JavaScript引擎是在单独的线程中的）。 这将导致内存使用量的增加。然而，多个 WorkerScript  元素都将使用相同的工作线程，因此一旦应用程序已经使用了一个，则使用第二个或第三个 WorkerScript  元素的内存影响可以忽略不计。
不要使用动态角色
QtQuick 2 中的 ListModel 元素比 QtQuick 1 中的性能要好得多。性能改进主要来自对给定模型中每个元素中的角色类型的假设 —— 如果类型不改变，则缓存性能显着提高。如果类型可以从元素到元素动态变化，则这种优化变得不可能，并且模型的性能将会更差一个数量级。
因此，动态类型在缺省情况下是禁用的；开发人员必须主动设置模型的boolean 类型 “dynamicRoles” 属性值为 true，以启用动态类型（并忍受伴随的性能下降）。如果可以重新设计应用程序以避免使用，我们建议不要使用动态类型。
视图
视图委托（delegate）应该尽可能地保持简单。在委托中应刚刚有足够的 QML 来显示必要的信息即可。 任何不是立即需要的附加功能（例如，如果在点击时显示更多信息）不应该被立即创建（请参见即将后文的延迟初始化部分）。
以下列表是设计委托时要牢记的事项的一个很好的总结：

委托中的元素越少，可以创建得越快，因此可以滚动视图的速度越快。
将委托中的绑定数保持最小； 特别地，使用锚而不是绑定以在委托中进行相对定位。
避免在委托中使用 ShaderEffect 元素。
切勿在委托中启用 clip 属性。

我们可以设置视图的 cacheBuffer 属性，以允许在可见区域之外异步创建和缓冲代理。对于不重要且不太可能在单个框架内创建的视图代理，建议使用 cacheBuffer。请注意，cacheBuffer  会在内存中保留额外的代理，因此使用 cacheBuffer  导出的值必须与额外的内存使用相平衡。开发人员应该使用基准测试来找出用例的最佳值，因为在极少数情况下，使用 cacheBuffer 引起的内存压力增加会导致滚动时的帧速率降低。
视觉效果
Qt Quick 2 包括几个功能，允许开发人员和设计人员创建非常吸引人的用户界面。流动性和动态转换以及视觉效果可以在应用程序中发挥很大的作用，但是在使用QML中的一些特性时，一定要注意它们的性能影响。
动画
一般来说，动画化属性将导致引用该属性的任何绑定被重新评估。 通常，这是期望的，但在其他情况下，最好在执行动画之前禁用绑定，然后在动画完成后重新分配绑定。
避免在动画过程中运行 JavaScript。例如，应避免为 x 属性动画的每个帧运行复杂的 JavaScript 表达式。
开发人员应该特别注意使用脚本动画，因为它们在主线程中运行（因此如果花费的时间太长，可能会导致跳帧）。
粒子
Qt Quick Particles 模块允许将美丽的粒子效果无缝集成到用户界面中。然而，每个平台都具有不同的图形硬件功能，而粒子模块无法将参数限制在硬件可以正常支持的范围内。您尝试渲染的粒子越多（它们越大），图形硬件需要以60 FPS呈现的速度越快。影响更多的粒子需要更快的CPU。因此，重要的是仔细测试目标平台上的所有粒子效应，以校准可以以60 FPS渲染的粒子的数量和大小。
应当注意的是，在不使用时（例如，在不可见元素上）可以禁用粒子系统，以避免进行不必要的模拟。
有关更多详细信息，请参阅 “粒子系统性能指南”。
控制元素生命周期
通过将应用程序分为简单的模块化组件，每个组件都包含在单个 QML 文件中，我们可以实现更快的应用程序启动时间，更好地控制内存使用情况，并减少应用程序中活动但不可见元素的数量。
延迟初始化
QML引擎做了一些棘手的事情，以确保组件的加载和初始化不会导致跳帧。然而，除了不去做你不需要做的工作，并且把工作推迟到有必要的时候进行，没有更好的方法来减少启动时间。这可以通过使用 Loader 或动态（dynamically）创建组件来实现。
使用 Loader
加载器（Loader）是一个允许组件动态加载和卸载的元素。

使用 Loader 的 “active” 属性，可以延迟初始化，直到需要。
使用重载版本的 “setSource()” 函数，可以提供初始属性值。
将加载器（Loader）异步（asynchronous）属性设置为 true 也可以在组件实例化时提高流动性。

使用动态创建
开发人员可以使用 Qt.createComponent() 函数在 JavaScript 中在运行时动态创建一个组件，然后调用 createObject() 来实例化它。根据调用中指定的所有权语义，开发人员可能必须手动删除所创建的对象。请参阅 JavaScript 中的动态创建 QML 对象，以获得更多信息。
销毁不再使用元素
由于它们是不可见元素的子元素（例如，标签窗口小部件中的第二个选项卡，当前正在显示第一个选项卡），因此在大多数情况下应该被延迟初始化，并在不再使用时被删除 ，以避免使其活动的持续成本（例如，渲染，动画，财产绑定评估等）。
加载加载器元素的项可以通过重新设置加载器的 “source” 或 “sourceComponent” 属性来释放，而其他项目可以通过调用 destroy() 来显式地释放。在某些情况下，可能有必要让项目处于活动状态，在这种情况下，它至少应该是不可见（invisible）的。
有关活动但不可见的元素的更多信息，请参阅后续的“渲染”部分的内容。
渲染
用于在 QtQuick 2 中渲染的场景图允许高度动态的动画用户界面以 60 FPS 流畅呈现。然而，有一些东西可能极大地降低渲染性能，而开发人员应该小心地避免这些陷阱。
剪裁
默认情况下禁用了剪裁，只在需要时才启用。
剪裁是一种视觉效果，而不是一种优化。它增加(而不是减少)渲染器的复杂性。如果启用了剪裁，一个项目将会把它自己的绘画，以及它的孩子的绘画，剪切到它的边界矩形中。这将使渲染器无法自由地重新排列元素的绘制顺序，从而导致次优的最佳情况场景图遍历。
在委托中进行剪切是非常糟糕的，应该不惜一切代价避免。
超绘和不可见元素
如果我们有其他（不透明）元素完全覆盖的元素，最好将其 “visible” 属性设置为false，否则将被无谓地绘制。
类似地，不可见的元素（例如，当前正在显示第一个选项卡的选项卡小部件中的第二个选项卡），但需要在启动时初始化（例如，如果实例化第二个选项卡的成本花费的时间太长时，才能够做到选项卡被激活），应该将其“visible”属性设置为false，以避免绘制它们的成本（虽然如前所说，他们仍将承担任何动画或绑定的成本评估，因为他们仍然活跃）。
半透明vs不透明
不透明的内容通常比半透明的要快得多。原因在于半透明的内容需要混合，而且渲染器可以更好地优化不透明的内容。
具有一个半透明像素的图像被视为完全半透明的，尽管它大多是不透明的。 对于具有透明边框的 BorderImage 也是如此。
着色器
ShaderEffect 类型使我们可以在开销很小的情况下将 GLSL 代码内联到 Qt Quick 应用程序中。然而，重要的是要意识到片段程序需要为渲染形状中的每个像素运行。当部署到低端硬件时，着色器覆盖了大量的像素，应该将片段着色器保存到一些指令中，以避免性能下降。
用 GLSL 编写的着色器允许编写复杂的转换和视觉效果，但应谨慎使用。使用 ShaderEffectSource 会将场景预渲染到 FBO 中，然后绘制。 这种额外的开销可能相当昂贵。
内存分配和收集
应用程序分配的内存数量和内存分配的方式是非常重要的考虑事项。除了对内存受限设备的内存不足的明显担忧外，在堆上分配内存是一个相当昂贵的操作，而且某些分配策略可能导致跨页面的数据碎片化。JavaScript使用一个托管的内存堆，它自动地收集垃圾，这提供了一些优势，但也有一些重要的含义。
用 QML 编写的应用程序可以即使用 C++ 堆也使用自动管理的 JavaScript 堆中的内存。 应用程序开发人员需要了解每个应用程序的细微之处，以便最大限度地提高性能。
给 QML 应用程序开发人员的提示
本节中提供的技巧和建议仅供参考，可能不适用于所有情况。确保使用经验指标仔细地对我们的应用进行基准和分析，以便做出最佳决策。
延迟实例化和初始化组件
如果我们的应用程序包含多个视图（例如，多个选项卡），但是在任何时候只需要一个视图，则可以使用延迟实例化来最小化在任何给定时间分配的内存量。有关详细信息，请参阅上一节“** 延迟初始化 **”部分。
销毁不再使用的对象
如果我们延迟实例化组件，或者在 JavaScript 表达式中动态创建对象，最好是手动 destroy() 而不是等待自动垃圾收集来完成。有关更多信息，请参阅上文控制元素生命周期的章节。
不要手动调用垃圾收集器
在大多数情况下，手动调用垃圾收集器是不明智的，因为它会在相当长的一段时间内阻塞 GUI 线程。这可能导致跳帧和不稳定的动画，这些都应该不惜一切代价避免。
有些情况下，手动调用垃圾收集器是可以接受的(这在接下来的部分中会更详细地解释)，但是在大多数情况下，调用垃圾收集器是不必要的，并且会产生相反的效果。
避免复杂的绑定
除了复杂绑定的性能降低(例如，由于必须输入 JavaScrip t执行上下文来执行评估)，它们还在 C++ 堆和 JavaScript 堆上占用了比绑定可以由 QML 优化的绑定表达式进行评估的求值器更多的内存。
避免定义多个相同的隐式类型
如果 QML 元素有在 QML 中定义的自定义属性，那么它就变成了它自己的隐式类型。这将在接下来的部分中更详细地解释。如果在一个组件内定义了多个相同的隐式类型，那么一些内存就会被浪费掉。在这种情况下，最好是显式地定义一个新组件，然后可以重用该组件。
定义自定义属性通常可以是有益的性能优化（例如，减少所需或重新评估的绑定数量），或者可以提高组件的模块性和可维护性。 在这些情况下，鼓励使用自定义属性。 但是，如果新类型被多次使用，则应将其定义为自己的组件（.qml文件），以节省内存。
复用现有组件
如果您正在考虑定义新的组件，那么值得加倍检查的是，我们的平台的组件集中是否不存在此类组件。否则，我们将迫使 QML 引擎生成和存储类型数据，而类型数据实质上与另一个预先存在的并且可能已经加载的组件重复。
使用单例类型（singleton types）而不是编译库（pragma library）脚本
如果您正在使用一个编译库（pragma library）脚本来存储应用程序范围的实例数据，那么可以考虑使用 QObject 单例类型（singleton types）。这将带来更好的性能，并将带来使用的 JavaScript 堆内存减少。
QML 应用程序中的内存分配
QML 应用程序的内存使用可能会分为两部分：即 C++ 堆的使用和 JavaScript 堆的使用。在每个部分中分配的一些内存是不可避免的，因为它由 QML 引擎或 JavaScript 引擎分配，而其余的则取决于应用程序开发人员做出的决定。
C++ 堆将包含：

QML 引擎的固定和不可避免的开销（实现数据结构，上下文信息等）
每个组件编译的数据和类型信息，包括每个类型的属性元数据，它由 QML 引擎生成，取决于应用程序导入哪些模块以及应用程序加载哪些组件
每个对象 C++ 数据（包括属性值）加上每个元素元对象层次结构，这取决于应用程序实例化的组件
任何由 QML 导入（库）专门分配的数据

JavaScript 堆将包含：

JavaScript 引擎本身的固定和不可避免的开销（包括内置的 JavaScript 类型）
我们的 JavaScript 集成的固定和不可避免的开销（用于加载类型，功能模板等的构造函数）
在运行时，由 JavaScript 引擎在运行时生成的每种类型的布局信息和其他内部类型数据(请参阅下面的关于类型的说明)
每个对象的 JavaScript 数据（“var” 属性，JavaScript 函数和信号处理程序以及未优化的绑定表达式）
表达式评估期间分配的变量

此外，在主线程中将分配一个用于使用的 JavaScript 堆，并可选地分配一个用于 WorkerScript 线程的其他 JavaScript 堆。如果应用程序不使用 WorkerScript 元素，那么就不会产生该开销。JavaScript 堆的大小可能是几兆字节，因此为内存受限的设备编写的应用程序最好避免使用 WorkerScript 元素，尽管它在异步填充 list 模型方面很有用。
请注意，QML 引擎和 JavaScript 引擎都将自动生成自己的关于观察类型的类型数据的缓存。应用程序加载的每个组件都是一个不同的（显式）类型，并且在 QML 中存在自定义属性的每个元素（组件实例）都是隐式类型。任何不存在任何自定义属性的元素（组件的实例）都被 JavaScript 和 QML 引擎视为由组件显式定义的类型，而不是其自身的隐式类型。
请考虑以下示例：
import QtQuick 2.3

Item {
    id: root

    Rectangle {
        id: r0
        color: "red"
    }

    Rectangle {
        id: r1
        color: "blue"
        width: 50
    }

    Rectangle {
        id: r2
        property int customProperty: 5
    }

    Rectangle {
        id: r3
        property string customProperty: "hello"
    }

    Rectangle {
        id: r4
        property string customProperty: "hello"
    }
}

在上面示例中，矩形 r0 和 r1 没有任何自定义属性，因此 JavaScript 和 QML 引擎将它们都视为相同类型。也就是说，r0 和 r1 都被认为是明确定义的 Rectangle 类型。矩形 r2，r3 和 r4 各自具有自定义属性，并且各自被认为是不同的（隐式）类型。注意，r3 和 r4 都被认为是不同类型的，尽管它们具有相同的属性信息，只是因为自定义属性未在其实例的组件中声明。
如果 r3 和 r4 都是 RectangleWithString 组件的实例，并且该组件定义包含名为 customProperty 的字符串属性的声明，则 r3 和 r4 将被认为是相同的类型（即它们将是 RectangleWithString 类型的实例 ，而不是定义自己的隐式类型）。
深度内存分配注意事项
无论何时作出关于内存分配或性能权衡的决策，请务必记住 CPU 缓存性能，操作系统分页和 JavaScript 引擎垃圾收集的影响。潜在的解决方案应该仔细地进行基准测试，以确保选出最好的解决方案。
没有一套通用的指导方针可以取代对计算机科学的基本原理的深入理解，结合应用程序开发人员正在开发的平台的实现细节的实际知识。此外，在做出权衡决策时，没有多少理论计算可以替代一组良好的基准和分析工具。
碎片
碎片是一个 C++ 开发问题。如果应用程序开发人员没有定义任何 C++ 类型或插件，他们可能会安全地忽略此部分。
随着时间的推移，应用程序将分配大量内存，将数据写入到该内存中，并在使用完某些数据之后，将部分内存释放出来。这可能导致“空闲”内存位于非连续的块中，这些块不能返回给其他应用程序使用的操作系统。它还对应用程序的缓存和访问特性产生了影响，因为“活着”的数据可能分布在许多不同的物理内存页上。这反过来可能会迫使操作系统进行交换，这可能导致文件系统 I/O —— 相对而言，这是一个极其缓慢的操作。
可以通过使用池分配器(和其他连续的内存分配程序)来避免碎片化，可以通过减少任何时间分配的内存量，通过仔细管理对象的生命周期、定期清理和重建缓存、或者利用内存管理运行时使用垃圾收集(比如JavaScript)来减少内存的数量。
垃圾收集
JavaScript 提供垃圾回收。在 JavaScript 堆上分配的内存（而不是 C++ 堆）由 JavaScript 引擎所拥有。引擎将定期收集 JavaScript 堆上的所有未引用的数据。
垃圾收集的影响
垃圾收集有其优点和缺点。这意味着手动管理对象的生命周期不那么重要。 但是，这也意味着JavaScript引擎可能会在应用程序开发人员控制之外启动一个潜在的持久性操作。除非应用程序开发人员仔细考虑 JavaScript 堆使用情况，否则垃圾收集的频率和持续时间可能会对应用程序体验产生负面影响。
手动调用垃圾收集器
在 QML 中编写的应用程序（很可能）需要在某个阶段执行垃圾收集。当可用的空闲内存数量较低时，JavaScript 引擎会自动触发垃圾收集，但如果应用程序开发人员决定何时手动调用垃圾收集器（通常情况并非如此），则偶尔会更好一些。
应用程序开发人员可能最了解应用程序何时空闲一段相当长的时间。如果 QML 应用程序使用了大量的 JavaScript 堆内存，那么在特别对性能敏感的任务（例如列表滚动，动画等）期间会导致定期的和破坏性的垃圾收集周期，那么应用程序开发人员可能会很好地手动调用垃圾收集器在零活动期间。 空闲周期是执行垃圾收集的理想选择，因为用户不会注意到在活动发生时调用垃圾回收器会导致用户体验（跳帧，抖动动画等）的任何降级。
垃圾收集器可以通过在 JavaScript 内调用 gc() 来手动调用。这将导致执行一个完整的收集周期，它可能从几百毫秒到超过 1000 毫秒的时间完成，因此，如果可能的话，应该尽量避免。
内存与性能的权衡
在某些情况下，为了减少处理时间而增加内存使用量是可行的。例如，将一个符号查找的结果缓存到一个 JavaScript 表达式的临时变量中，在评估该表达式时将会得到显著的性能提升，但它涉及分配一个临时变量。在某些情况下，这些权衡是明智的（比如上面的例子，这几乎总是明智的），但是在其他情况下，为了避免增加系统的内存压力，最好允许处理稍微长一点的时间。
在某些情况下，增加的内存使用的影响可能是极端的。在某些情况下，将内存使用用于假定的性能增益，可能会导致增加的页面或缓存，从而导致性能的大幅降低。总是有必要仔细评估权衡的影响，以确定在给定情况下哪个解决方案最好。
有关缓存性能和内存时间权衡的深入信息，请参阅Ulrich Drepper的优秀文章“每个程序员都应该了解的内存”（可从访问 http://ftp.linux.org.ua/pub/docs/developer/general/cpumemory.pdf 截至2012年4月18日），以及有关 C++ 特定优化的信息，请参阅 Agner Fog 的“优化 C++ 应用程序的优秀手册”（可从访问http://www.agner.org/optimize/ 截至2012年4月18日）。
本文欢迎转载，但是请注明出处。
本文参考链接：http://doc.qt.io/qt-5/qtquick-performance.html#tips-for-qml-application-developers

作者：赵者也
链接：https://www.jianshu.com/p/e6fcb575f916
来源：简书
简书著作权归作者所有，任何形式的转载都请联系作者获得授权并注明出处。

