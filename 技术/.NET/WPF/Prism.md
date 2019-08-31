# Prism

## 简介
Prism 是一个用于 WPF、Window 10 UWP 和 Xamarin 形式构建松散耦合、可维护和可测试的 XAML 应用程序。Prism 提供了一组设计模式的实现，这些设计模式有助于编写结构良好且可维护的 XAML 应用程序，包括 MVVM、依赖注入、命令、EventAggregator(事件聚合器)等。

## Commanding
除了提供对要在视图中显示或编辑的数据的访问，ViewModel 还可能定义一个或多个用户可以执行的 actions 或 operations。用户可以通过 UI 执行的操作通常定义为 Commands。Commands 提供了一种方便的方法来标识可以轻松绑定到 UI 中控件的 actions 或 operations。它们封装了实现 actions 或 operations 的实际代码，并帮助其与视图中的实际可视表示分离。

视图中的 UI 控件和命令之间的交互可以是双向的。可以在用户与 UI 交互时调用该命令，并且可以在底层命令启用或禁用时自动启用或禁用该 UI。

ViewModel 可以作为 Commands 对象(实现 ICommand 接口的对象)来实现命令。实现 ICommand 接口很简单，prism 提供了这个接口的 DelegateCommand 实现。

### 创建 DelegateCommand
prism DelegateCommand 类封装了两个委托来引用在 ViewModel 类中实现的方法。它通过调用这些委托来实现 ICommand 接口的 Execute 和 CanExecute 方法。
``` CSharp
public class ArticleViewModel
{
  public DelegateCommand SubmitCommand { get; private set; }
  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand<object>(Submit, CanSubmit);
  }

  void Submit(object parameter)
  {
    // implement logic
  }

  bool CanSubmit(object parameter)
  {
    return true;
  }
}
```
当对 DelegateCommand 对象调用 Execute 方法时，它只是通过在构造函数中指定的委托将调用转发到 ViewModel 类中的方法。同样，当调用 CanExecute 方法时，将调用 ViewModel 类中的响应方法。构造函数中 CanExecute 方法的委托时可选的。如果未指定委托， DelegateCommand 将始终为 CanExecute 返回 true。
``` CSharp
public class ArticleViewModel
{
  public DelegateCommand SubmitCommand { get; private set; }

  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand(Submit, Cansubmit);
  }

  void Submit()
  {
    // implement logic
  }

  bool CanSubmit()
  {
    return true;
  }
}
```
DelegateCommand 故意阻止使用值类型(int、double、bool等)。因为实现者无法区分有效值和默认值，如果要使用值类型，必须使用 `DelegateCommand<Nullable<int>>` 或者简写 `DelegateCommand<int?>`

### 从视图调用 DelegateCommand
`<Button Command="{Binding SubmitCommand}" CommandParameter="OrderId" />`
视图中的控件可以通过多种方式与 ViewModel 提供的命令对象关联。Command 参数可以使用 CommandParameter 属性定义。预期参数的类型在 DelegateCommand<T> 泛型声明中指定。当用户与该控件交互时，该控件自动调用目标命令，并且 Command 参数将作为参数传递给该命令的 Execute 方法。此外，如果指定了 CanExecute 委托，CanExecute 返回 false，按钮将自动禁用，返回 true 按钮将启用。

### Raising Change Notifications 引发更改通知
ViewModel 通常需要指明 CanExecute 状态的更改，以便绑定到 Command 的 UI 中的任何控件都将更新其启用状态。DelegateCommand 提供了几种将这些通知发送到 UI 的方法。

#### RaiseCanExecuteChanged
当需要手动更新绑定的 UI 元素的状态时，请使用 RaiseCanExecuteChanged 方法。例如，当 IsEnabled 属性值更改时，我们在属性的 setter 中调用 RaiseCanExecuteChanged 以通知 UI 状态更改。
``` CSharp
private bool _isEnabled;
public bool IsEnabled
{
  get { return _isEnabled; }
  set
  {
    SetProperty(ref _isEnabled, value);
    SubmitCommand.RaiseCanExecuteChanged();
  }
}
```

