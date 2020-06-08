#include "EventLoop.h"
#include "Channel.h"
#include "Socket.h"
#include "Acceptor.h"

Acceptor::Acceptor(EventLoop* loop, const InetAddr& addr)
:loop_(loop),listenfd_(sockets::createListenfd()),
listenSocket_(listenfd_), localAddr_(addr)
,channel_(loop, listenfd_)
{
    listenSocket_.bind(localAddr_);
    listenSocket_.listen();
    channel_.setReadCallback(
        std::bind(&Acceptor::handleRead,this));
    channel_.setReadable();
}

Acceptor::~Acceptor()
{
    channel_.deleteChannel();
}

void Acceptor::handleRead()
{
    assertInThisLoop();
    InetAddr peerAddr;
    int connfd = listenSocket_.accept(peerAddr);
    if(connfd != -1)
    {
        acceptorCallback_(connfd,peerAddr);
    }
}


void Acceptor::assertInThisLoop()
{
    loop_->assertInThisThread();
}