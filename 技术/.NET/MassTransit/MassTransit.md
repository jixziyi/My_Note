# MassTransit

## 安装 RabbitMQ
- 安装 Erlang 环境
- 配置 Erlang 环境变量，测试 `erl` 指令是否正常使用
- 打开 RabbitMQ Service - start，启动服务
- 启动管理界面，打开 RabbitMQ Command Prompt，输入如下命令：

``` bash
rabbitmq-plugins enable rabbitmq_management
```

- 登陆管理界面，端口：15672，账号/密码：guest/guest
- RabbitMQ 常用端口

``` text
4369：epmd，RabbitMQ节点和CLI工具使用的对等发现服务
5672,5671：由AMQP 0-9-1和1.0客户端使用，不带TLS和TLS
25672：Erlang分发用于节点间和CLI工具通信，并从动态范围分配（默认情况下限制为单个端口，计算为AMQP端口+ 20000）。有关详细信息，请参阅网络指南。
15672：HTTP API客户端和rabbitmqadmin（仅当启用管理插件时）
61613,61414：没有和使用TLS的STOMP客户端（只有启用了STOMP插件）
1883,8883：MQTT客户端没有和带有TLS，如果启用了MQTT插件
15674：STOMP-over-WebSockets客户端（只有启用了Web STOMP插件）
15675：MQTT-over-WebSockets客户端（仅当启用了Web MQTT插件时）
```

- 配置允许远程访问
``` bash
# 默认是无法通过http://server-name:15672来访问 RabbitMQ 的
# 可以通过修改 \RabbitMQ Server\rabbitmq_server-3.6.10\etc 下 Rabbitmq.config
# 或 C:\Users\{User}\AppData\Roaming\RabbitMQ\rabbitmq.config
[{rabbit, [{loopback_users, [guest]}]}]
```

## 


