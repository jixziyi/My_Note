# PowerShell

## 基础操作
- Get-Command
使用 Get-Command 可以搜索相关命令
``` powershell
Get-Command "*vm"
```

- Get-Help
使用 Get-Help 可以查看帮助文档
``` powershell
Get-Help new-vm

# 如果想知道怎么是使用，可以查看例子
Get-Help new-vm -example

# 更新帮助文档
Get-Help -update
```

- Get-Process 获取所有进程
- Set-Alias   给指定的命令设置别名 `Set-Alias aaa Get-Command`
- Set-ExecutionPolicy remotesigned  设置 powershell 可直接执行脚本文件 一般脚本文件以 .ps1 结尾
- Get-Member  获取对象属性 `$var | Get-Member` 访问 $var 属性

## 基础语法
### 变量
- 定义变量
    - 不需要定义或声明数据类型
    - 在变量前加 `$`
- 定义变量的规则
    - 变量可以是数字 $123
    - 变量可以是字符串 $abc
    - 变量可以是特殊字符 ${@1b}
- 内置变量
    - $pshome、$home、$profile

``` powershell
# 变量赋值
$var = 123
$var = "aaaaa"

# 变量取值
$var 

# 特殊操作
Set-Variable var 100    # 赋值
Get-Variable var        # 取值
Clear-Variable var      # 清空变量
Remove-Variable var     # 删除变量
Get-Variable var*       # 取多个变量值  如，$var1 $var2 $var3

# 变量复制
$var1 = "bbb"
$var2 = "ccc"
$var2 = "$var1 $var2"     # $var2 = "bbb ccc"
$var2 = '$var1 $var2'     # $var2 = "$var1 $var2"
```

### 时间
- 获取当前时间 `$date=Get-Date`
- 当前时间加3天 `$date.AddDays(3)`

### 输出
- 排序 
    - `Get-Process | Sort-Object ws` 根据 ws 值排序

- 列表形式显示数据
    - `Get-Process | Sort-Object | fl`
    - `Get-Process | Sort-Object | Format-List`

### 比较运算符
- eq 是否等于 equal
- lt 小于 less than
- gt 大于 greater than
- ge 大于或等于 greater or equal
- le 小于或等于 less or equal
- ne 不等于 no equal

``` powershell
$var = "abc"
$var -like "*b*"        # 返回 true / false
$var -clike "*b*"       # 返回 true / false
```

### 函数
- 函数作用域
``` powershell
# 函数中不会对全局变量作出改变
# 执行结果
# 10 20 10
$var = 10
function one {
    "$var "
}

function two {
    $var = 20
    one
}
one
two
one
```

``` powershell
# 如果需要改变全局变量
# 执行结果
# 10 20 20
$var = 10
function one {
    "$var "
}

function two {
    $Script:var = 20
    one
}

one
two
one
```

### If
``` powershell
If ($a -gt 10) 
{
}
ElseIf ($a -eq 10)
{
}
Else
{
}
```

### Foreach
``` powershell
$var = 1..6     # 定义数组
Foreach($i in $var)
{
    $n++
}
```
