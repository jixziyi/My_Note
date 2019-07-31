# SharpDevelop 开发教程
- Pad 面板就是 SharpDevelop 中的停靠窗口。
- View 是 SharpDevelop 的基础部分，显示于 MPI 窗口选项卡页面上的面板。

# SharpDevelop 代码分析
SharpDevelop 实现了强大的插件系统，所有界面和功能都是通过插件的形式挂入的
- AddInTree 插件树
  - 树的结构是通过 Extension 扩展点中定义的 Path 来定义的
  - 在系统中可以通过 AddTreeSingleton 对象来访问各个插件，以实现插件之前的互动
- AddIn 插件
  - 插件时包含多个功能模块的合集，在文件上的形式时 addin 配置文件，在系统中对应 AddIn 类
- Extension 扩展点
  - 通过 Extension 对象中的 Path 指定插件挂到 AddInTree 插件树中的哪个位置
``` XML
<Extension path="/SharpDevelop/Workbench/Ambiences">
  <Class id=".NET" class="ICSharpCode.SharpDevelop.Services.NetAmbience" />
</Extension>
```
- Codon
  - Codon 描述一个功能模块，一个功能模块对应一个实现了具体功能的 Command 类
  - 基本属性：ID、Name，其中 ID 才是真正的名称， Name 可能是 Class 类、MenuItem 菜单项、Pad 面板等
  - SharpDevelop 定义了 ClassCodon、MenuCodon、PadCodon 等对象
``` XML
<!-- 此处 Codon 对应系统中的 MenuCodon 对象 -->
<Extension path="/SharpDevelop/Views/ProjectBrowser/ContextMenu/CombineBrowserNode">
  <MenuItem id="Compile" label="${res:XML.MainMenu.RunMenu.Compile}"
    class="ICSHarpCode.SharpDevelop.Commands.Compile" />
</Extension>
```
- Command 命令
  - Codon 描述一个功能模块，每个模块都是一个 ICommand 的实现
  - 最基本的 Command 就是 AbstractCommand，根据 Codon 的不同对应了不同的 Command
  - 例如 MenuCodon 对应 MenuCommand 等
- Service 服务
  - 插件系统中，有一些功能是整个系统都要使用的，如文件访问、资源、消息等
  - 通过 ServiceManager 来管理这些基本功能
  - Service 的扩展路径在目录树的 /Services 中

# C# 软件项目开发全程剖析 - 全面透视 SharpDevelop 软件开发内幕

## 第01章 功能简介
### 1.1 SharpDevelop 的设计理念

## 第02章 体系结构设计

## 第05章 通过工作区服务提供功能
### 5.1 实现考虑事项
定义只含静态成员的类，使其他需要这些服务的对象可以访问它们。

