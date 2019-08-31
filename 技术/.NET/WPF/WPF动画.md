# WPF 动画

## 基本动画
本质上 WPF 动画只不过是在一段时间间隔内修改依赖项属性值的一种方式，可以只关注动画定义，不考虑它们的渲染方式。
为了实现属性的动态化，需要有支持相应数据的动画类。
> Button.Width 为 double 类型，需要使用 DoubleAnimation 类
> Button.Padding 为 Thickness 结构，需使用 ThicknessAnimation 类

## Animation 类
WPF 动画使用三种方法：线性插值、关键帧、路径。所有数据类型都支持关键帧动画。
在 System.Windows.Media.Animation 名称空间中有一下内容
  1. 7个“类型名+Animation类”这些类使用插值动画。
  2. 22个“类型名+AnimationUsingKeyFrames”这些类使用关键帧动画。
  3. 3个“类型名+AnimationUsingPath”这些类使用基于路径的动画。

## 使用代码创建动画
WFP 中，最常用的动画技术是线性插值动画，标准帧数率是 60 帧/秒。使用动画最简单方式是实例化在前面列出的一个动画类，然后使用修改元素的 `BeginAnimation()` 方法。所有 WPF 元素，从 UIElement 基类开始，都继承了 `BeginAnimation()` 方法，该方法是 IAnimatable 接口的一部分。

``` XML
<Button Width="150" Height="60" Grid.Row="0" Click="Button_Click">点击开始动画</Button>
<Button Grid.Row="1" Name="btn1" Width="150" Height="60" Content="动画按钮"></Button>
```

``` CSharp
private void Button_Click(object sender, RoutedEventArgs e)
{
  // 实例化一个DoubleAnimation类
  DoubleAnimation doubleAnimation = new DoubleAnimation();
  // 设置From属性
  doubleAnimation.From = btn1.Width;
  // 设置To属性
  doubleAnimation.To = 250;
  // 设置Duration属性
  doubleAnimation.Duration = new Duration(TimeSpan.FromSeconds(5));
  // 为元素设置 BeginAnimation 方法
  btn1.BeginAnimation(Button.WidthProperty, doubleAnimation);
}
```

## 同时发生的动画
可以创建多个 Animation 动画，然后为元素设置属性

``` CSharp
private void Button_Click(object sender, RoutedEventArgs e)
{
  // 实例化一个 DoubleAnimation 类
  DoubleAnimation doubleAnimation = new DoubleAnimation();
  // 设置 From 属性
  doubleAnimation.From = btn1.Width;
  // 设置 To 属性
  doubleAnimation.To = 250;
  // 设置 Duration 属性
  doubleAnimation.Duration = new Duration(TimeSpan.FromSeconds(5));
  // 为元素设置 BeginAnimation 方法
  btn1.BeginAnimation(Button.WidthProperty, doubleAnimation);

  // 实例化一个 DoubleAnimation 动画，用于设置元素的 Height
  DoubleAnimation doubleAnimationHeight = new DoubleAnimation();
  // 设置 From 属性
  doubleAnimationHeight.From = btn1.Height;
  // 设置 To 属性
  doubleAnimationHeight.To = 70;
  // 设置 Duration 属性
  doubleAnimationHeight.Duration = new Duration(TimeSpan.FromSeconds(3));
  // 开始动画
  btn1.BeginAnimation(Button.HeightProperty, doubleAnimationHeight);
}
```

## 动画的生命周期
当 WPF 动画处于活动状态时，只是覆盖了属性的值。
单向动画，在动画运行结束后会保持处于活动状态，这是因为动画需要将按钮的宽度保持为新值，**如果尝试使用代码在动画完成后修改属性值，代码将不会起作用，因为代码只是为属性制定了一个新的本底值，但仍会先试用动画之后的属性。有以下方法解决：
> 设置 AutoReverse 属性，如果将该属性设置为 true，将会反向运动，返回原始的值。
> 改变 FillBehavior 属性。通常，FillBehavior 属性设置 HoldEnd，这意味着当动画结束时，会继续为目标元素应用最后的值。如果将 FillBehavior 属性改为 Stop，只要动画结束，属性就会恢复为原来的值（适用于动画结束后，再次为其设置新值，一般不与 AutoReverse 配合使用，这两个用其中一个就行了）。

