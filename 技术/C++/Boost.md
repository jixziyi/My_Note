# Boost

## Boost安装编译
1. 安装带gcc/g++编译器，参考`MinGW.md`或者使用[Code::Blocks](http://www.codeblocks.org/)

2. 下载[Boost源码](https://dl.bintray.com/boostorg/release/)，选择boost_1_68_0.zip版本，然后解压。

3. 打开CMD终端，执行bootstrap.bat，生成bjam.exe和b2.exe，其中gcc是指定编译器。
``` bat
rem 编译器可以为: gcc/msvc/borland 
booststrap.bat gcc
```

4. 执行下面命令
``` bat
bjam install -toolset=gcc -without-graph -without-graph_parallel -without-mpi -without-serialization -without-wave -prefix=”D:\Boost\boost_1_68_0” link=static runtime-link=shared runtime-link=static threading=multi debug release 
```
下面解释具体参数：
- install/stage: install会生成包含头文件的include目录,stage表示只生成库（dll和lib）无Include目录（可以使用原本就有的booost_1_64_0目录下的boost目录）。我这里面用install命令，生成的include只有几十M不会占用太大空间。
- toolset编译器选项可以是gcc、msvc、borland
- without表示不安装某些库（因为我在学习Python所以我这里安装了python库，安装Python库需要首先安装Python解释器，您如果不需要的话可以添加-with-python来取消安装python库）
- prefix/stagedir 前面使用install时用prefix，用stage时用stagedir，表示编译生成文件的路径，我这里是在D:\dev_tool\Boost下的Boost目录，您可以根据自己的偏好更好，同样配置C::B和VS时的也要相应地更改。 
- build-dir 编译过程中间文件存放目录，默认是bjam目录下的bin.v2，等编译完成后便可删掉该文件.
- threading 一般是多线程所以multi（如果您不写多线程程序的话这里可以不用设置） 
link 生成动态链接库/静态链接库。生成动态链接库需使用shared方式，生成静态链接库需使用static方式。一般boost库可能都是以static方式编译，因为最终发布程序带着boost的dll感觉会比较累赘。
- runtime-link 动态/静态链接C/C++运行时库。同样有shared和static两种方式，这样runtime-link和link一共可以产生4种组合方式，各人可以根据自己的需要选择编译。一般link只选static的话，只需要编译2种组合即可，即link=static runtime-link=shared和link=static runtime-link=static，本人一般就编这两种组合。
- debug/release 编译debug/release版本。一般都是程序的debug版本对应库的debug版本，所以两个都编译。

5. 设置全局变量
