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
localAddr_(sockets::getLocalAddr(fd)), channel_(loop,fd),
writing_(false)
{
    channel_.setReadCallback(
        std::bind(&TcpConnection::handleRead, this)
    );
    channel_.setWriteCallback(
        std::bind(&TcpConnection::handleWrite,this)
    );
    channel_.setReadable();
}

void TcpConnection::handleStartConnection()
{
    assert(state_ == Kconnecting);
    assertInThisThread();

    if(connectionCallback_)
        connectionCallback_(shared_from_this());

    state_ = Kconnected;
}


void TcpConnection::assertInThisThread()
{
    loop_->assertInThisThread();
}


void TcpConnection::handleKillConnection()
{
    assert((state_ == Kconnected) || (state_ == Kdisconnecting));
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
    int n = inputBuffer_.readFd(fd_, &saveErrno);
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
        perror("read");
        handleKillConnection();
        handleError();
    }
}

bool TcpConnection::inThisThread()
{
    return loop_->inThisThread();
}

void TcpConnection::send(const std::string& str)
{
    if(inThisThread())
    {
        sendInLoop(str);
    }
    else
    {
        loop_->queueInLoop(
            std::bind(&TcpConnection::sendInLoop, this, str)
        );   
    }
}

void TcpConnection::sendInLoop(std::string str)
{
    assertInThisThread();
    if((state_ == KdisConnected) || state_ == Kdisconnecting)
    {
        return;
    }
    if(writing_ == true)
    {
        outputBuffer_.append(str);
    }
    else
    {
        int n = ::write(fd_,str.c_str(),str.size());
        if(n == -1)
        {
            handleError();
        }
        else if(n == str.size())
        {
            // 写完全，需要调用写完整函数
            if(writeCompleteCallback_)
                writeCompleteCallback_(shared_from_this());
        }
        else
        {
            outputBuffer_.append(str.c_str() + n, str.size() - n);
            // 需要监控可写事件
            channel_.setWritable();
            writing_ = true;
        }
    }
}

void TcpConnection::handleWrite()
{
    if(state_ == KdisConnected)
    {
        return;
    }
    assert(writing_ == true);
    int n = ::write(fd_, outputBuffer_.peek(), outputBuffer_.readableBytes());
    if(n == -1)
    {
        perror("write");
        handleKillConnection();
        handleError();
    }
    else
    {
        outputBuffer_.retrieve(n);
        if(outputBuffer_.readableBytes() == 0)
        {
            channel_.setUnWritable();
            writing_ = false;
            if(state_ == Kdisconnecting)
                shutdownInLoop();
            if(writeCompleteCallback_)
                writeCompleteCallback_(shared_from_this());
        }
    }
}

void TcpConnection::handleError()
{
    
}

void TcpConnection::shutdown()
{
    state_ = Kdisconnecting;
    loop_->runInLoop(
        std::bind(&TcpConnection::shutdownInLoop, this)
    );   
}

void TcpConnection::shutdownInLoop()
{
    assertInThisThread();
    if(writing_ == false)
    {
        socket_.shutdownWrite();
    }
}