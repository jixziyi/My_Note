# HBase 使用教程

HBase - Hadoop Database，是一个分布式、面向列的开源数据库。

## HBase基础定义与概念
HBase是一个数据库，数据以表的形式存储在HBase中

**行、列族、列**

行以rowkey作为唯一标示。Rowkey是一段字节数组，这意味着，任何东西都可以保存进去，例如字符串、或者数字。行是按字典的排序由低到高存储在表中。

列族是列的集合，要准确表示一个列，需要“列族：列名”的方式。

HBase的存储优化都是针对一个列族，可以将经常需要一起取出来分析的信息都存储在一个列族上。

**HBase常用操作**

1. status: 查询服务器状态
2. version: 查看HBase版本
3. whoami: 查看连接的用户

**DDL命令**

1. create: create '表名', '列族名1', '列族名2'
2. disable: 失效一个表，当需要修改表结构、删除表时，需要先执行此命令
3. enable: 恢复失效表
4. alter: 修改表结构
5. describe: 查看表结构
6. list: 列举数据库中所有表
7. drop: 删除指定表


**DML命令**

1. put插入数据 `put 'tablename', '列族名:列名', 'value'`
2. get获取数据 获取rowkey的指定列族指定列的数据
3. count 计算行数
4. scan 扫描全表数据
5. delete 删除数据
6. deleteall 删除整行数据
7. truncate 删除全表数据


