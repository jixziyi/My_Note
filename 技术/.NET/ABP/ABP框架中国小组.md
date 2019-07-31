# ABP 框架
- ABP 框架中国小组

## 1. Abp 总体介绍

### 1.1 入门介绍

ABP 是 `ASP.NET Boilerplate Project (ASP.NET 样板项目)` 的简称。

#### 1.1.1 ABP 采用了以下技术

**服务器端**
- ASP.NET MVC 5、Web API 2、C# 5.0
- DDD 领域驱动设计 (Entities、Repositories、Domain Services、Domain Events、Application Services、DTOs等)
- Castle windsor 依赖注入容器
- Entity Framework 6 / NHibernate，数据迁移
- Log4Net 日志记录
- AutoMapper 实现 Dto 类与实体类的双向自动转换

**客户端**
- Bootstrap
- Less
- AngularJs
- jQuery
- Modernizr
- 其他JS库：jQuery.validate、jQuery.form、jQuery.blockUI、json2

#### 1.1.2 ABP 框架已实现了以下特性
- 多语言/本地化支持
- 多租户支持，每个租户的数据自动隔离，业务模块开发者不需要在保存和查询数时写响应代码
- 软删除支持、继承相应的基类或实现相应接口，会自动实现软删除
- 统一的异常处理、应用层几户不需要处理自己写异常处理代码
- 数据有效期验证
- 日志记录、自动记录程序异常
- 模块化开发、每个模块有独立的 EF DbContext，可单独制定数据库
- Repository 仓储模式、已实现了 Entity Framework、NHibernate、MangoDB、内存数据库
- Unit Of Work 工作单元模式、为应用层和仓储层的方法自动实现数据库事务
- EventBus 实现领域事件 Domain Events
- DLL 嵌入资源管理
- 通过 Application Services 自动创建 Web Api 层、不需要写 ApiController 层了
- 自动创建 JavaScript 的代理层来更方便使用 Web Api
- 封装一些 JavaScript 函数，更方便地使用 ajax、消息框、通知组件、忙状态的遮罩层

"Zero" 的模块、实现了以下功能：
- 身份验证与授权管理、通过 ASP.NET Identity 实现的
- 用户&角色管理
- 系统设置存取管理、系统级、租户级、用户级、作用范围自动管理
- 审计日志、自动记录每一次接口的调用者和参数

**需要非常高并发DDD框架，建议去研究netfocus的ENode**

### 1.2 层架构体系
#### 1.2.1 前言
ABP 遵循DDD的原则，将工程分为4个层
- 展现层 Presentation：向用户提供一个接口 UI、使用应用层和用户 UI 进行交互
- 应用层 Application：应用层是表现层和领域层能够实现交互的中间者，协调业务对象去执行特定的应用任务
- 领域层 Domain：包括业务对象和业务规则，这是应用层的核心层
- 基础设施层 Infrastructure：提供通用技术来支持更高的层。

根据需要额外添加的层
- 分布式服务层 Distributed Service：用于公开应用程序接口供远程调用，比如通过 Web API 或 WCF 来实现

#### 1.2.2 ABP 的体系结构
|     Layers     |                                                                                                       |
| -------------- | ----------------------------------------------------------------------------------------------------- |
| Presentation   | View Models(JavaScript)、Views(HTML/CSS)、Localization                                                |
| Web            | Web API Controllers、MVC Controllers                                                                  |
| Application    | Application Services、DTOs、DTO Mappers                                                               |
| Domain         | Entities、Value Objects、Repositories、Business Classes、Domain Services、Unit of Work、Domain Events |
| Infrastructure | ORM、DB Migrations                                                                                    |
| Server Side    | Dependency Injection、Logging                                                                         |

