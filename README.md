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