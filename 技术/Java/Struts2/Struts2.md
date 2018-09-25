
Struts2是Apache基金会赞助的开源项目。通过Java Servlet/JSP技术，实现了JaveEE Web应用的MVC模式应用框架，是MVC模式中经典产品。
基于MVC的web应用程序框架。
<!--more-->
Struts2按照技术细节划分，主要分为以下几块：
1. **标签库**：在视图中运行这些标签莱实现网页上各种格式的显示
2. **拦截器**：HTTP请求在进入控制器部分执行前先执行拦截器中的功能
3. **FilterDispatcher/Action**：接收HTTP请求，根据Action的ActionMapper决定调用Action哪些方法
4. **Struts2配置文件**：定义控制转发流程，定义每个Action类的处理和结果数据如何导航到相应的表示界面
5. **OGNL和类型转换**：在表示界面将包含特定数据的java对象进行类型转换，显示出符合页面规则的数据
6. **Struts2校验规则**：对数据输入的严格定义，保证没有垃圾数据和不符合项目需求的数据
7. **国际化和本地化**：针对字符编码的转换，让web项目显示各种语言版本
8. **SiteMesh页面布局**：使用插件式开发模式让其和Struts2形成一个完整实体，支持web项目中的页面布局

Model1:jsp+JavaBean
Struts1 -> Struts2 <- WebWork

**web.xml**

- 任何MVC框架都需要与Web应用整合，只有配置在web.xml文件中Servlet才会被应用加载。
- 通常所有MVC框架都需要web应用加载一个核心控制器。
- Struts2需要加载`org.apache.struts2.dispatcher.filter.StrutsPrepareAndExecuteFilter`

**struts.xml**
1. 全局属性
2. 用户请求和Action之间对应关系
3. Action可能用到的参数和返回结果
4. 各种拦截器配置

``` xml
<!--XML头文件 dtd 文件用作xml格式验证-->
<!DOCTYPE struts PUBLIC
        "-//Apache Software Foundation//DTD Struts Configuration 2.5//EN"
        "http://struts.apache.org/dtds/struts-2.5.dtd">
<struts>
  <!---->
  <include file="struts-default.xml"></include>

  <!--  Overwrite Convention -->
  <constant name="struts.convention.action.suffix" value="Controller"/>
  <constant name="struts.convention.action.mapAllMatches" value="true"/>
  <constant name="struts.convention.default.parent.package" value="rest-showcase"/>

  <constant name="struts.convention.package.locators" value="example"/>

  <package name="rest-showcase" extends="rest-default">
      <global-allowed-methods>index,show,create,update,destroy,deleteConfirm,edit,editNew</global-allowed-methods>
  </package>
</struts>
```


**struts.properties**
struts2框架全局属性文件，自动加载
包含很多key-value对
可以使用constant元素配置在struts.xml中