#### 1.2.3 领域层
领域层式实现所有业务规则的地方
- 实体 Entity：实体代表业务领域的数据和操作，通常用来映射成数据库表
- 仓储 Repository：仓储式像集合一样的对象，用来在数据源上检索和存储实体，在领域层定义仓储，但不实现他们。它们在基础设施层被实现
- 领域服务 Domain Service：当处理的业务规则跨越两个及以上实体时，应该写在领域服务方法里面
- 领域事件 Domain Event：领域事件被用来定义特定于领域的事件，并且触发使用它们。领域服务与实体以及其他领域对象一起实现了不属于单个实体的业务规则
- 工作单元 Unit of Work：工作单元是一种设计模式被用来管理数据库连接和事务，以及跟踪实体更改，并将这些更改保存到数据存储中。它被定义在领域层中，但在基础设施层实现它们

#### 1.2.4 应用层
应用层提供一些应用服务 Application Services 方法供展现层调用。一个应用服务方法接收一个 DTO (数据传输对象)作为输入参数，使用这个输入参数执行特定的领域层操作，并根据需要返回另一个 DTO。在展现层到领域层之间，不应该接收或返回实体(Entity)对象，应该进行 DTO 映射。一个应用服务方法通常被认为是一个工作单元(Unit of Work)。用户输入参数的验证工作也应该在应用层实现。ABP 提供了一个基础架构让我们很容易地实现输入参数有效性验证。建议使用一种像 AutoMapper 这样的工具来进行实体与 DTO 之间的映射

#### 1.2.5 基础设施层
当在领域层中为定义了仓储接口，应该在基础设施层中实现这些接口。可以使用 ORM 工具，例如 EntityFramework 或 NHibernate。ABP 的基类已经提供了对这两种 ORM 工具的支持，数据库迁移也被用于这一层

#### 1.2.6 Web 与展现层


### 1.3 模块系统
#### 1.3.1 ABP 模块系统简介
ABP 框架提供了创建和组装模块的基础，一个模块能够依赖于另一个模块。

## 2. ABP 公共结构
### 2.1 依赖注入
依赖注入是一种软件设计模式，指一个或多个依赖（或服务）被注入，或通过引用传递，传入一个依赖对象（或客
户端）并成为客户状态的一部分。模式通过自身的行为分离了客户依赖的创建，这允许程序设计是松耦合的，同时遵循依赖倒
置和单一职责原则。与服务定位器模式直接进行对比，它允许客户了解他们用来查找依赖的机制。

#### 2.1.1 传统方法的问题
在一个应用程序中，类之间相互依赖。假设我们有一个应用程序服务，使用仓储 repository 类插入实体到数据库。在这种情况下，应用程序服务类依赖于仓储 repository 类。
``` C#
public class PersonAppService
{
  private IPersonRepository _personRepository;
  public PersonAppService()
  {
    _personRepository = new PersonRepository();
  }

  public void CreatePerson(string name, int age)
  {
    var person = new Person { Name = name, Age = age };
    _personRepository.Insert(person);
  }
}
```
PersonAppService 使用 PersonRepository 插入 Person 到数据库，这段代码的问题：
- PersonAppService 通过 IPersonRepository 调用 CreatePerson 方法，所以这方法依赖于 IPersonRepository，代替了 PersonRepository 具体类。但 PersonAppService 的构造函数仍然依赖于 PersonRepository。组件应该依赖于接口而不是实现，这就是所谓的依赖倒置原则。
- 如果 PersonAppService 亲自创建 PersonRepository，即依赖一个特定的 IPersonRepository 接口实现，且不能使用另一实现进行工作。实现分离接口变得无意义，硬依赖 hard-dependency 使得代码基于紧耦合和低重用。
- 如果我们未来需要改变 PersonRepository 的方式。即，我们可能想让它创建一个单例，或者我们想要创建多个类实现 。IPersonRepository 并根据条件创建对象。在这种情况下，我们需要修改所有依赖于 IPersonRepository 的类。
- 因为这样的依赖，很难对 PersonAppService 进行单元测试。