## 动画的 Completed 事件
使用 Completed 事件时，要将 **事件设置 BeginAnimation() 方法之前，否则不起作用**。在 Completed 中，可通过调用 BeginAnimation() 方法来渲染不活动的动画，为此，只需要指定属性，并未动画传递 null 引用。
``` CSharp
void doubleAnimationHeight_Completed(object sender, EventArgs e)
{
  MessageBox.Show("动画的高执行完毕了！！！");
  btn1.BeginAnimation(Button.HeightProperty, null);
}
```

## TimeLine类
TimeLine 类常用属性

|                名称                |                                              说明                                              |
| ---------------------------------- | ---------------------------------------------------------------------------------------------- |
| BeginTime                          | 设置将被添加到动画开始之前的延时事件，延时将会加载到总时间，具有5秒延时的5秒动画，总时间时10秒 |
| Duration                           | 动画开始到结束的运行时间                                                                       |
| SpeedRatio                         | 提高或减慢动画速度。SpeedRatio属性值为1，如果改成5，动画速度变为原来的5倍                      |
| AcclerationRatio/DecelerationRatio | 使动画不是线性的，从而开始时慢或开始时快，两个属性值之和不能超过1                              |
| AutoReverse                        | 如果为true，当动画播放完成后会自动反向播放，返回到原始值                                       |
| FillBehavior                       | 决定当动画结束时，如何操作                                                                     |
| RepeatBehavior                     | 通过该属性，可以使用指定次数或时间间隔重复动画                                                 |

## AcclerationRatio 和 DecelerationRatio 属性
设置动画的加速度和减速度，按百分比计算。
``` CSharp
private void Button_Click(object sender, RoutedEventArgs e)
{
  DoubleAnimation doubleAnimation = new DoubleAnimation();
  doubleAnimation.From = btn1.Width;
  doubleAnimation.AcclerationRatio = 0.5;   // 前5秒加速度
  doubleAnimation.DecelerationRatio = 0.2;  // 后2秒开始加速
  doubleAnimation.To = 1000;
  doubleAnimation.Duration = new Duration(TimeSpan.FromSeconds(10));
  btn1.BeginAnimation(Button.WidthProperty, doubleAnimation);
}
```

## RepeatBehavior 属性
使用 RepeatBehavior 属性可以控制如何重复运行动画。可以设置固定次数，也可以设置为永久重复。
``` CSharp
doubleAnimation.RepeatBehavior = new RepeatBehavior(3);
doubleAnimation.RepeatBehavior = RepeatBehavior.Forever;
```

## 故事板 Storyboard
> 故事板：是 `BeginAnimation()` 方法的 XAML 等价物，通过故事板将动画指定到合适的元素和属性。
> 事件触发器：事件触发器响应属性变化或事件(如按钮的Click事件)，并控制故事板。

### 故事板
故事板是增强的时间线，可用来分组多个动画，而且具有控制动画播放的能力 -> 暂停、停止以及播放位置。
Storyboard 类提供的最基本功能是，能够使用 TargetProperty 和 TargetName 属性指向某个特定属性和特定元素，换句话说，故事板在动画和希望应用动画的属性之间架起了一座桥梁。其中 TargetProperty 属性和 TargetName 属性都是附加属性。
``` XML
<!-- 创建一个故事板 -->
<Storyboard Storyboard.TargetProperty="Width">
  <!-- 创建一个 DoubleAnimation 类 -->
  <DoubleAnimation To="350" RepeatBehavior="Forever" Duration="0:0:3"></DoubleAnimation>
</Storyboard>

<!-- 由于 Storyboard.TargetProperty 属性是附加属性，因此还可以写出 -->
<Storyboard>
  <!-- 创建一个 DoubleAnimation 类 -->
  <DoubleAnimation Storyboard.TargetProperty="Width" To="350" RepeatBehavior="Forever" Duration="0:0:3"></DoubleAnimation>
</Storyboard>
```

### 事件触发器
可以在以下4个位置定义事件触发器
1. 在样式中 Style.Triggers 集合
2. 在数据模板中 DataTemplate.Triggers 集合
3. 在控件模板中 ControlTemplate.Triggers 集合
4. 直接在元素中定义事件触发器 FrameworkElement.Triggers 集合

