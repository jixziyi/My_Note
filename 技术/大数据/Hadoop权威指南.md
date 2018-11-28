## Hadoop权威指南 (第2版) -Tom White

http://www.tuicool.com/articles/BRVjiq
http://www.tuicool.com/articles/EVB3aaU

### 第一章 初识Hadoop

Hadoop是由Apache Lucene创始人Doug Cutting创建的，Lucene是一个广泛使用的文本搜索系统库。Hadoop起源于Apache Nutch，一个开源的网络搜索引擎，本身也是也是Lucene项目的一部分。
Hadoop提供了一个可靠的共享存储和分析系统，HDFS实现共享，MapReduce实现分析处理。

我们遇到的问题：多年来磁盘存储容量快速增长的同时，其访问速度——磁盘读取速度——却未能与时俱进。
一个简单减少读取时间办法是对多个磁盘数据并行读取，但同时有更多问题要解决。

1. 硬件故障，一旦使用多个硬件，其中任一硬件发生故障的概率非常高。可以使用冗余磁盘阵列RAID，或者Hadoop文件系统，HDFS (Hadoop Distributed FileSysetm)。
2. 大多数分析任务需要以某种方式结合大部分数据共同完成分析任务，即从一个磁盘读取的数据可能需要和另外99个磁盘中读取的数据结合使用。MapReduce提供了一个编程模型，该模型将磁盘读写问题进行抽象，转换成一个对Key-Value数据集的计算。


**MapReduce**

MapReduce可以视为关系型数据库的补充，适合一次写入多次读取的应用，而关系型数据库更适合持续更新的数据集。

|    /     |     RDBMS      |    MapReduce     |
| -------- | :------------: | :--------------: |
| 数据大小 |       GB       |        PB        |
| 访问     | 交互式和批处理 |      批处理      |
| 更新     |    多次读写    | 一次写入多次读取 |
| 结构     |    静态模式    |     动态模式     |
| 完整性   |       高       |        低        |
| 横向扩展 |     非线性     |       线性       |

不久将来RDBMS和MapReduce之间关系会越来越模糊，RDBMS开始吸收MapReduce一些思路如：Aster Data和GreenPlum的数据库。基于MapReduce的高级查询语言，也使MapReduce接近传统开发方式。

**网格计算**

高性能计算 (High Performance Computing, HPC) 和网格计算 (Grid Computing) 将作业分散到集群的各台计算机上，使用类似于消息传递接口 (Message Passing Interface, MPI) 的API，这些机器访问由存储区域网络 (SAN) 组织的共享文件系统，如果节点需要访问大量数据，计算节点会由于网络宽带的瓶颈问题而空闲下来等待数据。
MapReduce会尽量在计算节点上存储数据，以实现数据本地的快速访问，**数据本地化** (data locality) 是其核心特性，并因此获得良好性能。

**Apache Hadoop和Hadoop生态圈**

1. `Common`:一组分布式文件系统和通用I/O的组件与接口 (序列化，Java PRC和储蓄话数据结构)
1. `Avro`:一种支持高效、跨语言的PRC以及永久存储数据的序列化环境
1. `MapReduce`:分布式数据处理模型和执行环境，运行于大型商用机集群
1. `HDFS`:分布式文件系统，运行于大型商用机集群
1. `Pig`:一种数据流语言和运行环境，用于检索非常大的数据集，Pig用于MapReduce和HDFS的集群上
1. `Hive`:一个分布式、按列存储的数据仓库。Hive管理HDFS中存储的数据，并提供基于SQL的查询语言 (由运行时引擎翻译成MapReduce作业)泳衣查询数据
1. `HBase`:一个分布式按列存储数据库。HBase使用HDFS作为底层存储，同时支持MapReduce的批量式计算和点查询 (随机读取)
1. `ZooKeeper`:一个分布式、可用性高的协调服务。Zookeeper提供分布式锁之类的基本服务用于构建分布式应用
1. `Sqoop`:在数据库和HDFS直接高效传输的工具



### 第二章 关于MapReduce


### 第三章 初识HDFS
