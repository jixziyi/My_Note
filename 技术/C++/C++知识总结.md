# C++ 知识总结

[地址](https://github.com/huihut/interview)



## const
### 作用
1. 修饰变量，说明该变量不可以被改变
2. 修饰指针，分别指向常量指针和指针常量
3. 常量引用，经常用于形参类型，即避免了拷贝，又避免了函数对值的修改
4. 修饰成员函数，说明该成员函数内不能修改成员变量

### 使用
``` C++
class A
{
private:
    const int a;            // 常对象成员，只能在初始化列表中赋值

public:
    A() { };                // 构造函数
    A(int x) : a(x) {};     // 初始化列表

    // const可以用于对重载构造函数的区分
    int getValue();         // 普通成员函数
    int getValue() const;   // 常成员函数，不得修改类中的任何数据成员的值
};

void function()
{
    // 对象
    A b;
    const A a;              // 常对象，只能调用常成员函数、更新常成员变量
    const A *p = &a;        // 常指针
    const A &p = a;         // 常引用
    
    // 指针
    char greeting[] = "hello";
    char* p1 = greeting;        // 指针变量，指向字符数组变量
    const char* p2 = greeting;  // 指针变量，指向字符数组常量
    char* const p3 = greeting;  // 常指针，指向字符数组变量
    const char* const p4 = greeting;    // 常指针，指向字符数组常量
}

// 函数
void function1(const int Var);      // 传递过来的参数在函数内不可变
void function2(const char* Var);    // 参数指针所指内容为常量
void function3(char* const Var);    // 参数指针为常指针
void function4(const int& Var);     // 引用参数在函数内为常量

// 函数返回值
const int function5();          // 返回一个常数
const int* function6();         // 返回一个指向常量的指针变量，使用：const int *p = function6();
int* const funcation7();        // 返回一个指向变量的常指针，使用：int* const p = funcation7();

```

## static
### 作用
- 修饰普通变量，修改变量的存储区域和生命周期，使变量存储在静态区，在main函数运行前就分配了空间，如果有初始值就用初始值初始化它，如果没有初始值系统就用默认值初始化它
- 修饰普通函数，表明函数的作用范围，仅在定义函数的文件内才能使用。在多人开发的项目时，位防止与他人命令函数重名，可以将函数定位为 static
- 修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员
- 修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在static函数内不饿能访问非静态成员

## sizeof()
- sizeof 对数组，得到整个数组所占空间的大小
- sizeof 对指针，得到指针本身所占空间的大小

``` C++
int i[10];
int* pi = i;

// 40, 4/8
std::cout << sizeof(i) << "," << sizeof(pi)

```


## this 指针
- this指针时一个隐藏于每一个非静态成员函数中的特殊指针，指向正在被该成员函数操作的那个对象
- 当对一个对象调用成员函数时，编译器先将对象的地址传给this指针，然后调用成员函数，每次成员函数存取数据成员时，由隐含使用this指针
- 当一个成员函数被调用时，自动向它传递一个隐含的参数，该参数是一个指向这个成员函数所在的对象的指针
- this指针被隐含地声明为：`ClassName *const this`，这意味着不能给this指针赋值；在ClassName类的const成员函数中，this指针的类型为`const ClassName* const`，这说明this指针所指向的这种对象是不可修改的
- this并不是一个常规变量，而是个右值，所以不能取得this的地址，不能使用`&this`
- 在以下场景中需要显示引用this指针
    - 为实现对象的链式引用
    - 为避免对同一对象进行赋值操作
    - 在实现一些数据结构时，如:list


## 数据类型转换
1. 强制类型转换
    - 对变量对应的内存里的0/1按照新类型进行重新解释的过程
2. 指针类型转换
    - 转换后指针变量的值(地址)不变
    - 读取变量的长度按照转换后的变量大小读取
    - 读取到的内容按照转换后的变量类型重新解释

## C语言标准库(ANSI C)
- stdio.h - 标准输入输出
- stdio.h - 文件操作
- ctype.h - 字符操作
- string.h - 字符串操作
- math.h - 数学函数
- stdlib.h - 资源管理
- stdlib.h - 格式转换
- time.h - 时间/日期
- assert.h - 断言
- limits.h & float.h - 各种类型上的常数
- stdarg.h - 变长参数
- setjmp.h - 非局部跳转
