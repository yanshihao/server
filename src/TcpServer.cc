#include "TcpServer.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Acceptor.h"
#include <functional>
#include "TcpConnection.h"

using std::placeholders::_1;
using std::placeholders::_2;
TcpServer::TcpServer(EventLoop* loop, uint16_t port)
: loop_(loop), localAddr_(port), acceptor_(new Acceptor(loop,localAddr_))
{
    acceptor_->setAccptorCallback(
        std::bind(&TcpServer::onAcceptorCallback,this,_1,_2)
    );
}

void TcpServer::start()
{
    acceptor_->start();
}

void TcpServer::onAcceptorCallback(int fd, const InetAddr& peerAddr)
{
    TcpConnectionPtr newConnectionptr(new TcpConnection(loop_,fd));
    connectionMap_[newConnectionptr->toHostPortName()] = newConnectionptr;
    newConnectionptr->setConnectionCallback(connectionCallback_);
    newConnectionptr->setRemoveConnectionCallback(
        std::bind(&TcpServer::removeChannelCallback,this, _1));
    newConnectionptr->setMessageCallback(messageCallback_);
    newConnectionptr->setWriteCompleteCallback(writeCompleteCallback_);
    newConnectionptr->handleStartConnection();
}

void TcpServer::removeChannelCallback(TcpConnectionPtr connptr)
{
    connectionMap_.erase(connptr->toHostPortName());
    loop_->queueInLoop(
        std::bind(connectionCallback_,connptr)
    );
}