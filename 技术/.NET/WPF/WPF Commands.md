# Windows Presentation Foundation (WPF)中的命令(Commands)简述

<small>
2007年09月03日 17:47:00 大可山人 阅读数 4030更多
分类专栏： WPF研究 GDI+图形类
版权声明：本文为博主原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接和本声明。
本文链接：https://blog.csdn.net/johnsuna/article/details/1770602

引用或转载时请保留以下信息：
大可山 [MSN:a3news(AT)hotmail.com]
http://www.zpxp.com http://www.brawdraw.com
萝卜鼠在线图形图像处理
</small>

在我们日常的应用程序操作中，经常要处理各种各样的命令和进行相关的事件处理，比如需要复制、粘贴文本框中的内容;上网查看网页时，可能需要返回上一网页查看相应内容;而当我们播放视频和多媒体时，我们可能要调节音量，快速拖动到我们想看的片段等等。在Winform编程中，我们经常使用各种各样的控件来解决此类问题，当然我们也必须编写一堆代码来处理各种各样的命令和事件处理。那么，Windows Presentation Foundation (WPF)作为微软新一代图形图像支援系统，它是如何处理这些命令及事件的呢？

在WPF中，**许多控件都自动集成了固有的命令集**。比如文本框TextBox就提供了复制(Copy),粘贴(Paste),裁切(Cut),撤消(Undo)和重做(Redo)命令等。

WPF提供常用应用程序所用的命令集，常用的命令集包括：ApplicationCommands, ComponentCommands, NavigationCommands, MediaCommands和EditingCommands。

## ApplicationCommands（应用程序命令）:
 CancelPrint:取消打印
 Close：关闭
 ContextMenu：上下文菜单
 Copy：复制
 CorrectionList： Gets the value that represents the Correction List command. 
 Cut：剪切
 Delete：删除
 Find：查找
 Help：帮助
 New：新建
 NotACommand：不是命令，被忽略
 Open：打开
 Paste：粘贴
 Print：打印
 PrintPreview：打印预览
 Properties：属性
 Redo：重做
 Replace：取代
 Save：保存
 SaveAs：另存为
 SelectAll：选择所有的
 Stop：停止
 Undo：撤消

## ComponentCommands（组件命令）:
 ExtendSelection：后接Down/Left/Right/Up, 比如：ExtendSelectionDown（Shift+Down,Extend Selection Down)，ExtendSelectionLeft等
 Move：后接Down/Left/Right/Up, 如：MoveDown
 MoveFocus：后接Down/Forward/Back/Up, 如：MoveFocusDown
 MoveFocusPage：后接Down/Up,如：MoveFocusPageUp
 MoveTo：后接End/Home/PageDown/PageUp，比如：MoveToPageDown
 ScrollByLine
 ScrollPage：后接Down/Left/Right/Up，比如：ScrollPageLeft
 SelectTo：End/Home/PageDown/PageUp，比如：SelectToEnd

## NavigationCommands（导航命令）：
 Browse浏览: 后接Back/Forward/Home/Stop, 比如：BrowseBack
 缩放显示：DecreaseZoom, IncreaseZoom, Zoom
 Favorites（收藏）
 页面：FirstPage, LastPage, PreviousPage, NextPage,GoToPage
 NavigateJournal
 Refresh(刷新)
 Search（搜索）

## MediaCommands（多媒体控制命令）:
 Treble高音：DecreaseTreble,IncreaseTreble
 Bass低音:BoostBass,DecreaseBass,IncreaseBass
 Channel频道：ChannelDown,ChannelUp
 MicrophoneVolume麦克风音量调节:DecreaseMicrophoneVolume,IncreaseMicrophoneVolume,MuteMicrophoneVolume
 ToggleMicrophoneOnOff:麦克风开关
 Volume音量: DecreaseVolume,IncreaseVolume,MuteVolume
 Rewind, FastForward(回放，快进)
 Track轨道:PreviousTrack,NextTrack [上一段(节)]
 Play,Pause,Stop,Record(播放，暂停，停止，录制)
 TogglePlayPause
 Select选择

