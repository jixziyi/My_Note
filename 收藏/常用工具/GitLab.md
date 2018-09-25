# GitLab 常用操作



## 常规操作
``` bash
# 查看状态
sudo gitlab-ctl status
# 启动
sudo gitlab-ctl start
# 停止
sudo gitlab-ctl stop
# 重启
sudo gitlab-ctl restart
# 重新配置
sudo gitlab-ctl reconfigure
```

## 备份
**配置文件备份**
``` bash
# 所有配置文件均位于 /etc/gitlab 文件夹下
cd /etc/gitlab/
```

**备份数据**
``` bash
# 备份
# 路径: /var/opt/gitlab/backups/1490183942_2017_03_22_gitlab_backup.tar
sudo gitlab-rake gitlab:backup:create

# 恢复
sudo gitlab-ctl stop unicorn
sudo gitlab-ctl stop sidekiq
sudo gitlab-ctl status
sudo gitlab-rake gitlab:backup:restore BACKUP=1490183942_2017_03_22
```

## 异常处理
**查看日志**
``` bash
vi /var/log/gitlab/unicorn/unicorn_stderr.log
```

**The remote end hung up unexpectedly**
``` bash
# Ruby判断连接超时
vi /var/opt/gitlab/gitlab-rails/etc/unicorn.rb

# 修改unicorn timeout值
# timeout 30
timeout 180

# 重启服务
sudo systemctl restart gitlab-runsvdir.service
```