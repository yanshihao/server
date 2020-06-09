#include "TcpConnection.h"
#include "EventLoop.h"
#include "Socket.h"
#include "Channel.h"
#include <functional>
#include <assert.h>
#include <unistd.h>
#include "Timestamp.h"
TcpConnection::TcpConnection(EventLoop* loop, int fd)
:state_(Kconnecting), loop_(loop),fd_(fd),
socket_(fd), peerAddr_(sockets::getPeerAddr(fd)), 
localAddr_(sockets::getLocalAddr(fd)), channel_(loop,fd)
{
    channel_.setReadCallback(
        std::bind(&TcpConnection::handleRead, this)
    );
    channel_.setReadable();
}

void TcpConnection::handleStartConnection()
{
    assert(state_ == Kconnecting);
    assertInThisLoop();

    if(connectionCallback_)
        connectionCallback_(shared_from_this());

    state_ = Kconnected;
}


void TcpConnection::assertInThisLoop()
{
    loop_->assertInThisThread();
}


void TcpConnection::handleKillConnection()
{
    assert(state_ == Kconnected);
    state_ = Kdisconnecting;
    // 去掉TcpServer的备份，并注册一个插入事件处理连接
    removeConnectionCallback_(shared_from_this());
    state_ = KdisConnected;
}

TcpConnection::~TcpConnection()
{
    assert(state_ == KdisConnected);
    channel_.deleteChannel();
}

void TcpConnection::handleRead()
{
    int saveErrno;
    size_t n = inputBuffer_.readFd(fd_, &saveErrno);
    if(n == 0)
    {
        handleKillConnection();
    }
    else if(n > 0)
    {
        messageCallback_(shared_from_this(),&inputBuffer_, Timestamp::now());   
    }
    else
    {
        errno = saveErrno;
        handleError();
    }
}