当创建事件触发器时，需要指定开始触发器的路由事件和触发器执行的一个或多个动作。对于动画，最常用的动作是 BeginStoryboard，该动作相当于调用 BeginAnimation() 方法。**所有事件触发器都可以启动动作，所有动作都由继承自 System.Windows.TriggerAction 的类表示。**

``` XML
<Button Width="200" Height="80" Content="事件触发器" FontSize="20">
  <!-- 元素触发器 -->
  <Button.Triggers>
    <!-- 定义事件触发器 -->
    <EventTrigger RoutedEvent="Button.Click">
      <!-- 执行一个动作 -->
      <EventTrigger.Actions>
        <!-- 开始故事板 -->
        <BeginStoryboard>
          <!-- 故事板 -->
          <Storyboard>
            <!-- 创建一个 DoubleAnimation 类 -->
            <DoubleAnimation Storyboard.TargetProperty="Width" To="350" RepeatBehavior="Forever" Duration="0:0:3"></DoubleAnimation>
          </Storyboard>
        </BeginStoryboard>
      </EventTrigger.Actions>
    </EventTrigger>
  </Button.Triggers>
</Button>
```

## 使用样式关联触发器
有三种基本类型的 WPF 触发器：属性触发器、数据触发器以及事件触发器。
使用触发器是关联动画的最常用方式，但并不是唯一的选择。
``` XML
<Window.Resources>
  <Style TargetType="Button">
    <Setter Property="FontSize" Value="20"></Setter>
    <Style.Triggers>
      <!-- 使用属性触发器 -->
      <Triggers Property="IsPressed" Value="True">
        <!-- 在这里使用的是 EnterActions -->
        <Triggers.EnterActions>
          <BeginStoryboard>
            <Storyboard Storyboard.TargetProperty="Width">
              <DoubleAnimation To="350" RepeatBehavior="Forever" Duration="0:0:3"></DoubleAnimation>
            </Storyboard>
          </BeginStoryboard>
        </Triggers.EnterActions>
      </Triggers>
    </Style.Triggers>
  </Style>
</Window.Resources>

<Grid>
  <Button Width="200" Height="80" Content="使用样式关联触发器"></Button>
</Grid>
```

## 同步的动画
Storyboard 类间接地继承自 TimeLineGroup 类，所以 Storyboard 类能包含多个动画，这些动画可以作为一组进行管理，这意味着它们可以在同一时间开始。
``` XML
<Window.Resources>
  <Style TargetType="Button">
    <Setter Property="FontSize" Value="20"></Setter>
    <Style.Triggers>
      <Trigger Property="IsPressed" Value="True">
        <Trigger.EnterActions>
          <BeginStoryboard>
            <Storyboard>
              <DoubleAnimation Storyboard.TargetProperty="Width" To="300" Duration="0:0:3"></DoubleAnimation>
              <DoubleAnimation Storyboard.TargetProperty="Height" To="100" Duration="0:0:3"></DoubleAnimation>
            </Storyboard>
          </BeginStoryboard>
        </Trigger.EnterActions>
      </Trigger>
    </Style.Triggers>
  </Style>
</Window.Resources>

<Grid>
  <Button Width="150" Height="60" Content="同步动画"></Button>
</Grid>
```

## 控制播放
一旦创建了故事板，就可以使用其他动作控制故事板，这些动作类都继承自 ControlableStoryboardAction 类，控制故事板主要类如下：

|          名称           |                                                    说明                                                    |
| ----------------------- | ---------------------------------------------------------------------------------------------------------- |
| PauseStoryboard         | 停止播放动画并且保持当前位置                                                                               |
| ResumeStoryboard        | 恢复播放动画                                                                                               |
| StopStoryboard          | 停止播放动画，并将动画时钟重新设置到开始位置                                                               |
| SeekStoryboard          | 跳到动画时间线中的特定位置，如果当前动画正在播放，就继续从新位置播放。如果当前动画是暂停的，就继续保持暂停 |
| SetStoryboardSppedRatio | 改变故事板的 SpeedRatio 属性                                                                               |
| SkipStoryboardToFill    | 将故事板移动到时间线的终点。FillBehavior 属性设置为 HoldEnd，动画继续保持最后的值                          |
| RemoveStoryboard        | 移除故事板，停止所有正在运行的动画，并将属性返回为原来的、最后一次设置的数值                               |

