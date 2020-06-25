1. 首先设计一个不带日志的多线程网络库

Class EventLoop;        事件循环
Class Epoll;            Epoll
Class Channel;          IO通道
Class Acceptor;         接收者
Class TcpConnection;    TCP连接
Class TimerQueue;       时间队列
Class Wakeuper;         唤醒者

Class Buffer;           缓冲
Class Timer;            记录时间
Class Timestamp;        时间戳
class Socket;           套节字及一些套接字的便利函数

class Tcpserver;

2. 定义回调函数接口

3. EventLoop， Epoll, Channel

4. Wakeuper, TimerQueue

5. Socket, Buffer, Acceptor, Tcpserver, TcpConnection


6. nothing

7. sharedptr 很难确定在哪个线程被销毁

   std::bind 好像不能绑定右值引用

   shutdown之后也要记得销毁Tcp连接，不然最后文件描述符都用不了了

   多线程比之单线程并没有明显的提升，这是因为处理的任务太简单，多线程还要用在调度上

   accept会产生-1大概率是因为文件描述符不够了，可是本系统的文件描述符才用到8000多，应该还好才对阿

   换个思路考虑问题，本来想着把通道的删除放在析构函数中，然而很难确定析构函数在哪个线程被调用，因此可以转换成在IO线程shutdown或者收到0个字节的时候调用通道的删除，可以确定线程

   再仔细研究一下sharedptr的用法

8. 