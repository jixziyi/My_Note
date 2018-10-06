# C++ Primer Plus
- 第6版
- Stephen Prata 著
- 张海龙 袁国忠 译

### C -> C++
程序 = 数据 + 算法
- C++ 在 C 语言基础上添加了面向对象概念
- C++ 在 C 语言基础上添加了泛型编程概念

OOP是一个管理大型项目的工具
泛型编程提供了执行常见任务(如数据排序或合并链表)的工具

C语言
- 过程性语言 procedural
- 结构化编程 structured programming
- 自顶而下设计 top-down
    - 将大型程序分解成小型、便于管理的任务

C++
- 设计与问题本质特征相对应的数据格式
    - 类是一种规范，使用类描述这种新型数据格式
    - 对象是根据这种规范构造的特定数据结构
    - 将数据和方法合并为类定义
    - 创建可重用的代码
    - 信息隐藏保护数据
    - 多态为运算符和函数创建多个定义
    - 继承使用旧类派生出新类
- 自下向上编程 bottom-up 
    - 从低级组织(如类)到高级组织(如程序)
- 泛型编程 (generic programming)


### 程序创建过程
``` mermaid
graph TD
    SourceCode-->Compiler
    Compiler-->ObjectCode
    ObjectCode-->LinkProgram
    StartupCode-->LinkProgram
    LibraryCode-->LinkProgram
    LinkProgram-->ExecutableProgram
    SourceCode[源代码 .cpp/.cxx]
    Compiler[编译器]
    ObjectCode[目标代码 .o/.obj ]
    StartupCode[启动代码]
    LibraryCode[库代码]
    LinkProgram[链接程序]
    ExecutableProgram[可执行代码 .exe/.lib/.dll]
```

### C++ 源代码文件的扩展名
|        C++实现        |      扩展名       |
| --------------------- | ----------------- |
| UNIX                  | C/cc/cxx/c        |
| GNU C++               | C/cc/cxx/cpp/c++  |
| Digital Mars          | cpp/cxx           |
| Borland C++           | cpp               |
| Watcom                | cpp               |
| Microsoft Visual C++  | cpp/cxx/cc        |
| Freestyle CodeWarrior | cp/cpp/cc/cxx/c++ |


### 头文件命名约定

| 头文件类型  |         约定         |    示例    |                          说明                           |
| ----------- | -------------------- | ---------- | ------------------------------------------------------- |
| C++旧式风格 | .h                   | iostream.h | C++程序可以使用                                         |
| C旧式风格   | .h                   | math.h     | C/C++程序可以使用                                       |
| C++新式风格 | 没有扩展名           | iostream   | C++转换后可以使用，使用`namespace std`                  |
| 转换后的C   | 加上前缀c,没有扩展名 | cmath      | C++程序可以使用，可以使用不是C的特性，如`namespace std` |