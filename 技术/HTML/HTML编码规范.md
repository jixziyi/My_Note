
# HTML编码规范
[link](http://codeguide.bootcss.com)

## 黄金定律
永远遵守同一套编码规范。

>不管有多少人参与同一项目，一定要确保每一行代码都像是同一个人编写的。

## HTML
### 语法

* 用两个空格代替制表符`tab`，这是唯一能够保证在所有环境下获得一致展现的方法.
* 嵌套元素应当缩进一次
* 对于属性的定义，确保全部使用双引号，绝对不要使用单引号
* 不要在自闭合`self-closing`元素的尾部添加斜线，html5规范中明确说明这是可选的
* 不要省略可选的结束标签`closing tag`

### HTML5 doctype
为每个HTML页面的第一行添加标准模式`standard mode`的声明，这样能够确保在每个浏览器中拥有一致的展现

```html
<!DOCTYPE html>
<html>
</html>
```

### 语言属性
根据HTML5规范:
>强烈建议为html根元素指定lang属性，从而为文档设置正确的语言。这将有助于语音合成工具确定其所应该采用的正确发音，有助于翻译工具确定其翻译时所应遵守的规则等等。

```html
<html lang="zh-CN">
</html>
```

### IE兼容模式
IE支持通过特定的<meta>标签来确定绘制当前页面所应该采用的IE版本。除非有特殊要求，否则最好设置为`edge mode`,从而通知IE采用其所支持的最新的模式。

```html
<meta http-equiv="X-UA-Compatible" content="IE=Edge">
```
