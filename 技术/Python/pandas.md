# Pandas
Pandas 是一个Python数据分析库

## Pandas 有三种基本结构
- Series: 一维
- DataFrame: 二维
- Panel: 三维

## 常用方法
``` python
# 查看前几行数据，默认5条
df.head()

# 查看后3条数据
df.tail(3)

# 查看下标
df.index

# 查看列标
df.columns

# 查看数据
df.values

# 查看简单数据统计
df.describe()

# 数据转置
df.T

# 排序, axis表示按第几维排序
df.sort_index(asis=0, ascending=True)
df.sort_values(by, axis=0, ascending=True)
df.sort_values(by="Name")

# 索引，
```



