# C# 并发编程

## 并发编程概述

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

## 异步编程基础
### 暂停一段时间

''' C# 
await Task.Delay(delay);
'''

使用 Task.Delay 实现简单超时功能
``` C#
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
``` C#
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
