# Eclipse 远程 Hadoop

## Ecplise 配置

配置文章：http://www.2cto.com/kf/201603/496487.html

Hadoop路徑説明：http://www.jianshu.com/p/f5a6c4d888e0

填坑貼：http://blog.csdn.net/rongyongfeikai2/article/details/45886807

**Ecplise遠程操作權限報錯解決辦法**

1. 在系统的环境变量或java JVM变量里面添加HADOOP_USER_NAME，这个值具体等于多少看自己的情况，以后会运行HADOOP上的Linux的用户名。（修改完重启eclipse，不然可能不生效）
2. 将当前系统的帐号修改为hadoop
3. 使用HDFS的命令行接口修改相应目录的权限，hadoop fs -chmod 777 /user,后面的/user是要上传文件的路径，不同的情况可能不一样，比如要上传的文件路径为hdfs://namenode/user/xxx.doc，则这样的修改可以，如果要上传的文件路径为hdfs://namenode/java/xxx.doc，则要修改的为hadoop fs -chmod 777 /java或者hadoop fs -chmod 777 /，java的那个需要先在HDFS里面建立Java目录，后面的这个是为根目录调整权限。

**重點**

1. Eclipse安裝 Hadoop 插件
2. Windows執行文件需要編譯，與平臺有對應關係
3. GitHub上可以下載以上文件
4. java JDK對應操作系統版本，目前看1.8版本無法使用



**Sqoop安裝配置**
http://pan.baidu.com/s/1i4BqZpb
http://www.jisoupan.com/share/319.html