#### ObservesProperty
如果 Command 应用在属性值更改时发送通知，则可以使用 ObservesProperty 方法。使用 ObservesProperty 只要所提供属性的值发生更改，DelegateCommand 就会自动调用 RaiseCanExecuteChanged 事件通知 UI 状态更改。
``` CSharp
public class ArticleViewModel : BindableBase
{
  private bool _isEnabled;
  public bool IsEnabled
  {
    get { return _isEnabled; }
    set { SetProperty(ref _isEnabled, value); }
  }

  public DelegateCommand SubmitCommand { get; private set; }

  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand(Submit, CanSubmit).ObservesProperty(() => IsEnabled);
  }

  void Submit()
  {
    // implement logic
  }

  bool CanSubmit()
  {
    return IsEnabled;
  }
}
```
使用 ObservesProperty 方法时，可以链注册多个要观察的属性。
`ObservesProperty(() => IsEnabled).ObserversProperty(() => CanSave)`

#### ObservesCanExecute
如果 CanExecute 是简单的布尔属性的结果，则可以消除声明 CanExecute 委托的必要性，而改用 ObservesCanExecute 方法。 ObservesCanExecute 不仅在注册的属性值更改时向 UI 发送通知，还将使用与实际 CanExecute 委托相同的属性。
``` CSharp
public class ArticleViewModel : BindableBase
{
  private bool _isEnabled;
  public bool IsEnabled
  {
    get { return _isEnabled; }
    set { SetProperty(ref _isEnabled, value); }
  }

  public DelegateCommand SubmitCommand { get; private set; }

  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand(Submit, CanSubmit).ObservesCanExecute(() => IsEnabled);
  }

  void Submit()
  {
    // implement logic
  }
}
```

#### 实现基于任务的 DelegateCommand
在 Execute 委托中使用 `async/await` 关键字调用异步方法是一个非常常见的需求。但是 IComamnd 本质上是同步的，Execute 和 CanExecute 委托应该视为事件。这意味着 async void 对于 Command 是有效的语法。
``` CSharp
// Option 1
public class ArticleViewModel
{
  public DelegateCommand SubmitCommand { get; private set; }

  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand(Submit);
  }

  async void Submit()
  {
    await SomeAsyncMethod();
  }
}

// Option 2
public class ArticleViewModel
{
  public DelegateCommand SubmitCommand { get; private set; }

  public ArticleViewModel()
  {
    SubmitCommand = new DelegateCommand(async () => await Submit());
  }

  Task Submit()
  {
    return SomeAsyncMethod();
  }
}
```

## Composite Commands 复合 Command
许多情况下，由视图模型定义的命令将绑定到关联视图中的控件，以便用户可以直接从视图中调用该 Command。但是在某些情况下，您可能希望能够从应用程序 UI 的父视图中调用一个或多个视图模型上的命令。
例如：如果应用程序允许用户同时编辑多个项目，SaveAll 命令将为每个项调用视图模型实例实现的每个 Save 命令。

Prism 通过 CompositeCommand 类支持这个场景。CompositeCommand 类表示由多个子命令组成的命令。当调用复合命令时，它的每个子命令依次被调用。在需要将一组命令表示为单个命令的情况下，或者需要调用多个命令以实现逻辑命令的情况下，它非常有用。

CompositeCommand 类维护子命令列表（CompositeCommand 实例）。CompositeCommand 类的 `Execute` 方法将依次调用每个子命令的 `Execute` 方法，`CanExecute` 方法同样调用每个子命令的 `CanExecute` 方法，如果有任何子命令无法执行， `CanExecute` 方法都将返回 false。默认情况下，只有所有子命令都能执行才能执行 CompositeCommand。

CompositeCommand 可以在 NuGet 的 Prism.Core 包中 Prism.Commands 命名控件下找到。

### 创建一个 Composite Command 

``` CSharp
public class ApplicationCommands
{
  private CompositeCommand _saveCommand = new CompositeCommand();
  public CompositeCommand SaveCommand
  {
    get { return _saveCommand; }
  }
}
```


``` CSharp
public interface IApplicationCommands
{
    CompositeCommand SaveCommand { get; }
}
```

``` CSharp
public class ApplicationCommands : IApplicationCommands
{
  private CompositeCommand _saveCommand = new CompositeCommand();
  public CompositeCommand SaveCommand
  {
    get { return _saveCommand; }
  }
}
```

``` CSharp
public partial class App : PrismApplication
{
  protected override void RegisterTypes(IContainRegistry containRegistry)
  {
    containRegistry.RegisterSingleton<IApplicationCommands, ApplicationCommands>();
  }
}
```


## WPF Prism 库简介
复合应用程序通常具有多个屏幕，丰富的用户交互和数据可视化，并且具有重要的表示和业务逻辑。这些应用程序通常与多个后端系统和服务进行交互，并且使用分层体系结构，可以跨多个层进行物理部署。预期在该应用程序生命周期内发生重大变化，以响应新的需求和商机。简而言之，这些应用程序应该“经久耐用”，“为变革而生”。

