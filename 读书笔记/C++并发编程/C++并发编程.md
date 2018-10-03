# C++ Concurrency In Action / C++ 并发编程

- [一、你好，C++的并发世界](#一、你好，C++的并发世界)
    - [何谓并发和多线程](#何谓并发和多线程)
    - [应用程序为什么要使用并发和多线程](#应用程序为什么要使用并发和多线程)
    - [C++的并发史](#C++的并发史)
    - [一个简答的多线程程序](#一个简答的多线程程序)
- [二、线程管理](#二、线程管理)
    - [启动新线程](#启动新线程)
    - [等待线程与分离线程](#等待线程与分离线程)
    - [线程唯一标识符](#线程唯一标识符)
- [三、线程间共享数据](#三、线程间共享数据)
- [四、同步并发操作](#四、同步并发操作)
- [五、C++内存模型和原子类型操作](#五、C++内存模型和原子类型操作)
- [六、基于锁的并发数据结构设计](#六、基于锁的并发数据结构设计)
- [七、无锁并发数据结构设计](#七、无锁并发数据结构设计)
- [八、并发代码设计](#八、并发代码设计)
- [九、高级线程管理](#九、高级线程管理)
- [十、多线程程序的测试和调试](#十、多线程程序的测试和调试)

## 一、你好，C++的并发世界

### 何谓并发和多线程
- 并发 - 两个或更多个独立的活动同时发生

#### 计算机系统中的并发
- 任务切换：通过一个任务做一会，再切换到别的任务再做一回的方式，让任务看起来是并行执行的
- 为了实现交织进行，系统每次从一个任务切换到另一个时都需要切换一次上下文(context switch)，任务切换也有时间开销
- 进行上下文切换时，操作系统必须为当前运行的任务保存CPU的状态和指令指针，并计算出要切换到哪个任务，并为即将切换到的任务重新加载处理器状态。然后，CPU可能要将新任务的指令和数据的内存载入到缓存中，这会阻止CPU执行任何指令，从而照成更多的延时
线程 - 每个线程相互独立运行，且线程可以在不同的指令序列中运行。进程中所有线程都共享地址空间，并且所有线程都访问到大部分数据-全局变量。指针、对象的引用或数据可以在线程之间传递

#### 并发的途径
1. 多进程并发
    - 将应用程序分为多个独立的进程，他们在同一时刻运行
2. 多线程并发
    - 在单个进程中运行多个线程

### 应用程序为什么要使用并发和多线程
#### 为什么使用并发
1. 关注点分离SOC
2. 性能 - 将一个单个任务分成几部分，且各自并行运行，从而降低总运行时间。
    1. 任务并行(task parallelism) - 一个线程执行算法的一部分，另一个线程执行算法的另一个部分。受此影响的算法称之为易并行(embarrassingly parallel)算法。
    2. 数据并行(data parallelism) - 每个线程在不同的数据部分上执行相同的操作。
#### 什么时候不使用并发
    - 收益比不上成本
    1. 使用并发的代码在很多情况下难以理解，增加开发维护成本
    2. 性能增益可能会小于预期

### C++的并发史
只有在 C++ 11 标准下，才能编写不依赖平台扩展的多线程代码

### 一个简答的多线程程序
`#include <thread>` 管理线程的函数和类在 `<thread>` 中声明

``` C++
#include <istream>
#include <thread>

void hello(){
    std::count << "Hello Concurrent World\n";
}

int main(){
    std::thread t(hello);

    // 调用线程(main 线程) 等待与 std::thread 对象相关的线程(t)
    t.join();
}
```

## 二、线程管理
### 启动新线程
构造 `std::thread` 对象：
``` C++
void do_some_work();
std::thread my_thread(do_some_work);
```

`std::thread` 可以调用类型构造
``` C++
class background_task
{
public:
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};

background_task f;
std::thread my_thread(f);
```

为避免 C++ 语法解析问题 `C++'s most vexing parse` ，不能直接把函数对象传入线程构造函数中
``` C++
// std::thread my_thread(background_task()); 定义一个名为 my_thread 的函数

// 使用括号组
std::thread my_thread((background_task()));

// 使用新的初始化表达式
std::thread my_thread{background_task()};

// 使用lambda表达式
std::thread my_thread([]{
    do_something();
    do_something_else();
});
```

### 等待线程与分离线程
``` C++
struct func 
{
    int& i;
    func(int& i_) : i(i_) {}
    void operator()()
    {
        for (unsigned j=0; j<1000000; ++j)
        {
            do_something(i);
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach(); // 不等待线程运行
}   // 新线程可能还在运行
```

#### `join()` 加入：
使用 try/catch 块确保访问本地状态的线程退出后，函数才结束。
``` C++
struct func
{
    int &i;
    func(int &i_) : i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000; ++j)
        {
            do_something(i);
        }
    }

    void do_something(int &i)
    {
        std::cout << i << std::endl;
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);

    try
    {
        // do_something_in_current_thread();
    }
    catch (...)
    {
        t.join();
        throw;
    }
    t.join();
}
```

使用 `RAll` 等待线程完成
``` C++
class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_) : t(t_) {}

    ~thread_guard()
    {
        if(t.joinable())
        {
            t.join();
        }
    }

    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

struct func
{
    // ...
}

void oop()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
    do_something_in_current_thread();
}
```

#### `detached()` 分离：

### 线程唯一标识符

## 三、线程间共享数据

## 四、同步并发操作

## 五、C++内存模型和原子类型操作

## 六、基于锁的并发数据结构设计

## 七、无锁并发数据结构设计

## 八、并发代码设计

## 九、高级线程管理

## 十、多线程程序的测试和调试

