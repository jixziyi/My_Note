# FFTW3 
快速傅里叶变换库

## 环境配置
- [登陆官网](#http://www.fftw.org/install/windows.html) 下载 64-bit version
- 解压到指定盘符，不要 C 盘，需要额外权限，如 `D:\fftw`
- 打开 `VS 开发人员命令提示`
- 转到目录 `D:\fftw`
- 输入命令
``` cmd
lib /machine:x64 /def:libfftw3-3.def
lib /machine:x64 /def:libfftw3f-3.def
lib /machine:x64 /def:libfftw3l-3.def
```
- 生成对应 lib 文件，`libfftw3-3.lib`、`libfftw3f-3.lib`、`libfftw3l.lib`

### VS 配置
- VS 项目-属性-C/C++附加包目录，加上 `D:\fftw`
- VS 项目-属性-链接器-常规-附加库目录，加上 `D:\fftw`
- VS 项目-属性-链接器-输入-附加依赖项，加上 `libfftw3-3.lib;libfftw3f-3.lib;libfftw3l.lib`
- 把 `libfftw3-3.dll`、`libfftw3f-3.dll`、`libfftw3l.dll` 复制到项目文件夹里，有 .vcxproj 文件的那个
- 设置项目为 64 位
- 项目属性->链接器->高级->目标计算机->MachineX64(/MACHINE:X64) 
- 头文件添加 `#include "fftw3.h"` 看下会不会报错

### Qt Creator 配置
- 项目路径下新建文件夹 bin、lib、include
- 将 `libfftw3-3.lib`、`libfftw3f-3.lib`、`libfftw3l.lib` 复制到 lib 文件夹
- 将 `libfftw3-3.dll`、`libfftw3f-3.dll`、`libfftw3l.dll` 复制到 bin 文件夹
- 将 `lltw3.h` 复制到 include 文件夹
- 项目-添加库-外部库-选取对应lib文件，取消 `为 debug 版本添加 'd' 作为后缀` 选项-添加
- pro 文件夹下生成配置内容如下：
``` bash
win32: LIBS += -L$$PWD/lib/ -llibfftw3-3
win32: LIBS += -L$$PWD/lib/ -llibfftw3f-3
win32: LIBS += -L$$PWD/lib/ -llibfftw3l-3

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
```
- 项目-运行设置-Working directory 路径设置为 bin 目录路径

## Qt Multimedia 多媒体库的使用
### QAudioFormat
参数描述
|        参数        |   说明   |                                        描述                                        |
| ------------------ | -------- | ---------------------------------------------------------------------------------- |
| Sample Rate        | 采样率   | 每秒音频数据采样数 单位 赫兹                                                       |
| Number of channels | 信道数   | 音频通道数 一个单声道 或 两个用于立体声 (typically one for mono or two for stereo) |
| Sample size        | 样本大小 | 每个样本中存储了多少数据 (typically 8 or 16 bits)                                  |
| Sample type        | 样本类型 | 样本的数字表示法 (typically signed integer, unsigned integer or float)             |
| Byte order         | 字节顺序 | 样本字节顺序 小尾数/大尾数 (typically little endian, big endian)                   |

### QAudioOutput
- 引用
``` C++
// QT += multimedia
#include <QObject>
#include <QAudioOutput>
```

### QAudioInput
``` C++
// QT += multimedia
#include <QObject>
#include <QAudioInput>
```

## 音频测试
- 音频六大基本测试项目：电平、频率响应、总谐波失真加噪音、相位、串扰、信噪比
- 电平测试
  - 测试项目：输出电平、功率、增益
- 频率响应
  - 待测品受已知电平不同频率激励信号激励时的输出信号电平
  - 在待测品的频率范围内，从最低频到最高频的正弦波信号的扫描，并将结果绘与同一张电平
  - 


peak level大概是峰值电平的水平（这个不大重要，一般可无视）

RMS是均方根有效值，一般在音频方面用作有效值的意思。
低音通道的RMS，就是指低音通道的有效输出功率，这个功率参数是最有参考价值的我。