**为成功地执行这些动作，必须在同一个Triggers集合中定义所有的触发器，如果将BeginStoryboard动作的触发器和PauseStoryboard动作的触发器放置到不同的集合中，PauseStoryboard动作就无法工作。**

``` XML
<Window x:Class="控制播放.MainWindow"
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
  Title="MainWindow" Height="350" Width="525">
  <Window.Triggers>
    <EventTrigger RoutedEvent="Button.Click" SourceName="btn_start">
      <BeginStoryboard Name="beginstoyboard1">
        <Storyboard>
          <DoubleAnimation Storyboard.TargetProperty="img" Storyboard.TargetProperty="Opacity" From="1" To="0" Duration="0:0:3"></DoubleAnimation>
        </Storyboard>
      </BeginStoryboard>
    </EventTrigger>

    <EventTrigger RoutedEvent="Button.Click" SourceName="btn_pause">
      <PauseStoryboard BeginStoryboardName="beginstoyboard1"></PauseStoryboard>
    </EventTrigger>

    <EventTrigger RoutedEvent="Button.Click" SourceName="btn_resume">
      <ResumeStoryboard BeginStoryboardName="beginstoyboard1"></ResumeStoryboard>
    </EventTrigger>

    <EventTrigger RoutedEvent="Button.Click" SourceName="btn_stop">
      <StopStoryboard BeginStoryboardName="beginstoyboard1"></StopStoryboard>
    </EventTrigger>

    <EventTrigger RoutedEvent="Button.Click" SourceName="btn_remove">
      <RemoveStoryboard BeginStoryboardName="beginstoyboard1"></RemoveStoryboard>
    </EventTrigger>
  </Window.Triggers>
  
  <Grid>
    <Grid.RowDefinitions>
      <RowDefinitions Height="3*"></RowDefinitions>
      <RowDefinitions></RowDefinitions>
    </Grid.RowDefinitions>

    <Image Name="img" Source="1.jpg"></Image>

    <Grid Grid.Row="1">
      <Grid.ColumnDefinitions>
        <ColumnDefinitions></ColumnDefinitions>
        <ColumnDefinitions></ColumnDefinitions>
        <ColumnDefinitions></ColumnDefinitions>
        <ColumnDefinitions></ColumnDefinitions>
        <ColumnDefinitions></ColumnDefinitions>
      </Grid.ColumnDefinitions>
      <Button Name="btn_start" Content="开始" Margin="10" FontSize="20" Grid.Column="0"></Button>
      <Button Name="btn_pause" Content="暂停" Margin="10" FontSize="20" Grid.Column="1"></Button>
      <Button Name="btn_resume" Content="恢复" Margin="10" FontSize="20" Grid.Column="2"></Button>
      <Button Name="btn_stop" Content="停止" Margin="10" FontSize="20" Grid.Column="3"></Button>
      <Button Name="btn_remove" Content="移除" Margin="10" FontSize="20" Grid.Column="4"></Button>
    </Grid>
  </Grid>
</Window>
```

## 故事板事件
|             名称              |                                         说明                                         |
| ----------------------------- | ------------------------------------------------------------------------------------ |
| Completed                     | 动画已经到达终点                                                                     |
| CurrentGlobalSpeedInvalidated | 速度发生了变化，或者动画被暂停、重新开始、停止或移动到某个新的位置                   |
| CurrentStateInvalidated       | 动画已经开始或结束                                                                   |
| CurrentTimeInvalidated        | 动画时钟已经向前移动了一个步长，正在更改动画。当动画开始、停止或结束时也会引发该事件 |
| RemoveRequested               | 动画正在被移除                                                                       |

### 监视动画进度
如果要监视动画进度，可以使用 CurrentTimeInvalidated 事件，每次向前移动动画时钟都会引发该事件。
``` CSharp
private void Storyboard_CurrentTimeInvalidated(object sender, EventArgs e)
{
  Clock storyboardClock = (Clock) sender;
  if (storyboardClock.CurrentProgress == null)
  {
    lblTime.Content = "";
    progressBar1.Value = 0;
  }
  else
  {
    lblTime.Content = storyboardClock.CurrentTime.ToString();
    progressBar1.Value = (double) storyboardClock.CurrentProgress;
  }
}
```