## EditingCommands（编辑/排版类命令）:
 Align对齐：AlignCenter,AlignJustify,AlignLeft,AlignRight(居中，撑满，左对齐，右对齐)
 Backspace退格
 TabForward,TabBackward(Tab前缩，Tab向后)
 FontSize字体大小：DecreaseFontSize,IncreaseFontSize
 Indentation缩排：DecreaseIndentation, IncreaseIndentation
 Delete删除: Delete选中部分，DeleteNextWord：删除后一字,DeletePreviousWord：删除前一字
 EnterLineBreak：换行
 EnterParagraphBreak：换段
 CorrectSpellingError/IgnoreSpellingError：纠正/忽略拼写错误
 MoveUpByLine,MoveDownByLine: 上/下移一行，
 MoveUpByPage,MoveDownByPage: 上/下移一页
 MoveUpByParagraph,MoveDownByParagraph: 上/下移一段
 MoveLeftByCharacter/MoveRightByCharacter：左/右移一字符
 MoveLeftByWord/MoveRightByWord 左/右移一词
 MoveToDocumentStart/MoveToDocumentEnd:到文章开头/结尾
 MoveToLineStart/MoveToLineEnd:到一行的开头/结尾
 SelectUpByLine,SelectDownByLine：向上/下选一行
 SelectUpByPage,SelectDownByPage：向上/下选一页
 SelectUpByParagraph,SelectDownByParagraph：向上/下选一段
 SelectLeftByCharacter,SelectRightByCharacter:向左/右选中一字
 SelectLeftByWord,SelectRightByWord:向左/右选中一词
 SelectToDocumentStart,SelectToDocumentEnd: 选中到篇头/篇尾
 SelectToLineStart/SelectToLineEnd:选中到行首/行尾
 ToggleBold, ToggleItalic, ToggleUnderline(加粗，斜体，下划线)
 ToggleBullets, ToggleNumbering(列表：加点，加数字)
 ToggleInsert:插入
 ToggleSuperscript,ToggleSubscript(上标字，下标字)


先来举一个简单的例子：

XAML代码:
``` XML
<StackPanel>
  <Menu>
    <MenuItem Command="ApplicationCommands.Paste" />
  </Menu>
  <TextBox />
</StackPanel>
```
C#代码:
``` CSharp
StackPanel mainStackPanel = new StackPanel();
TextBox pasteTextBox = new TextBox();
Menu stackPanelMenu = new Menu();
MenuItem pasteMenuItem = new MenuItem();

stackPanelMenu.Items.Add(pasteMenuItem);
mainStackPanel.Children.Add(stackPanelMenu);
mainStackPanel.Children.Add(pasteTextBox);

pasteMenuItem.Command = ApplicationCommands.Paste;
```
上面代码演示了将对文本框设置为焦点时，菜单项可用，点击菜单项时，将执行粘贴命令。


## 下面列出关于Command的四个概念和四个小问题：
### 1、WPF中Command(命令)的四个概念：
- (1)命令command:要执行的动作。
- (2)命令源command source：发出命令的对象（继承自ICommandSource）。
- (3)命令目标command target：执行命令的主体
- (4)命令绑定command binding：映射命令逻辑的对象
比如在上面示例中，粘贴（Paste）就是命令（command）, 菜单项(MenuItem)是命令源(command source), 文本框(TextBox)是命令目标对象(command target), 命令绑定到command binding文本框(TextBox)控件上。

提示：WPF中的命令都继承自ICommand接口。ICommand暴露两个方法：Execute方法、 CanExecute方法和一个事件：CanExecuteChanged。
继承自ICommandSource的有：ButtonBase, MenuItem, Hyperlink和InputBinding。
而Button，GridViewColumnHeader，ToggleButton，RepeatButton继承自ButtonBase。System.Windows.Input.KeyBinding和MouseBinding继承自InputBinding。

### 2、四个小问题：
#### （1）如何指定Command Sources?
XAML:（请将“ApplicationCommands.Properties”换成对应的ApplicationCommands属性值，比如：ApplicationCommands.Copy）
``` XML
<StackPanel>
  <StackPanel.ContextMenu>
    <ContextMenu>
      <MenuItem Command="ApplicationCommands.Properties" />
    </ContextMenu>
  </StackPanel.ContextMenu>
</StackPanel>
```
同等的C#代码：
``` CSharp
StackPanel cmdSourcePanel = new StackPanel();
ContextMenu cmdSourceContextMenu = new ContextMenu();
MenuItem cmdSourceMenuItem = new MenuItem();

cmdSourcePanel.ContextMenu = cmdSourceContextMenu;
cmdSourcePanel.ContextMenu.Items.Add(cmdSourceMenuItem);

cmdSourceMenuItem.Command = ApplicationCommands.Properties;
```

#### （2）如何指定快捷键？
XAML代码:
``` XML
<Window.InputBindings>
  <KeyBinding Key="B"
              Modifiers="Control"
              Command="ApplicationCommands.Open" />
</Window.InputBindings>
```
C#代码：
``` CSharp
KeyGesture OpenKeyGesture = new KeyGesture(
    Key.B,
    ModifierKeys.Control);

KeyBinding OpenCmdKeybinding = new KeyBinding(ApplicationCommands.Open,OpenKeyGesture);
this.InputBindings.Add(OpenCmdKeybinding);
//也可以这样（下面一句与上面两句的效果等同）：
//ApplicationCommands.Open.InputGestures.Add(OpenKeyGesture);
```

