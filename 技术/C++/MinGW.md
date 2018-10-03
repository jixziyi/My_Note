# MinGW

## 安装
访问MinGW 64 [网站](#http://mingw-w64.org/doku.php/start)
下载 [MinGW-w64 - for 32 and 64 bit Windows](#https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/installer/mingw-w64-install.exe/download)

## VS Code C/C++插件配置
``` json
{
    "name": "MinGW",
    "intelliSenseMode": "gcc-x64",
    "compilerPath": "C:/mingw64/bin/gcc.exe",
    "includePath": [
        "${workspaceFolder}"
    ],
    "defines": [],
    "cStandard": "c11",
    "cppStandard": "c++17"
}
```