## 动画缓动
WPF 预置缓动函数 EasingFunction
``` XML
<Window.Resources>
  <Style TargetProperty="Button">
    <Style.Triggers>
      <EventTrigger RoutedEvent="Button.Click">
        <EventTrigger.Actions>
          <BeginStoryboard>
            <Storyboard Storyboard.TargetProperty="Width">
              <DoubleAnimation To="300" Duration="0:0:3">
                <!-- 使用缓动函数 -->
                <DoubleAnimation.EasingFunction>
                  <!-- 设置缓动模式和震荡次数 -->
                  <ElasticEase EasingMode="EaseOut" Oscillations="5"></ElasticEase>
                </DoubleAnimation.EasingFunction>
              </DoubleAnimation>
            </Storyboard>
          </BeginStoryboard>
        </EventTrigger.Actions>
      </EventTrigger>
    </Style.Triggers>
  </Style>
</Window>
```

## 缓动函数类
所有缓动函数都继承自 EasingFunctionBase 类，并且继承了 EasingMode 属性。
EasingMode 有三种值，EasyIn 动画开始时应用/EasyOut 动画结束时引用/EasyInOut 开始和结束时都应用，应用缓动函数不会改变动画的持续时间。

## 自定义缓动函数
创建自定义缓动函数一般需要一下几个步骤
1. 新建一个类，让其继承 EasingFunctionBase 类
2. 重写 EaseInCore() 方法和 CreateInstanceCore() 方法
3. 定义依赖属性
4. 引用

``` CSharp
public class RandomJitterEase : EasingFunctionBase
{
  Random rand = new Random();

  protected override double EaseInCore(double normalizedTime)
  {
    // 几乎所有的逻辑代码都在 EaseInCore 种运行，该方法接收一个规范化的值，本质上表示动画进度从 0 到 1 之间的值
    // 当动画开始时，规范化的时间值时0，它从该点开始增加，直到在动画结束点达到1
    // 在动画运行期间，每次更新动画值时，WPF 都会调用 EaseInCore 方法，确切的调用频率取决于动画的帧率
    if (normalizedTime == 1)
    {
      return 1;
    } 
    else 
    {
      return Math.Abs(normalizedTime - (double)rand.Next(0,10) / (2010 - Jitter));
    }
  }

  protected override System.Windows.Freezable CreateInstanceCore()
  {
    return new RandomJitterEase();
  }

  public static readonly DependencyProperty JitterProperty;
  static RandomJitterEase()
  {
    JitterProperty = DependencyProperty.Register("Jitter", typeof(int), typeof(RandomJitterEase), new UIPropertyMetadata(1000),
    new ValidateValueCallback(ValidateJitter));
  }

  public int Jitter
  {
    get { return (int) GetValue(JitterProperty); }
    set { SetValue(JitterProperty, value); }
  }

  private static bool ValidateJitter(object value)
  {
    int jitterValue = (int)value;
    if (jitterValue <= 2000 && jitterValue >= 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
}
```
``` XML
<Window x:Class="自定义缓动函数.MainWindow"
  xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
  xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
  xmlns:local="clr-namespace:自定义缓动函数"
  Title="MainWindow" Height="350" Width="525">
  <Window.Triggers>
    <EventTrigger RoutedEvent="Window.Loaded">
      <EventTrigger.Actions>
        <BeginStoryboard>
          <Storyboard>
            <DoubleAnimation Storyboard.TargetName="ellipse1" Storyboard.TargetProperty="(Canvas.Left)" From="0" To="480" Duration="0:0:3">
              <DoubleAnimation.EasingFunction>
                <!-- 调用自定义寒冬函数类 -->
                <local:RandomJitterEase EasingMode="EaseIn" Jitter="1500"></local:RandomJitterEase>
              </DoubleAnimation.EasingFunction>
            </DoubleAnimation>
          </Storyboard>
        </BeginStoryboard>
      </EventTrigger.Actions>
    </EventTrigger>
  </Window.Triggers>
</Window>
```


## WPF 动画性能和帧率
WPF 默认帧率为 60 帧/秒，可以通过 TimeLine.DesiredFrameRate 属性进行调整。

``` XML
<Storyboard TimeLine.DesiredFrameRate="100">
</Storyboard>
```

