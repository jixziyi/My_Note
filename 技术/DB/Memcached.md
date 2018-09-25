
# Memcached

## 简介
Memcached是高性能的分布式内存缓存服务器，一般使用的目的是通过缓存数据库查询结果，减少数据库访问次数，以提高动态Web应用的速度、提高可扩展性。

首次访问从RDBMS中取得数据保存到memcached中
第二次后，从memcached中取得数据显示页面

<!-- more -->

## 特点
1.**协议简单**
memcached的服务器和客户端通信并不使用复杂的XML等格式，而是用简单的基于文本行的协议。因此，使用telnet也能在memcached上保存数据、取得数据。

```dos
$telnet localhost 11211
Trying 127.0.0.1...
Connected to localhost.localdomain(127.0.0.1).
Escape character is '^]'.
set foo 0 0 3 (保存命令)
bar (数据)
STORED (结果)
get foo (取得命令)
VALUE foo 0 3 (数据)
bar (数据)
```

2.**基于libevent的事件处理**

3.**内置内存存储方式**
数据存储在memcached内置的内存存储空间中，重启memcached或重启系统都会导致全部数据消失。另外，内容容量达到指定值之后，基于LRU(Last Recently Used)算法自动删除不使用的缓存。

4.**memcached不互相通信的分布式**
