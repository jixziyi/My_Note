# RabbitMQ

## pull 镜像
``` bash
# 无管理界面
docker pull rabbitmq:latest

# 有web管理界面
docker pull rabbitmq:3-management
```

## 运行
``` bash
docker run -d --hostname my-rabbit --name rabbitMQ -p:8080:15672 rabbitmq:3-management
```

