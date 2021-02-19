# Vagrant
一个简单高效 运行期无动态内存分配的c++ web服务器框架，运行在linux上，配备一个可运行的例子。
通过http请求的接收，解析，处理，再发送实现一个登陆功能。旨在展示一个完整的服务器运行流程，供初学者学习。

• 高并发（reactor 线程池）

• 运行期无动态内存分配（各种使用内存池）

• io多路复用（epoll et模式）

• 零拷贝（mmap）

• request和response类处理GET和POST

• 内置一个高效的字符串系统(引用计数)

• 内置一颗红黑树（为了运行期无动态内存分配，自己用内存池实现了一颗红黑树）

• RAII机制的mysql连接池

• 安全独立的文件访问子系统

===================================================================================================================

例子实现了从前端发送用户名和密码的登陆流程，后端收到后核对，如果密码正确则返回该用户的昵称，否则返回error。(json格式)
（框架实现了cookie相关代码，使用者可以用其实现长期登陆）

食用方法：
安装g++，mysql，mysql-dev，
创建数据库

```JAVA
create database vagrant;
use vagrant;
create table user(name char(50) NULL,passwd char(50) NULL,nick char(50) NULL);
insert into user (name,passwd,nick) values ('fawkes','123456','laoli');
exit;
```

然后在config.txt中正确填入mysql的用户名和密码，

```JAVA
make

./bin/server
```
（如果你这一步出问题了可能需要root权限）

在浏览器中访问

http://localhost:8652/index.html

