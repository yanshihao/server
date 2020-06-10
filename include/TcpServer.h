#pragma once
#include <memory>
#include "Callback.h"
#include "Socket.h"
#include <map>
#include <string>
#include "EventLoopThreadPool.h"

class EventLoop;
class Acceptor;
class TcpConnection;
class InetAddr;

typedef std::map<std::string, TcpConnectionPtr> TcpConnectionMap;

class TcpServer
{
public:
    TcpServer(EventLoop* loop, uint16_t port);
    ~TcpServer() {};

    void setThreadNum(uint16_t n);
    void setConnectionCallback(const ConnectionCallback& cb)
    {
        connectionCallback_ = cb;
    }

    void setMessageCallback(const MessageCallback& cb)
    {
        messageCallback_ = cb;
    }

    void setWriteCompleteCallback(const WriteCompleteCallback& cb)
    {
        writeCompleteCallback_ = cb;
    }

    void start();
private:
    void onAcceptorCallback(int fd, const InetAddr& peerAddr);
    void removeChannelCallback(TcpConnectionPtr connptr);

    EventLoop* loop_;
    
    EventLoopThreadPool threadPool_;

    InetAddr localAddr_;
    std::shared_ptr<Acceptor> acceptor_;
    
    TcpConnectionMap connectionMap_;

    // 建立连接和断开连接时的处理
    ConnectionCallback connectionCallback_;

    // 有消息送到时的处理
    MessageCallback    messageCallback_;

    // 当写完成时的处理
    WriteCompleteCallback writeCompleteCallback_;
};

