# C++ 内存管理

## C++ 创建类的对象的方法两种创建类的对象的方法的区别如下：
- new 创建的对象会赋值给类指针，此对象可以在多处使用
- new 创建的对象在使用完时，必须要使用 delete 销毁该对象，否则会造成内存泄露
- new 创建的对象只有调用 delete 才会执行析构函数
- 直接使用类名创建的对象，不需要手动销毁该对象，因为该类的析构函数会自动执行
- new 创建的对象使用的是堆空间
- 在局部，直接使用类名创建的对象使用的是栈空间
- new 创建的对象会赋值给类指针，指针用途广泛，比如作为函数返回值、函数参数等
- 频繁调用(不同)对象的场合并不适合使用 new 方法创建的对象，原理同 new 申请和 delete 释放内存

``` C++
// 直接使用类名创建对象
ClassOne c1;
c1.m_one = 1;
string strSomething = "m_one value is :";
c1.PrintSomething(strSomething, c1.m_one);

// 使用 new 创建对象
ClassOne *c2 = new ClassOne();
c2->m_one = 2;
c2->PrintSomethone(strSomething, c2->m_one);
if (NULL != c2) {
    delete c2;
    c2 = NULL;
}
```

## C++ new 一个对象的时候加括号和不佳括号的区别
- 加括号调用没有参数的构造函数，不加括号调用默认构造函数或唯一的构造函数
- C++ 在 new 时的初始化规律：对于有构造函数的类，无论有没有括号，都用构造函数进行初始化；如果没有构造函数，则不加括号的 new 只分配内存空间，不进行内存的初始化，而加了括号的 new 会在分配内存的同时初始化为 0


## C++ 零参数初始化对象三种风格：`()`、`{}`、`无括号`
``` C++
IntCell *m;

// 1. 加 ()
m = new IntCell();

// 2. 加 {}，C++ 11 初始化列表语法
m = new IntCell{};
vector<int> daysInWeek = { 1, 2, 3, 4, 5, 6, 7 };
vector<int> daysInWeek { 1, 2, 3, 4, 5, 6, 7 };

// 3. 无括号
m = new IntCell;
```

