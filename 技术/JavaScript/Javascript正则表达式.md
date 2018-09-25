
# Javascript正则表达式

## 正则表达式作用
1.数据有效性验证
2.文本替换
3.提取子字符串

## 语法
### 创建正则表达式

```javascript
var re = new RegExp(); //RegExp是一个对象
re = new RegExp("a"); //匹配字母a
re = new RegExp("a","i"); //第二个参数，表示匹配时不区分大小写
```
RegExp 构造函数第一个参数为正则表达式的文本内容，第二个参数为可选标志(可选标志可以组合使用)
`g`：全文查找 
`i`：忽略大小写
`m`：多行查找

<!-- more -->

```javascript
var re = new RegExp("a","gi");
```

正则表达式的一般形式为`/love/`，其中位于`/`定界符之间的部分就是将要在目标对象中进行匹配的模式。

### 方法和属性

**方法**

- test：返回一个Boolean值，指出在被查找的字符串中是否存在

```javascript
>/a/.test("about")
true
```

- exec：用正则表达式进行查找，并返回包含查询结果的数组

```javascript
>/a/.exec("about")
["a"]
```
- compile：把正则表达式编译为内部格式，从而执行的更快

```javascript
>var re = new RegExp(); 
>re.compile("[0-9]"); //compile方法返回值为re对象
```

**属性**

- source：返回正则表达式模式的文本的副本

```javascript
>/[0-9]{3}/.source
"[0-9]{3}"
```
- lastIndex：字符串中下一次匹配的开始位置，可以赋值。全局匹配时会自动修改lastIndex的值

```javascript
>var re = /[A-K]/gi;
undefined
>re.lastIndex
0
>re.exec("About!")
["A"]
>re.lastIndex
1
>re.exec("About!")
["b"]
>re.lastIndex
2
>re.exec("About!")
null
>re.lastIndex
0
```
- $1...$9： 如果正则语句中有括号，返回每个括号中对应的匹配结果

```javascript
>var re = /([A-Z])([a-z])/;
>var str = "Hello World!";
>re.test(str);
>RegExp.$1
"H"
>RegExp.$2
"e"
```
- input()：返回执行规范表述查找的字符串

```javascript
>var re = /([A-Z])([a-z])/;
>var str = "Hello World!";
>re.test(str);
>RegExp.input
"Hello World!"
```
- lastMatch()：返回正则表达式搜索过程中最后匹配的字符

```javascript
>var re = /([A-Z])([a-z])/;
>var str = "Hello World!";
>re.test(str);
>RegExp.lastMatch
"He"
```
- lastParen()：返回正则表达式开始查找过程中最后的子匹配

```javascript
>var re = /([A-Z])([a-z])/;
>var str = "Hello World!";
>re.test(str);
>RegExp.lastParen
"e"
```
- leftContext()：返回被查找的字符串从开始查找的位置到最后匹配之前的位置之间的字符

```javascript
>var re = / /;
>var str = "Hello World!";
>re.test(str);
>RegExp.leftContext
"Hello"
```
- rightContext()：返回被搜索的字符串从最后一个匹配位置开始到字符串结尾之间的字符

```javascript
>var re = / /;
>var str = "Hello World!";
>re.test(str);
>RegExp.rightContext
"World!"
```

**String对象和正则相关的方法**

- match：找到一个或多个正则表达式的匹配

```javascript
>var str = "Hello World!";
>str.match(/[a-z]/)
["e"]
>str.match(/[a-z]/g)
["e", "l", "l", "o", "o", "r", "l", "d"]
```
- replace：替换和正则表达式匹配的子串

```javascript
>var str = "Hello World!";
>str.replace(/[a-z]/g, '?')
"H???? W????!"
```
- search：与indexOf类似，返回第一个匹配值的位置

```javascript
>var str = "Hello World!";
>str.search(/[a-z]/);
1
```
- split：把字符串分割为字符串数组

