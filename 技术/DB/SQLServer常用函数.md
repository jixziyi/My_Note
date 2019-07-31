# 笔记 SQLServer 常用函数

## 时间函数

|    含义     | 名称 | 缩写 |
| ----------- | ---- | ---- |
| Day of Year | Dy   | y    |
| Month       | Mm   | m    |
| Day         | Dd   | d    |
| Quarter     | Qq   | q    |
| Weekday     | Dw   | w    |
| Week        | Wk   | Ww   |
| Hour        | Hh   | h    |
| Second      | Ss   | s    |
| Millisecond | Ms   | /    |



``` SQL
select dateadd(day, 2, getdate())

select datediff(hour, getdate() - 1, getdate())

select datepart(hour, getdate())

select datename(weekday, getdate())

select day(getdate()), month(getdate()), year(getdate())

select convert(varchar, getdate(), 101)
--02/25/2019
select convert(varchar, getdate(), 102)
--2019.02.25
select convert(varchar, getdate(), 103)
--25/02/2019
select convert(varchar, getdate(), 104)
--25.02.2019
select convert(varchar, getdate(), 105)
--25-02-2019
select convert(varchar, getdate(), 106)
--25 02 2019
select convert(varchar, getdate(), 107)
--02 25, 2019
select convert(varchar, getdate(), 108)
--10:56:52
select convert(varchar, getdate(), 109)
--02 25 2019 10:56:48:620AM
select convert(varchar, getdate(), 110)
--02-25-2019
select convert(varchar, getdate(), 111)
--2019/02/25
select convert(varchar, getdate(), 112)
--20190225
select convert(varchar, getdate(), 113)
--25 02 2019 10:56:34:453
select convert(varchar, getdate(), 114)
--10:56:30:680
select convert(varchar, getdate(), 120)
--2019-02-25 10:56:27
```

## 其他函数
``` SQL
select left('about', 2)

select right('about', 2)

select len('about')

select lower('ABOUT')

select upper('about')

select ltrim(' about ')
select rtrim(' about ')

select reverse('about')

select replace('about', 'a', 'b')

select substring('about', 2, 2)

select char(97)

select ascii('a')

select char(97)

select charindex('a', 'about')
```