我们可以使用工厂模式，来克服这些问题，创建仓储类是抽象的。
``` C#
public class PersonAppService
{
  private IPersonRepository _personRepository;
  public PersonAppService()
  {
    _personRepository = PersonRepositoryFactory.Create();
  }

  public void CreatePerson(string name, int age)
  {
    var person = new Person { Name = name, Age = age };
    _personRepository.Insert(person);
  }
}
```
PersonRepositoryFactory 是一个静态类，创建并返回一个 IPersonRepository。这就是所谓的**服务定位器模式**。以上依赖问题得到解决，因为 PersonAppService 不需要创建一个 IPersonRepository 实现的对象，这个对象取决于 PersonRepositoryFactory 的 Create 方法。但是，仍然存在一些问题：
- PersonAppService 取决于 PersonRepositoryFactory。这更容易接收，但仍是一个硬依赖 hard-dependency
- 需要为每个库或每个依赖项写一个工厂类/方法
- 测试行依然不好，很难使得 PersonAppService 使用 mock 实现 IPersonRepository。

#### 2.1.2 解决方案
##### 2.1.2.1 构造函数注入 Constructor Injection
``` C#
public class PersonAppService
{
  private IPersonRepository _personRepository;

  public PersonAppService(IPersonRepository personRepository)
  {
    _personRepository = personRepository;
  }

  // ...
}
```
这被称为构造函数注入。现在 PersonAppService 不知道哪些类实现了 IPersonRepository 以及如何创建它。谁需要使用 PersonAppService，首先创建一个 IPersonRepository，并将其传递给 PersonAppService 构造函数。
``` C#
var repository = new PersonRepository();
var personService = new PersonAppService(repository);
personService.CreatePerson("Emre", 19);
```
构造函数注入是一个完美的方法，使一个类与依赖对象创建相独立。但是，上面代码有一些问题：
- 创建一个 PersonAppService 变得困难。如果它有多个依赖，我们必须创建多个依赖对象，并将它们传递到构造函数 PersonAppServcie
- 从属类可能有其他依赖项，如 PersonRepository 可能有依赖关系。所以我们必须创建 PersonAppService 的所有依赖项，所有依赖项的依赖关系等等。因此，依赖关系使我们创建一个对象变得过于复杂了

##### 2.1.2.2 属性注入 Property Injection
采用构造函数的注入模式是一个完美的提供类的依赖关系的方式。通过这种方式，只有提供了依赖你才能创建类的实例。同时，这也是一个强大的方式显示地声明，类需要什么样的依赖才能正确的工作。

但是，在有些情况下，该类依赖于另一个类，但也可以没有它。这通常是适用于横切关注点，如日志记录。一个类可以没有工作日志，如果提供一个日志对象它也可以写日志。在这种情况下，你可以定义依赖为公共属性，而不是让它们放在构造函数。如果我们想在 PersonAppService 写日志，我们可以重写类如下：
``` C#
public class PersonAppService
{
  public ILogger Logger { get;set; }
  private IPersonRepository _personRepository;
  public PersonAppService(IPersonRepository personRepository)
  {
    _personRepository = personRepository;
    Logger = NullLogger.Instance;
  }

  public void CreatePerson(string name, int age)
  {
    Logger.Debug("Inserting a new person to database with name = " + name);
    var person = new Person { Name = name, Age = age };
    _personRepository.Insert(person);
    Logger.Debug("Successfully inserted!");
  }
}
```
NullLogger.Instance 是一个单例对象，实现了 ILogger 接口，但实际上什么都没有做。不写日志，它实现了 ILogger 实例，且方法体为空。如果你为 PersonAppService 实例设置了 Logger，PersonAppService 可以写日志了，如下：
``` C#
var personService = new PsersonAppService(new PersonRepository());
personService.Logger = new Log4NetLogger();
personService.CreatePerson("Emre", 19);
```

##### 2.1.2.3 依赖注入框架
有许多依赖注入框架，都可以自动解决依赖关系。它们可以创建所有的依赖项，递归依赖和依赖关系。所以你只需要依赖注入模式写类和类构造函数&属性，其他交给 `DI` 框架处理。

ABP 的依赖注入基于 `Castle Windsor` 框架，还有很多这样的框架，如 `Unity`、`Ninject`、`StructureMap`、`Autofac` 等等