```javascript
>var str = "Hello World!";
>str.split(/[a-z]/g);
["H", "", "", "", " W", "", "", "", "!"]
```


### 字符
**特殊字符**
`\t`:制表符
`\n`:换行符
`\r`:回车符
`\f`:换页符
`\a`:alert字符
`\e`:esc
`\cX`:X的控制字符，Control-X，也可为A-Z中任意字符
`\b`:backspace
`\v`:垂直制表符
`\0`:空字符

```javascript
>str = "		";
>str.match(/\t/)
["	"]
```

**简单字符**

1. 原则上正则一个字符对应一个字符`/a/.test("about")`，可以用`[]`把多个字符括起来，多个对应一个字符`[ab].test("about")`
2. 负向:在括号里加上元字符取反，可以表示不匹配括号中字符`[^ab].test("about")`
3. 范围:如果匹配的内容过多，而类型相同，可以使用`-`表示范围`[a-m].test("about")`
4. 组合:同一个中括号中可以匹配不同类型的字符`[a-c1-4\n].test("about")`

**预定义字符**
`.`:`[^\n\r]`除换行回车外任意字符
`\d`:`[0-9]`数字
`\D`:`[^0-9]`非数字
`\s`:`[\t\n\x0B\f\r]`空白字符
`\S`:`[^\t\n\x0B\f\r]`非空白字符
`\w`:`[a-zA-Z_0-9]`单词字符
`\W`:`[^a-zA-Z_0-9]`非单词字符

**量词**
`?`:出现零次或一次
`*`:出现零次或多次
`+`:出现一次或多次
`{n}`:出现零次或n次
`{n,m}`:至少出现n次但不超过m次
`{n,}`:至少出现n次

1. `贪婪量词`:所有简单量词都是贪婪量词，优先匹配整个字符串，如果匹配不了，从末位逐个减少字符串长度直到匹配。
2. `惰性量词`:在简单量词后加问号，先匹配第一个字符，然后逐个增加。
3. `支配性量词`:在简单量词后加加号，只会匹配一次，如果不匹配不再尝试。<span style="color:red;">javascript不支持</span>

```javascript
>var str = "aboutabout";
>str.match(/a.*b/)	//贪婪量词
["aboutab"]
>str.match(/a.*?b/)	//惰性量词
["ab"]
>str.match(/a.*+b/)	//支配性量词
"Error:SyntaxError: Invalid regular expression: /a.*+b/: Nothing to repeat"
```

匹配汉字:`/[\u4e00-\u9fa5]/`

**分组**
1. `{}`:表示重复次数
2. `[]`:表示选择范围
3. `()`:重复多个字符，`/(dog){2}/`

**反向引用**
反向引用标识由正则表达式中匹配组捕获的子字符串。

```javascript
>var str = "Hello World";
>str.replace(/(H.*o) (W.*d)/g, "$2 $1");
"World Hello"
```

**候选**
使用`|`将分组划分为两个或多个候选项。

```javascript
>var str = "Hello World";
>str.match(/(Hello|World)/g);
["Hello", "World"]
```

**非捕获性分组**
在分组的左括号后加一个问号或冒号，系统将不会创建反向引用。

```javascript
>var str = "Hello World";
>str.replace(/(?H.*o) (:W.*d)/g, "$2 $1");
"Error:SyntaxError: Invalid regular expression: /(?H.*o) (:W.*d)/: Invalid group"
```


**前瞻**
`(?=exp)`:正向前瞻，匹配exp前面的位置
`(?!=exp)`:负向前瞻，匹配后面不是exp的位置
`(?<=exp)`:正向后瞻，匹配exp后面的位置，<span style="color:red;">javascript不支持</span>
`(?<!exp)`:负向后瞻，匹配前面不是exp的位置，<span style="color:red;">javascript不支持</span>

**边界**

`^`:开头,不能紧跟着左中括号后面
`$`:结尾
`\b`:单词边界
`\B`:非单词边界


