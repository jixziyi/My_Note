# Qt 多线程

## QThread
提供开始一个新线程的方法

``` C++
// 创建 MyThread
#include <QThread>

class MyThread: public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = Q_NULLPRT);
    virtual MyThread();

protected:
    void run();
}

// 调用
MyThread myThread;
myThread.start();

// 析构
if (myThread.isRunning()) {
    myThread.quit();
    myThread.wait();
}
```

## QThreadStorage
提供线程数据存储

## QMutex
QMutex 的目的是保护一个对象、数据结构或者代码段，同一时间只有一个线程可以访问它。

### 成员变量
- enum QMutex::RecursionMode
    - QMutex::Recursive 1 在该模式下，一个线程可以锁住一个互斥量多次，只有经过相同次数的 `unlock()` 后才能释放
    - QMutex::NonRecursive 0 在该模式下，一个互斥量只能被锁住一次

### 成员函数
- QMutex::QMutex(RecursionMode mode = NonRecursive)
- QMutex::~QMutex()
- void QMutex::lock()
    - 锁定互斥量，如果另一个线程已经锁定该互斥量，那么这次调用将阻塞知道那个线程将它解锁
    - 如果是递归互斥量，允许同一个线程多次调用该函数锁定该互斥量。如果不是递归互斥量，调用该函数将导致死锁
- bool QMutex::tryLock()
    - 尝试锁定互斥量，如果获得该互斥量，返回 true。如果另外线程已经锁定该互斥量，那么函数立即返回 false
- bool QMutex::tryLock(int timeout)
    - 增加等待 timeout 微秒

## QMutexLocker
一个便利类，自动对 QMutex 加锁与解锁

## QReadWriteLock
对 `read` 和 `write` 访问区别对待，使得多个用户可以共同访问数据。

## QReadLocker / QWriteLocker
一个便利类，自动对 QReadWriteLocker 加锁与解锁

## QSemaphore
提供了一个整型信号量，是互斥量的泛化

## QWaitCondition
提供了一种方法，使得线程可以在被另外线程唤醒之前一直休眠