在使用一个依赖注入框架时，首先注册你的接口/类到依赖注入框架中，然后你就可以 resolve 一个对象，在 `Castle Windsor` 中：
``` C#
var container = new WindsorContainer();
container.Register(
  Component.For<IPersonRepository>().ImplementedBy<PersonRepository>().LifestyleTransient(),
  Component.For<IPersonAppService>().ImplementedBy<PersonAppService>().LifestyleTransient()

);
var personService = container.Resolve<IPersonAppService>();
personService.CreatePerson("Emre", 19);
```
首先我们创建了 WindsorContainer，然后注册 PersonRepository 和 PersonAppService 及它们的接口。然后我们要求容器创建一个 IPersonAppService 实例。它创建 PersonAppService 对象及其依赖项并返回。注册的依赖项只在程序启动的某个地方创建一次。
请注意，我们将对象声明 transient 临时对象，每次创建这些类型的一个对象时，就会创建一个新的实例。在这里会有许多不同的生命周期如 singletion 单例模式。

##### 2.1.2.4 ABP 依赖注入的基础结构
- Registering 注册
- Conventional registrations 常规注册
- 

#### 2.1.3 其他
##### 2.1.3.1 IShouldInitialize 接口
有些类在第一次使用前需要初始化，IShouldInitialize 有 Initialize() 方法，如果你实现它，那么你的 Initialize() 方法在创建对象之后会被自动调用。


### 2.2 会话管理
#### 2.2.1 简介


## 3. ABP 领域层

## 4. ABP 应用层

## 5. 分布式服务层
### 5.1 ABP 分布式服务 ASP.NET Web API Controllers
#### 5.1.1 简介
ABP 已经把 ASP.NET Web API Controllers 集成到了 Abp.Web.Api。为了能够享受使用 Abp.Web.Api 带来的便利，应该使你的 Controllers 派生自 AbpApiController

``` C#
public class UsersController : AbpApiController
{
}
```

#### 5.1.2 AbpApiController 基类
##### 5.1.2.1 本地化
AbpApiController中定义了一个方法：`L`，为了使用`L`方法，我们应该初始化 `LocalizationSourceName`，为了不重复初始化该变量我们可以定义一个继承 `AbpApiController` 的基类，在该类中初始化它，以后所有的 Controller 类都继承自该类
``` C#
public class UsersController : AbpApiController
{
  public UsersController()
  {
    LocalizationSourceName = "MySourceName";
  }

  public UserDto Get(long id)
  {
    var helloWorldText = L("HelloWorld");
    // ...
  }
}
```

##### 5.1.2.2 其他
可以预先注入(pre-inijected) AbpSession、EventBus、PermissionManager、PermissionChecker、SettingManager、FeatureManager、FeatureChecker、LocalizationManager、Logger、CurrentUnitOfWork 等基础属性

##### 5.1.2.3 过滤器
ABP 为 ASP.NET Web API 定义了一些预先构建的过滤器，默认它们被添加到了所有控制器的所有Action

##### 5.1.2.4 审计日志


##### 5.1.2.5 Authorization

##### 5.1.2.6 反伪造过滤器

##### 5.1.2.7 工作单元

##### 5.1.2.8 包装返回结果&异常处理

##### 5.1.2.9 缓存结果

##### 5.1.2.10 验证结果

##### 5.1.2.11 模型绑定
AbpApiDateTimeBinder 过滤器被用来标准化 DateTime(以及 Nullable<DateTime>)的输入(使用 Clock)

## 6. ABP 表现层

## 7. ABP 后台服务
### 7.1 后台作业和后台工人
#### 7.1.1 简介
ABP提供了后台作业和后台工人，来执行应用程序中的后台线程的某些任务

#### 7.1.2 后台作业
由于各种各样的原因，需要后台作业以队列和持久化的方式来排队执行某些任务
- 用户等待执行一个长时任务。如生成大型报表，可以添加这个工作到队列中，当报表生成完毕后，发送报表结果到该用户的邮箱
- 重试创建并持久化任务操作，以保证任务的成功执行。当后台任务失败，由于有后台作业及持久化机制，在问题排出后，可以重试执行失败的任务，保证任务的成功执行

**作业持久化**相关信息可以查看源码：`Background Job Store`


## 8. ABP 实时服务

## 9. ABP 基础设施层


# Abp Zero
## 1. 总体介绍

## 2. 功能

