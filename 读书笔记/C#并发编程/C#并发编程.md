# C# 并发编程

- [一、并发编程概述](#一、并发编程概述)
    - [并发编程简介](#并发编程简介)
    - [异步编程简介](#异步编程简介)
    - [并行编程简介](#并行编程简介)
    - [响应式编程简介](#响应式编程简介)
    - [数据流简介](#数据流简介)
    - [并发编程的集合](#并发编程的集合)
    - [现代设计](#现代设计)
- [二、异步编程基础](#二、异步编程基础)
    - [暂停一段时间](#暂停一段时间)
    - [返回完成的任务](#返回完成的任务)
    - [报告进度](#报告进度)
    - [等待一组任务完成](#等待一组任务完成)
    - [等待任意一个任务完成](#等待任意一个任务完成)
    - [任务完成时的处理](#任务完成时的处理)
    - [避免上下文延续](#避免上下文延续)
- [三、并行开发的基础](#三、并行开发的基础)
    - [数据并行处理](#数据并行处理)
- [四、数据流基础](#四、数据流基础)
- [五、Rx基础](#五、Rx基础)
- [六、测试技巧](#六、测试技巧)
- [七、互操作](#七、互操作)
- [八、集合](#八、集合)
- [九、取消](#九、取消)
- [十、函数式OOP](#十、函数式OOP)
    - [异步接口和继承](#异步接口和继承)
    - [异步构造：工厂](#异步构造：工厂)
    - [异步构造：异步初始化模式](#异步构造：异步初始化模式)
    - [异步属性](#异步属性)
    - [异步事件](#异步事件)
    - [异步销毁](#异步销毁)
- [十一、同步](#十一、同步)
- [十二、调度](#十二、调度)
- [十三、实用技巧](#十三、实用技巧)


## 一、并发编程概述

### 并发编程简介
- 并发：同时做多件事
- 多线程：并发的一种形式，采用多个线程来执行程序
- 并行处理：把正在执行的大量的任务分割成小块，分配给多个同时运行的线程
- 异步编程：并发的一种形式，采用future模式或者callback机制，避免产生不必要的线程
- 响应式编程：一种声明式的编程模式，程序再该模式中堆事件进行响应

### 异步编程简介
现代异步.NET程序使用两个关键字: async 和 await。
async 加在方法声明上，使方法内的 await 关键字生效。
如果 async 方法有返回值，应该返回 Task<T>，如果没有，应返回 Task。
task类型相当于future，用来在异步方法结束时通知主程序。
**async 方法可以返回void，单仅限于编写事件处理程序**

用await语句等待一个任务完成时，该方法在 await 处暂停时，就可以捕捉上下文(context)。
如果当前 SyncchroizationContext 不为空，则上下文为当前 SynchronizationContext。
如果为空，则上下文为当前 TaskScheduler。

运行UI线程时采用UI上下文，处理ASP.NET请求时采用ASP.NET请求上下文，其他很多情况则采用线程池上下文。

在 await 中 使用 ConfigureAwait方法，将参数 continueOnCapturedContext 设置为 false。接下来代码将会在开始调用的线程里运行，在被 await 暂停后，则会在线程池线程里继续运行。

**避免死锁关键点**
- 使用 ConfigureAwait(false) 使 await 忽略上下文
- 使用 await 调用方法，使之变成一个异步方法

### 并行编程简介
并行形式：
- 数据并行 data parallelism
- 任务并行 task parallelism

并行准则：
- 每个任务快要尽可能互相独立
- 任务不要特别短，也不要特别长


### 响应式编程简介

### 数据流简介

### 多线程编程简介

### 并发编程的集合

### 现代设计

## 二、异步编程基础
### 暂停一段时间

''' C# 
await Task.Delay(delay);
'''

使用 Task.Delay 实现简单超时功能
``` CSharp
static async Task<string> DownloadStringWithTimeout(string url){
    using (var client = new HttpClient()){
        var downloadTask = client.GetStringAsync(uri);
        var timeoutTask = Task.Delay(3000);

        var completedTask = await task.WhenAny(downloadTask, timeoutTask);
        if(completedTask == timeoutTask){
            return null;
        }
        return await downloadTask;
    }
}
```

### 返回完成的任务
Task.FromResult

### 报告进度
如果一个方法可以报告进度，就应该尽量做到可以被取消。
使用 IProgress<T> 和 Progress<T> 类型，其中 T 是需要报告的进度类型：
``` CSharp
static async Task MyMethodAsync(IProgress<double> progress = null){
    double percentComplete = 0;
    while (!done){
        // ... 
        if (progress != null){
            progress.Report(percentComplete);
        }
    }
}

static async Task CallMyMethodAsync(){
    var progress = new Progress<double>();
    progress.ProgressChanged += (sender, args) => {
        // ...
    };
    await MyMethodAsync(progress);
}
```

### 等待一组任务完成
Task.WhenAll()

### 等待任意一个任务完成
Task.WhenAny()

### 任务完成时的处理
await

### 避免上下文延续
默认情况下，一个async方法在被await调用后恢复运行时，会在原来的上下文中运行。
如果时UI上下文，并且有大量的async方法在UI上下文中恢复，就会引起性能上的问题。
WinRT知道标准，UI线程中延续任务，100个/s尚可，1000个/s则太多了。
使用 ConfigureAwait(false) 避免在上下文中恢复运行。


## 三、并行开发的基础
任务并行库TPL
**并行编程适用于计算密集型任务，对于IO密集型任务则需要异步操作。**

### 数据并行处理
Parallel.ForEach方法可以对一系列值进行并行处理。
``` CSharp
void RotateMatrices(IEnumerable<Matrix> matrices, float degrees){
    Parallel.ForEach(matrices, matrix => matrix.Rotate(degrees));
}
```

### 并行聚合


## 四、数据流基础

## 五、Rx基础

## 六、测试技巧

## 七、互操作

## 八、集合

## 九、取消


## 十、函数式OOP
### 异步接口和继承
#### 实现异步的接口或基类中的方法
- 一个接口或抽象方法可以返回一个Task/Task<T>对象，这个对象可以用await等待。
- 异步方法的特征仅仅表示他的实现可以是异步的，如果没有真正的异步任务，用同步方式实现这个方法也是可以的。
``` CSharp
interface IMyAsyncInterface
{
    Task<int> CountBytesAsync(string url);
}

class MyAsyncClass : IMyAsyncInterface
{
    public async Task<int> CountBytesAsync(string url)
    {
        var client = new HttpClient();
        var bytes = await client.GetByteArrayAsync(url);
        return bytes.Length;
    }
}

static async Task UseMyInterfaceAsync(IMyAsyncInterface service)
{
    var result = await service.CountBytesAsync("http://www.example.com");
    Trace.WriteLine(result);
}
```

### 异步构造：工厂
#### 需要在一个类的构造函数里进行异步操作
- 将构造函数与一个异步的初始化方法配对使用
``` CSharp
var instance = new MyAsyncClass();
await instance.InitializeAsync();
```
- 建立异步工厂
``` CSharp
class MyAsyncClass
{
    private MyAsyncClass()
    {
    }

    private async Task<MyAsyncClass> InitializeAsync()
    {
        await Task.Delay(TimeSpan.FromSecond(1));
        return this;
    }

    public static Task<MyAsyncClass> CreateAsync()
    {
        var result = new MyAsyncClass();
        return result.InitializeAsync();
    }
}

class MyAsyncClassFactory
{
    void CreateMyClass
    {
        // 创建实例
        var instance = await MyAsyncClass.CreateAsync();
    }
}
```

#### ~~错误示例~~
用一个常规构造函数启动一个异步操作
- 构造函数结束时，初始化过程仍在异步进行，没有直观方法检测异步的初始化过程是否已经完成。
- InitilizeAsync引发的任何错误，相关catch语句都无法捕获。
``` CSharp
class MyAsyncClass
{
    public MyAsyncClass()
    {
        InitializeAsync();
    }

    // 坏代码
    private async void InitializeAsync()
    {
        await Task.Delay(TimeSpan.FromSeconds(1));
    }
}
```

### 异步构造：异步初始化模式
#### 通过反射创建的类(依赖注入/控制反转容器、数据绑定、Activator、CreateInstance)的构造函数需要执行异步过程
- 使用异步初始化模式，对每个需要异步初始化的类，定义一个属性： `Task Initialization {get;}`
``` CSharp
public interface IAsyncInitialization
{
    // 把一个类标记为需要异步初始化，并提供初始化结果
    public interface IAsyncInitialization
    {
        // 本实例的异步初始化结果
        Task Initialization {get;}
    }
}

class MyFundamentalType : IMyFundamentalType, IAsyncInitialization
{
    public MyFundamentalType()
    {
        Initialization = InitializeAsync();
    }

    public Task Initialization {get; private set;}

    private async Task InitializeAsync()
    {
        // 对这个实例进行异步初始化
        await Task.Delay(TimeSpan.FromSeconds(1));
    }
}

// 使用了依赖注入/控制反转库，可以用下面的方式创建和初始化一个类的实例
IMyFundamentalType instance = UltimateDIFactory.Create<IMyFundamentalType>();
var instanceAsyncInit = instance as IAsyncInitialization;
if (instanceAsyncInit != null)
{
    await instanceAsyncInit.Initialization;
}

// 另一个写法
class MyComposedType : IMyComposedType, IAsyncInitialization
{
    private readonly IMyFundamentalType _fundamental;

    public MyComposedType(IMyFundamentalType fundamental)
    {
        _fundamental = fundamental;
        Initialization = InitializeAsync();
    }

    private async Task InitializeAsync()
    {
        // 如有必要，异步地等待基础实例的初始化
        var fundamentalAsyncInit = _fundamental as IAsyncInitialization;
        if (fundamentalAsyncInit != null)
        {
            await fundamentalAsyncInit.Initialization;
        }

        // 其他初始化工作 (同步或异步)
    }
}
```

#### 检查某个实例是否实现了接口，并对它做初始化
``` CSharp
public static class AsyncInitialization
{
    static Task WhenAllInitializedAsync(params object[] instances)
    {
        return Task.WhenAll(instances
            .OfType<IAsyncInitialization>()
            .Select(x => x.Initialization));
    }
}

private async Task InitalizeAsync()
{
    // 异步地等待三个实例全部初始化完毕
    await AsyncInitialization.WhenAllInitializedAsync(_fundamental,
        _anotherType, _yetAnother);
    
    // 其他初始化工作 (同步或异步)
}
```

### 异步属性
#### 把一个属性改成异步方式
- 如果每次访问属性都会启动一次新的异步操作，那这个属性应该是一个方法
- 如果异步属性只启动一次(异步)计算，并缓存结果供以后使用，可以使用Lazy对象初始化
``` CSharp
public AsyncLasy<int> Data
{
    get {return _data;}
}

private readonly AsyncLasy<int> _data = 
    new AsyncLazy<int>(async () => 
    {
        await Task.Delay(TimeSpan.FormSecond(1));
        return 13;
    });

int value = await instance.Data;
```
**不要用Result或Wait把异步代码强制转换为同步代码。**在GUI和ASP.NET平台中，这样的代码很容易造成死锁。

### 异步事件
#### 需要一个可以一部运行的事件处理器，并且需要检测事件处理器是否已经完成
- Nito.AsyncEx库中有个一个DeferralManager类(延时管理器)，可以用来分配延期对象，并且跟踪每个对象完成时间
``` CSharp
public class MyEventArgs : EventArgs
{
    private readonly DefferralManager _deferrals = new DeferralManager();

    public IDisposable GetDeferral()
    {
        return _deferrals.GetDeferral();
    }

    internal Task WaitForDeferralsAsync()
    {
        return _deferrals.SignalAndWaitAsync();
    }
}

public event EventHandler<MyEventArgs> MyEvent;

private Tassk RaiseMyEventAsync()
{
    var handler = MyEvent;
    if (handler == null)
    {
        return Task.FromResult(0);
    }

    var args = new MyEventArgs(...);
    handler(this, args);
    return args.WaitForDeferralsAsync();
}

async void AsyncHandler(object sender, MyEventArgs args)
{
    using(args.GetDeferral())
    {
        await Task.Delay(TimeSpan.FromSeconds(2));
    }
}
```

### 异步销毁

## 十一、同步

## 十二、调度

## 十三、实用技巧



