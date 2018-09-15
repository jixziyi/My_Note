# 常用配置说明

- [环境变量](##环境变量)
- [Node](##Node)
- [Maven](##Maven)
- [Docker](##Docker)

## 环境变量
Go
``` txt
GOPATH - C:\Users\{User}\go
PATH - %GOPATH%\bin
GOROOT - C:\Users\{User}\AppData\Local\GO\
```

Java 
``` txt
JAVA_HOME - C:\Program Files\Java\Jdk-10.0.2
PATH - %JAVA_HOME%\bin
```
Maven
``` txt
M2_HOME - D:\apache-maven-3.5.4
MAVEN_HOME - D:\apache-maven-3.5.4
PATH - %MAVEN_HOME%\bin
PATH - %M2_HOME%\bin
```

Python
``` txt
PATH - C:\Users\{user}\AppData\Local\Programs\Python\Python37\Scripts\
PATH - C:\Users\{user}\AppData\Local\Programs\Python\Python37\
```

Tomcat
``` txt
PATH - D:\Java\apache-tomcat-9.0.10-windows-x64\apache-tomcat-9.0.10\bin
```

QT
``` txt
QtMsBuild - C:\Users\{user}\AppData\Local\QtMsBuild
PATH - D:\Qt\Qt5.11.1\5.11.1\msvc2017_64\bin
```

Node
``` txt
PATH - C:\Program Files\nodejs\
```

## Node
``` bash
# install cnpm
npm install -g cnpm --registry=https://registry.npm.taobao.org

# 设置淘宝镜像
npm config set registry https://registry.npm.taobao.org

# 改回官方镜像
npm config set registry https://registry.npmjs.org
```

## Maven
- setting.xml 设置
``` xml
<!--54行 修改m2存储路径--> 
<localRepository>d:/Java/apache-maven-3.5.4/.m2/repository</localRepository>

<!--164行 修改maven镜像地址--> 
<mirrors>
    <mirror>
        <id>ui</id>
        <mirrorOf>central</mirrorOf>
        <name>ui maven</name>
        <url>http://uk.maven.org/maven2/</url>
    </mirror>
    <mirror>
        <id>alimaven</id>
        <mirrorOf>central</mirrorOf>
        <name>aliyun maven</name>
        <url>http://maven.aliyun.com/nexus/content/repositories/central/</url>
    </mirror>
</mirrors>

<!--224行 修改JDK版本--> 
<profile>
    <id>jdk-10</id>
    <activation>
        <jdk>10</jdk>
        <activeByDefault>true</activeByDefault>
    </activation>
    <properties>
        <maven.compiler.source>10</maven.compiler.source>
        <maven.compiler.target>10</maven.compiler.target>
        <maven.compiler.compilerVersion>10</maven.compiler.compilerVersion>
    </properties>
</profile>
```

## Docker
- Docker daemon 设置
``` json
{
  "registry-mirrors": [
    "https://hub-mirror.c.163.com",
    "https://docker.mirrors.ustc.edu.cn",
    "https://p10z8hr5.mirror.aliyuncs.com"
  ],
  "insecure-registries": [],
  "debug": true,
  "experimental": false
}
```