Prism 包括参考实现，快速入门，课重重用的库代码和大量文档。

应该指出的是，虽然Prism并不难学，但开发人员必须准备好并愿意接受可能对他们来说不熟悉的模式和实践。管理层的理解和承诺至关重要，项目截止日期必须包含预先投入时间来学习这些模式和实践。

### 为什么要使用 Prism
设计和构建灵活且易于维护的丰富WPF客户端应用程序可能具有挑战性。本节介绍了构建WPF客户端应用程序时可能遇到的一些常见挑战，并介绍了Prism如何帮助您应对这些挑战。

#### 客户应用程序开发挑战
通常，客户端应用程序的开发人员面临相当多的挑战。应用要求可能会随时间而变化。新的商业机遇和挑战可能会出现，新技术可能会出现，甚至在开发周期中持续的客户反馈可能会严重影响应用程序的要求。因此，构建应用程序非常重要，因为它非常灵活，可以随时修改或扩展。设计这种灵活性可能很难实现。它需要一种体系结构，允许独立开发和测试应用程序的各个部分，并且可以在以后单独修改或更新，而不会影响应用程序的其余部分。

大多数企业应用程序都非常复杂，它们需要多个开发人员，甚至可能包括除开发人员之外还包括用户界面（UI）设计人员和本地化人员的大型开发人员团队。决定如何设计应用程序以便多个开发人员或子团队可以独立地在应用程序的不同部分上有效地工作，同时确保在集成到应用程序中时无缝集成在一起，这可能是一项重大挑战。

以单片风格设计和构建应用程序可能会导致应用程序的维护非常困难且效率低下。在这种情况下，“单片”是指这样的应用，其中组件非常紧密地耦合并且它们之间没有明显的分离。通常，以这种方式设计和构建的应用程序会遇到使开发人员的生活变得困难的问题。很难向系统添加新功能或替换现有功能，在不破坏系统其他部分的情况下很难解决错误，并且难以测试和部署。此外，它还会影响开发人员和设计人员一起高效工作的能力。

#### 综合方法
针对这些挑战的有效补救措施是将应用程序划分为多个离散的，松散耦合的，半独立的组件，然后可以轻松地将它们集成到应用程序“shell”中以形成一致的解决方案。以这种方式设计和构建的应用程序通常称为复合应用程序。

复合应用程序提供许多好处，包括：
- 它们允许模块由不同的个人或子团队单独开发，测试和部署;它们还允许更容易地修改或扩展新功能，从而使应用程序更容易扩展和维护。请注意，即使是单人项目也可以使用复合方法创建更多可测试和可维护的应用程序。
- 它们提供了一个通用shell，它由各种模块提供的UI组件组成，这些模块以松散耦合的方式进行交互。这减少了多个开发人员向UI添加新功能所产生的争用，并且它促进了共同的外观。
- 它们促进了应用程序的横向功能（如日志记录和身份验证）与垂直功能（例如特定于应用程序的业务功能）之间的重用和清晰的关注点分离。这还使您可以更轻松地管理应用程序组件之间的依赖关系和交互。
- 它们通过允许不同的个人或子团队根据他们的重点或专业知识专注于特定任务或功能，帮助维持角色分离。特别是，它在UI和应用程序的业务逻辑之间提供了更清晰的分离 - 这意味着UI设计人员可以专注于创建更丰富的用户体验。
- 复合应用程序非常适合一系列客户端应用程序场景。例如，复合应用程序非常适合在不同的后端系统上创建丰富的最终用户体验。下图显示了此类具有多个后端系统的复合应用程序的示例。

在这种类型的应用程序中，可以向用户呈现丰富且灵活的用户体验，该体验提供面向任务的关注功能，该功能跨越多个后端系统，服务和数据存储，其中每个都由一个或多个专用服务器代表。模块。应用程序逻辑和UI之间的清晰分离允许应用程序在所有组成模块中提供一致且差异化的外观。

此外，当UI中独立发展的组件彼此高度集成并且通常由不同的团队维护时，复合应用程序可能非常有用。下图显示了此类应用程序的屏幕截图。突出显示的每个区域表示组成UI的独立组件。

股票交易者参考实施

在这种情况下，复合应用程序允许UI动态组合。这提供了灵活的用户体验。例如，它可以允许在运行时将新功能动态添加到应用程序，从而实现丰富的最终用户自定义和可扩展性。