#### （3）如何Command Binding？
XAML代码：
``` XML
<Window.CommandBindings>
  <CommandBinding Command="ApplicationCommands.Open"
                  Executed="OpenCmdExecuted"
                  CanExecute="OpenCmdCanExecute"/>
</Window.CommandBindings>
```
C#代码：
``` CSharp
CommandBinding OpenCmdBinding = new CommandBinding(
    ApplicationCommands.Open,
    OpenCmdExecuted,
    OpenCmdCanExecute);

this.CommandBindings.Add(OpenCmdBinding);
```
具体的事件处理：
C#代码：
``` CSharp
void OpenCmdExecuted(object target, ExecutedRoutedEventArgs e)
{
    MessageBox.Show("The command has been invoked.");
}

void OpenCmdCanExecute(object sender, CanExecuteRoutedEventArgs e)
{
    e.CanExecute = true;
}
```
#### （4）如何设置Command Target并进行绑定Command Binding？
XAML代码：
``` XML
<StackPanel>
  <Menu>
    <MenuItem Command="ApplicationCommands.Paste"
              CommandTarget="{Binding ElementName=mainTextBox}" />
  </Menu>
  <TextBox Name="mainTextBox"/>
</StackPanel>
```
C#代码：
``` CSharp
StackPanel mainStackPanel = new StackPanel();
TextBox mainTextBox= new TextBox();
Menu stackPanelMenu = new Menu();
MenuItem pasteMenuItem = new MenuItem();

stackPanelMenu.Items.Add(pasteMenuItem);
mainStackPanel.Children.Add(stackPanelMenu);
mainStackPanel.Children.Add(mainTextBox);

pasteMenuItem.Command = ApplicationCommands.Paste;
```
以上例子全是单条命令绑定的情形，事实上，你也可以多个按钮多条命令绑定到同一控件上，比如：
``` XML
<StackPanel xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
Orientation="Horizontal" Height="25">
<Button Command="Cut" CommandTarget="{Binding ElementName=textBoxInput}" Content="{Binding RelativeSource={RelativeSource Self}, Path=Command.Text}"/>
<Button Command="Copy" CommandTarget="{Binding ElementName=textBoxInput}" Content="{Binding RelativeSource={RelativeSource Self}, Path=Command.Text}"/>
<Button Command="Paste" CommandTarget="{Binding ElementName=textBoxInput}" Content="{Binding RelativeSource={RelativeSource Self}, Path=Command.Text}"/>
<Button Command="Undo" CommandTarget="{Binding ElementName=textBoxInput}" Content="{Binding RelativeSource={RelativeSource Self}, Path=Command.Text}"/>
<Button Command="Redo" CommandTarget="{Binding ElementName=textBoxInput}" Content="{Binding RelativeSource={RelativeSource Self}, Path=Command.Text}"/>
<TextBox x:Name="textBoxInput" Width="200"/>
</StackPanel>
```
最后，贴出一个完整点的例子：

XAML代码：
``` XML
<Window
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    x:Class="WPFCommand.Window1"
    Title="MenuItemCommandTask"
 x:Name="Window"
 Width="500"
 Height="400"
    >
<Window.CommandBindings>
  <CommandBinding Command="ApplicationCommands.Open"
                  Executed="OpenCmdExecuted"
                  CanExecute="OpenCmdCanExecute"/>
<CommandBinding Command="Help" CanExecute="HelpCanExecute" Executed="HelpExecuted" />
</Window.CommandBindings>
<Window.InputBindings>
  <KeyBinding Command="Help" Key="F2" />
  <KeyBinding Command="NotACommand" Key="F1" />
</Window.InputBindings>
    <Canvas>
      <Menu DockPanel.Dock="Top">
        <MenuItem Command="ApplicationCommands.Paste" Width="75" />
      </Menu>
      <TextBox BorderBrush="Black" BorderThickness="2" TextWrapping="Wrap" Text="这个TextBox未成为焦点之前，粘贴菜单不可用。" Width="476" Height="41" Canvas.Left="8" Canvas.Top="25"/>
   <Button Command="ApplicationCommands.Open" Height="32" Width="223" Content="测试弹出对话框" Canvas.Left="8" Canvas.Top="70"/>
    </Canvas>
</Window>
```
对应的C#代码：
``` CSharp
using System;
using System.IO;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Navigation;

namespace WPFCommand
{
 public partial class Window1
 {
  public Window1()
  {
   this.InitializeComponent();
  }
        void OpenCmdExecuted(object target, ExecutedRoutedEventArgs e)
        {
            MessageBox.Show("测试弹出对话框，命令已执行！");
        }

        void OpenCmdCanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        void HelpCanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        void HelpExecuted(object sender, ExecutedRoutedEventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.BrawDraw.com/");
        }
 }
}
```

你不妨试试在程序执行之后，按下F1或F2试试效果，是不是按F2时浏览器指向"http://www.BrawDraw.com/"，而按F1时没有任何效果？这是因为这两句：
``` XML
  <KeyBinding Command="Help" Key="F2" />
  <KeyBinding Command="NotACommand" Key="F1" />
```
当按F2时，Help命令执行;当按F1时，由于Command="NotACommand"，即窗口忽略此命令的执行。
