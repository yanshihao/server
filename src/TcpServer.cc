#include "TcpServer.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Acceptor.h"
#include <functional>
#include "TcpConnection.h"

using std::placeholders::_1;
using std::placeholders::_2;
TcpServer::TcpServer(EventLoop* loop, uint16_t port)
: loop_(loop),threadPool_(loop), localAddr_(port), acceptor_(new Acceptor(loop,localAddr_))
{
    acceptor_->setAccptorCallback(
        std::bind(&TcpServer::onAcceptorCallback,this,_1,_2)
    );
}

void TcpServer::setThreadNum(uint16_t n)
{
    threadPool_.setThreadNumber(n);
}

void TcpServer::start()
{
    acceptor_->start();
    threadPool_.start();
}

void TcpServer::onAcceptorCallback(int fd, const InetAddr& peerAddr)
{
    EventLoop* tloop = threadPool_.getNextLoop();
    TcpConnectionPtr newConnectionptr(new TcpConnection(tloop,fd));
    connectionMap_[newConnectionptr->toHostPortName()] = newConnectionptr;
    tloop->queueInLoop(std::bind(&TcpServer::setupConnection,this,newConnectionptr));
}


void TcpServer::removeChannelCallback(TcpConnectionPtr connptr)
{
    loop_->runInLoop(
        std::bind(&TcpServer::removeChannelInLoop, this, connptr));
}

void TcpServer::removeChannelInLoop(const TcpConnectionPtr& connptr)
{
    connectionMap_.erase(connptr->toHostPortName());
    EventLoop* tloop = connptr->getloop();
    tloop->runInLoop(
        std::bind(&TcpConnection::connectDestroyed, connptr)
    );
}

void TcpServer::setupConnection(TcpConnectionPtr newConnectionptr)
{
    newConnectionptr->setConnectionCallback(connectionCallback_);
    newConnectionptr->handleStartConnection();
    newConnectionptr->setRemoveConnectionCallback(
        std::bind(&TcpServer::removeChannelCallback,this, _1));
    newConnectionptr->setMessageCallback(messageCallback_);
    newConnectionptr->setWriteCompleteCallback(writeCompleteCallback_);
    newConnectionptr->setReadable();
}