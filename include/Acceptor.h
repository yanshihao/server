#pragma once
#include "Socket.h"
#include "Channel.h"
#include "Callback.h"
class EventLoop;

// 服务器独有
class Acceptor
{
public:
    Acceptor(EventLoop* loop, const InetAddr& addr);
    ~Acceptor();

    void setAccptorCallback(const AcceptorCallback& cb)
    {
        acceptorCallback_ = cb;
    }
private:
    void handleRead();
    void assertInThisLoop();
    EventLoop* loop_;
    int listenfd_;
    Socket listenSocket_;
    InetAddr localAddr_;
    Channel channel_;
    AcceptorCallback acceptorCallback_;
};