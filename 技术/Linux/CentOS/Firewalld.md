
# firewalld配置

[firewalld使用简介](#firewalld使用简介)

CentOS将默认的防火墙由iptables升级为firewalld，firewalld跟iptables比起来至少有两大好处：

1. firewalld可以动态修改单条规则，而不需要像iptables那样，在修改规则后全部刷新才生效
2. firewalld在使用上比iptables人性化的多，即使不明白"五张表五条链"而且对TCP/IP协议不理解也可实现大部分功能

## firewalld使用简介

莫小安

CentOS7使用firewalld打开关闭防火墙与端口

1. firewalld的基本使用
- 启动： `systemctl start firewalld`
- 查看状态： `systemctl status firewalld`
- 停止： `systemctl disable firewalld`
- 禁用： `systemctl stop firewalld`
 
2. systemctl是CentOS7的服务管理工具中主要的工具，它融合之前service和chkconfig的功能于一体。
- 启动一个服务：`systemctl start firewalld.service`
- 关闭一个服务：`systemctl stop firewalld.service`
- 重启一个服务：`systemctl restart firewalld.service`
- 显示一个服务的状态：`systemctl status firewalld.service`
- 在开机时启用一个服务：`systemctl enable firewalld.service`
- 在开机时禁用一个服务：`systemctl disable firewalld.service`
- 查看服务是否开机启动：`systemctl is-enabled firewalld.service`
- 查看已启动的服务列表：`systemctl list-unit-files|grep enabled`
- 查看启动失败的服务列表：`systemctl --failed`

3. 配置firewalld-cmd

- 查看版本：`firewall-cmd --version`
- 查看帮助：`firewall-cmd --help`
- 显示状态：`firewall-cmd --state`
- 查看所有打开的端口： `firewall-cmd --zone=public --list-ports`
- 更新防火墙规则： `firewall-cmd --reload`
- 查看区域信息:  `firewall-cmd --get-active-zones`
- 查看指定接口所属区域： `firewall-cmd - --get-zone-of-interface=eth0`
- 拒绝所有包：`firewall-cmd --panic-on`
- 取消拒绝状态： `firewall-cmd --panic-off`
- 查看是否拒绝： `firewall-cmd --query-panic`
 
那怎么开启一个端口呢
添加
firewall-cmd --zone=public --add-port=80/tcp --permanent    （--permanent永久生效，没有此参数重启后失效）
重新载入
firewall-cmd --reload
查看
firewall-cmd --zone= public --query-port=80/tcp
删除
firewall-cmd --zone= public --remove-port=80/tcp --permanent
 
标签: linux

学习apache安装的时候需要打开80端口，由于centos 7版本以后默认使用firewalld后，网上关于iptables的设置方法已经不管用了，想着反正iptable也不会用，索性直接搬官方文档，学习firewalld了，好像比iptables要简单点了。
 
官方文档地址：https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Security_Guide/sec-Using_Firewalls.html#sec-Introduction_to_firewalld
 
1、firewalld简介
firewalld是centos7的一大特性，最大的好处有两个：支持动态更新，不用重启服务；第二个就是加入了防火墙的“zone”概念
 
firewalld有图形界面和工具界面，由于我在服务器上使用，图形界面请参照官方文档，本文以字符界面做介绍
 
firewalld的字符界面管理工具是 firewall-cmd 
 
firewalld默认配置文件有两个：/usr/lib/firewalld/ （系统配置，尽量不要修改）和 /etc/firewalld/ （用户配置地址）
 
zone概念：
硬件防火墙默认一般有三个区，firewalld引入这一概念系统默认存在以下区域（根据文档自己理解，如果有误请指正）：
drop：默认丢弃所有包
block：拒绝所有外部连接，允许内部发起的连接
public：指定外部连接可以进入
external：这个不太明白，功能上和上面相同，允许指定的外部连接
dmz：和硬件防火墙一样，受限制的公共连接可以进入
work：工作区，概念和workgoup一样，也是指定的外部连接允许
home：类似家庭组
internal：信任所有连接
对防火墙不算太熟悉，还没想明白public、external、dmz、work、home从功能上都需要自定义允许连接，具体使用上的区别还需高人指点
 
2、安装firewalld
root执行 # yum install firewalld firewall-config
 
3、运行、停止、禁用firewalld
启动：# systemctl start  firewalld
查看状态：# systemctl status firewalld 或者 firewall-cmd --state
停止：# systemctl disable firewalld
禁用：# systemctl stop firewalld
 
4、配置firewalld
查看版本：$ firewall-cmd --version
查看帮助：$ firewall-cmd --help
查看设置：
                显示状态：$ firewall-cmd --state
                查看区域信息: $ firewall-cmd --get-active-zones
                查看指定接口所属区域：$ firewall-cmd --get-zone-of-interface=eth0
拒绝所有包：# firewall-cmd --panic-on
取消拒绝状态：# firewall-cmd --panic-off
查看是否拒绝：$ firewall-cmd --query-panic
 
更新防火墙规则：# firewall-cmd --reload
                            # firewall-cmd --complete-reload
    两者的区别就是第一个无需断开连接，就是firewalld特性之一动态添加规则，第二个需要断开连接，类似重启服务
 
将接口添加到区域，默认接口都在public
# firewall-cmd --zone=public --add-interface=eth0
永久生效再加上 --permanent 然后reload防火墙
 
设置默认接口区域
# firewall-cmd --set-default-zone=public
立即生效无需重启
 
打开端口（貌似这个才最常用）
查看所有打开的端口：
# firewall-cmd --zone=dmz --list-ports
加入一个端口到区域：
# firewall-cmd --zone=dmz --add-port=8080/tcp
若要永久生效方法同上
 
打开一个服务，类似于将端口可视化，服务需要在配置文件中添加，/etc/firewalld 目录下有services文件夹，这个不详细说了，详情参考文档
# firewall-cmd --zone=work --add-service=smtp
 
移除服务
# firewall-cmd --zone=work --remove-service=smtp
 
还有端口转发功能、自定义复杂规则功能、lockdown，由于还没用到，以后再学习



**多知道点**
iptables实际包含五张表

大部分iptables的资料都介绍说iptables包含四张表、五条链，不过实际上iptables还有第五张表——security表，但是这张表需要和selinux结合使用，而selinux虽然已经发布了十多年了但是直到现在还有很多人对他的理解不够透彻，甚至有很多人会将其关闭！

其实selinux的设计理念在安全上来说是非常优秀的，而且理解了其设计理念之后再去使用也没那么复杂，只不过其内置的规则是非常复杂的，等有 机会学生专门给大家介绍一下selinux，现在还回到iptables的五张表，他们分别是filter、nat、mangle、raw和 security。

filter表就是我们最常使用的过滤表；nat表主要用于数据包转发，比如局域网的电脑如果想连接互联网，那么就可以使用nat给转发一 下；mangle表的规则可以对数据包进行修改，比如修改ttl值等；raw表主要是为了提高效率使用的，raw本身的含义是指“原生的”、“未经过加工 的”，符合raw表所对应规则的数据包将会跳过一些检查，这样就可以提高效率，当然，raw表的优先级也是最高的；security是跟selinux相 关的MAC模式的安全过滤。

当然，这些内容大家了解一下就行，即使不理解也可以使用将firewalld使用的很好。

 

**firewalld和iptables的关系**

firewalld自身并不具备防火墙的功能，而是和iptables一样需要通过内核的netfilter来实现，也就是说firewalld和 iptables一样，他们的作用都是用于维护规则，而真正使用规则干活的是内核的netfilter，只不过firewalld和iptables的结构以及使用方法不一样罢了。

firewalld的结构
我们这里所说的结构并不是firewalld软件的结构，而是配置文件的结构。

在具体介绍firewalld配置文件结构之前学生先来给大家介绍一下firewalld的配置模式，firewalld的配置模式设计的非常巧妙，而且这种设计思路也非常值得我们借鉴和学习。

firewalld的配置模式

firewalld的配置文件以xml格式为主（主配置文件firewalld.conf例外），他们有两个存储位置

1. /etc/firewalld/
2. /usr/lib/firewalld/

使用时的规则是这样的：当需要一个文件时firewalld会首先到第一个目录中去查找，如果可以找到，那么就直接使用，否则会继续到第二个目录中查找。

firewalld的这种配置文件结构的主要作用是这样的：在第二个目录中存放的是firewalld给提供的通用配置文件，如果我们想修改配置， 那么可以copy一份到第一个目录中，然后再进行修改。这么做有两个好处：首先我们日后可以非常清晰地看到都有哪些文件是我们自己创建或者修改过的，其 次，如果想恢复firewalld给提供的默认配置，只需要将自己在第一个目录中的配置文件删除即可，非常简单，而不需要像其他很多软件那样在修改之前还 得先备份一下，而且时间长了还有可能忘掉之前备份的是什么版本。

当然，这种配置模式也并不是firewalld的首创，在其他很多地方也都有用到，比如java中用于记录日志的logback也是这种模式，他在 查找配置文件时会首先在根目录下找logback-test.xml文件，如果可以找到就直接使用，如果找不到就会接着找logback.xml文件，如 果还找不到就会使用自己包里边自带的配置文件，这样使用起来就非常方便了，比如我们可以把logback-test.xml和logback.xml两个 文件都创建出来，在开发机上使用logback-test.xml文件，然后在往服务器部署的时候直接将其删掉就可以了！当然还有很多产品也使用了这种配 置模式，spring的很多子框架也使用的是这种模式，比如spring MVC中的组件配置也是这样，如果没有配置的话就会使用默认的配置，当然，我们这里不是在讲Spring MVC所以就不展开了，如果想了解更多细节大家可以参考学生编写的《看透Spring MVC:源代码分析与实践》一书。

配置文件结构

firewalld的配置文件结构非常简单，主要有两个文件和三个目录：

文件：firewalld.conf、lockdown-whitelist.xml

目录：zones、services、icmptypes

另外，如果使用到direct，还会有一个direct.xml文件。我们要注意，在保存默认配置的目录“/usr/lib/firewalld/”中只有我们这里所说的目录，而没有firewalld.conf、lockdown-whitelist.xml和direct.xml这三个文件，也就是说这三个文件只存在于“/etc/firewalld/”目录中。

下面学生分别来给大家介绍一下这些文件和目录的作用

firewalld.conf：firewalld的主配置文件，是键值对的格式，不过非常简单，只有五个配置项

DefaultZone：默认使用的zone，关于zone学生稍后给大家详细介绍，默认值为public；

MinimalMark： 标记的最小值，linux内核会对每个进入的数据包都进行标记，目的当然是为了对他们进行区分，比如学生在前面给大家补充iptables五张表相关的内 容时候介绍说符合raw表规则的数据包可以跳过一些检查，那么是怎么跳过的呢？这里其实就是使用的标记，当然对数据包的标记还有很多作用。这里所设置的 MinimalMark值就是标记的最小值，默认值为100，一般情况下我们不需要对其进行修改，但是如果我们有特殊需要的时候就可以通过对其进行修改来 告诉linux所使用标记的最小值了，比如我们需要给符合某条件的数据包标记为123，这时候为了防止混淆就需要将MinimalMark设置为一个大于 123的值了；

CleanupOnExit：这个配置项非常容易理解，他表示当退出firewalld后是否清除防火墙规则，默认值为yes；

Lockdown： 这个选项跟D-BUS接口操作firewalld有关，firewalld可以让别的程序通过D-BUS接口直接操作，当Lockdown设置为yes的 时候就可以通过lockdown-whitelist.xml文件来限制都有哪些程序可以对其进行操作，而当设置为no的时候就没有限制了，默认值为 no；

IPv6_rpfilter：其功能类似于rp_filter，只不过是针对ipv6版的，其作用是判断所接受到的包是否是伪造的，检查方式主要是通过路由表中的路由条目实现的，更多详细的信息大家可以搜索uRPF相关的资料，这里的默认值为yes。

lockdown-whitelist.xml：当Lockdown为yes的时候用来限制可以通过D-BUS接口操作firewalld的程序

direct.xml：通过这个文件可以直接使用防火墙的过滤规则，这对于熟悉iptables的用户来说会非常顺手，另外也对从原来的iptables到firewalld的迁移提供了一条绿色通道

zones：保存zone配置文件

services：保存service配置文件

icmptypes：保存和icmp类型相关的配置文件

 

在firewalld的使用中最基础也是最重要的就是对zone的理解，不过现在还普遍理解的不是很透彻，下面学生就来给大家详细介绍一下zone到底是什么。

zone

firewalld默认提供了九个zone配置文件：block.xml、dmz.xml、drop.xml、external.xml、 home.xml、internal.xml、public.xml、trusted.xml、work.xml，他们都保存在“/usr/lib /firewalld/zones/”目录下。这些zone之间是什么关系？他们分别适用用哪些场景呢？

为了弄明白这些问题大家需要先明白zone的本质含义。学生在上一节给大家介绍防火墙时说过防火墙就相当于一个门卫，门卫对具体某个来访的人判断是否应该放行是依靠规则来判断的，而我们这里的zone其实就是一套规则集，或者说是一套判断的方案。

理解了这层含义firewalld就容易了，比如上面的九个zone其实就是九种方案，而且起决定作用的其实是每个xml文件所包含的内容，而不是 文件名，所以大家不需要对每种zone（每个文件名）的含义花费过多的精力，比如trusted这个zone会信任所有的数据包，也就是说所有数据包都会 放行，但是public这个zone只会放行其中所配置的服务，其他的一律不予放行，其实我们如果将这两个文件中的内容互换一下他们的规则就换过来了，也 就是public这个zone会放行所有的数据包，下面我们来看一下这两个文件的内容

``` xml
public.xml

<?xml version="1.0" encoding="utf-8"?>
<zone>
  <short>Public</short>
  <description>For use in public areas. You do not trust the other computers on networks to not harm your computer. Only selected incoming connections are accepted.</description>
  <service name="ssh"/>
  <service name="dhcpv6-client"/>
</zone>
trusted.xml

<?xml version="1.0" encoding="utf-8"?>
<zone target="ACCEPT">
  <short>Trusted</short>
  <description>All network connections are accepted.</description>
</zone>
```

我们要特别注意trusted.xml中zone的target，就是因为他设置为了ACCEPT，所以才会放行所有的数据包，而 public.xml中的zone没有target属性，这样就会默认拒绝通过，所以public这个zone（这种方案）只有其中配置过的服务才可以通 过。

其他的zone大家可以自己打开xml文件来看一下，这里学生就不一一介绍了，关于zone配置文件的详细结构及含义后面学生再给大家进行讲解，下面学生再给大家介绍一下firewalld中的service。

service

service是firewalld中另外一个非常重要的概念，不过其含义是非常简单的。学生还是拿门卫的例子来给大家做解释，在iptables 的时代我们给门卫下达规则时需要告诉他“所有到22号楼的人全部予以放行”、“所有到80号楼的人全部予以放行”等等，不过到了firewalld的时代 就不需要这样了，而是可以直接下达像“到销售部的全部予以放行”这样的命令，然后门卫再一查发现销售部在80号楼，那么所有到80号楼的人门卫就都会放行 了。我们这里的楼牌号和端口号相对应，部门名和服务名相对应，这样大家应该就可以理解service的作用了。

从端口号改为服务名主要有两个好处：首先是使用服务名配置的语义清晰，不容易出错；其次在对某个服务的端口号进行修改的时候只需要修改相应的 service文件就可以了，而不需要再修改防火墙方案——zone。这其实跟DNS将ip地址和域名关联了起来是一样的道理。下面学生再来给大家介绍一 下service的配置文件。

service配置文件的命名规则是<服务名>.xml，比如ssh的配置文件是ssh.xml，http的配置文件是 http.xml等，他们默认保存在“/usr/lib/firewalld/services/”目录下，常见的服务其中都可以找到，如果我们想修改某 个服务的配置，那么可以复制一份到“/etc/firewalld/services/”目录下然后进行修改就可以了，要想恢复默认配置直接将我们自己的 配置文件删除就可以了。我们来看一下ssh服务的ssh.xml文件

``` xml
<?xml version="1.0" encoding="utf-8"?>
<service>
  <short>SSH</short>
  <description>Secure Shell (SSH) is a protocol for logging into and executing commands on remote machines. It provides secure encrypted communications. If you plan on accessing your machine remotely via SSH over a firewalled interface, enable this option. You need the openssh-server package installed for this option to be useful.</description>
  <port protocol="tcp" port="22"/>
</service>
```

可以看到这里配置了tcp的22号端口，所以将ssh服务配置到所使用的zone（默认public）中后tcp的22号端口就开放了。如果我们想将ssh的端口修改为222，那么只需要将ssh.xml复制一份到“/firewalld/services/”中，然后将端口号修改为222就可以了。当然直接修改“/usr/lib/firewalld/services/”中的配置文件也可以实现，但是强烈建议不要那么做，原因相信大家都明白。

明白原理之后使用起来就可以非常灵活了，比如我们将“/etc/firewalld/services/ssh.xml”文件复制一份到“/etc/firewalld/services/”中，然后将名字改为abc.xml，并且将abc这个服务配置到所使用的zone中，这时22端口就会开放。也就是说在zone中所配置的服务其实跟实际的服务并不存在直接联系，而是和相应配置文件中配置的内容有关系。

配置方法
firewalld的配置方法主要有三种：firewall-config、firewall-cmd和直接编辑xml文件，其中 firewall-config是图形化工具，firewall-cmd是命令行工具，而对于linux来说大家应该更习惯使用命令行方式的操作，所以 firewall-config我们就不给大家介绍了。具体的配置方法学生在下一节给大家进行介绍。

参考文献
https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Security_Guide/sec-Using_Firewalls.html







