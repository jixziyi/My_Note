# gcc/g++ 配置

## g++ 常用命令选项
|     选项     |                     解释                     |
| ------------ | -------------------------------------------- |
| -ansi        | 只支持ANSI标准的C语法                        |
| -c           | 只编译并生成目标文件                         |
| -DMACRO      | 以字符串"1"定义MACRO宏                       |
| -DMACRO=DEFN | 以字符串"DEFN"定义MACRO宏                    |
| -E           | 只运行C预编译器                              |
| -g           | 生成调试信息，GNU调试器可利用该信息          |
| -IDIRECTORY  | 指定额外的头文件搜索路径DIRECTORY            |
| -LDIRECTORY  | 指定额外的函数库搜索路径DIRECTORY            |
| -ILIBRARY    | 链接时搜索指定的函数库LIBRARY                |
| -o           | FILE生成指定的输出文件，用在生成可执行文件时 |
| -O0          | 不进行优化处理                               |
| -O / -O1     | 优化生成代码                                 |
| -O2          | 进一步优化                                   |
| -O3          | 比-O2更进一步优化，包括inline函数            |
| -shared      | 生成共享目标文件，通常用在建立共享库时       |
| -static      | 禁止使用共享链接                             |
| -UMACRO      | 取消对MACRO宏的定义                          |
| -w           | 不生成任何警告信息                           |
| -Wall        | 生成所有警告信息                             |

## 修改默认include路径

``` bash
#在PATH中找到可执行文件程序的路径。
export PATH =$PATH:$HOME/bin

#gcc找到头文件的路径
C_INCLUDE_PATH=/usr/include/libxml2:/MyLib
export C_INCLUDE_PATH

#g++找到头文件的路径
CPLUS_INCLUDE_PATH=$CPLUS_INCLUDE_PATH:/usr/include/libxml2:/MyLib
export CPLUS_INCLUDE_PATH

#找到动态链接库的路径
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/MyLib
export LD_LIBRARY_PATH

#ObjC路径
OBJC_INCLUDE_PATH=$OBJC_INCLUDE_PATH:/MyLib
export OBJC_INCLUDE_PATH

#找到静态库的路径
LIBRARY_PATH=$LIBRARY_PATH:/MyLib
export LIBRARY_PATH

# 查看结果
gcc -v -x c++ -E -
g++ -v -x c++ -E -
```

### 编译时
头文件的搜索路径
gcc 在编译时如何去寻找所需要的头文件：
- 所以header file的搜寻会从-I开始
- 然后找gcc的环境变量 
    - C_INCLUDE_PATH
    - CPLUS_INCLUDE_PATH
    - OBJC_INCLUDE_PATH
- 再找内定目录
/usr/include
/usr/local/include（centos7中该目录下是空的）
- gcc的一系列自带目录
/usr/include/c++/4.8.5

库文件的搜索路径
- gcc会去找-L
- 再找gcc的环境变量LIBRARY_PATH
- 再找内定目录 /lib /usr/lib /usr/local/lib 这是当初compile gcc时写在程序内的

### 运行时
动态库的搜索路径
- 编译目标代码时指定的动态库搜索路径；
- 环境变量LD_LIBRARY_PATH指定的动态库搜索路径；
- 配置文件/etc/ld.so.conf中指定的动态库搜索路径；
- 默认的动态库搜索路径/lib；
- 默认的动态库搜索路径/usr/lib。




