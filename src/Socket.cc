#include "Socket.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <string.h>
#include <arpa/inet.h>
#include <endian.h>

InetAddr::InetAddr(std::string&& ipAddress, uint16_t port)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if(::inet_pton(AF_INET6,ipAddress.c_str(), &addr_.sin_addr) < 0)
    {
        perror("inet_ptorn");
        exit(1);
    }
}

InetAddr::InetAddr(uint16_t port)
{
    bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);
}

std::string InetAddr::to_string() const
{
    char host[16] = "INVALID";
    if(::inet_ntop(AF_INET, &addr_.sin_addr,host,sizeof(host)) < 0 )
    {
        perror("inet_ntop");
        exit(1);
    }
    uint16_t port = ::ntohs(addr_.sin_port);
    char buf[32];
    snprintf(buf, sizeof(buf),"%s:%d", host, port);
    return buf;
}

Socket::~Socket()
{
    if(::close(fd_) == -1)
    {
        perror("close socket fd");
    }
}

void Socket::bind(const InetAddr& localAddr)
{
    struct sockaddr_in addr = localAddr.getAddr();
    int ret = ::bind(fd_, (sockaddr *)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("bind");
        exit(1);
    }
}

void Socket::listen()
{
    // 等待连接的队列，之前有做过相关的测试
    int ret = ::listen(fd_,SOMAXCONN);
    if(ret == -1)
    {
        perror("listen");
        exit(1);
    }
}

int Socket::accept(InetAddr& peerAddr)
{
    struct sockaddr_in addr = peerAddr.getAddr();
    socklen_t len = sizeof(addr);
    int connfd = ::accept(fd_,(sockaddr*)&addr, &len);
    
    int saveErrno = errno;
    // 在创建之初就应当将套接字设置成 非阻塞和 禁止子进程复制文件描述符

    // 取得文件状态标志
    int flag = ::fcntl(connfd,F_GETFL,0);
    flag |= O_NONBLOCK;
    int ret = ::fcntl(connfd,F_SETFL,flag);
    if(ret == -1)
    {
        perror("fcntl set nonBlock");
        exit(1);
    }
    // close-on-exec
    flag = ::fcntl(connfd,F_GETFD, 0);
    flag |= FD_CLOEXEC;
    ret = ::fcntl(connfd,F_SETFD, flag);
    if(ret == -1)
    {
        perror("fcntl set cloexec");
        exit(1);
    }

    if(connfd == -1)
    {
        errno = saveErrno; 
        switch (saveErrno)
        {
        case EAGAIN:
        case EINTR:
            
            break;
        case EBADF:
        case EFAULT:
        case EINVAL:
        case ENFILE:
        case ENOBUFS:
        case ENOMEM:
        case ENOTSOCK:
        case EOPNOTSUPP:
            perror("accept");
            exit(1);
            break;
        default:
            perror("accept");
            exit(1);
            break;
        }
    }
    else
    {
        peerAddr.setAddr(addr);
    }
    return connfd;
}


void Socket::setReuseAddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR,
               &optval, sizeof optval);
}

void Socket::setTcpNoDelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY,
               &optval, sizeof optval);
}


// 写方向 shutdown, 单方面关闭
void Socket::shutdownWrite()
{
    int ret = ::shutdown(fd_,SHUT_WR);
    if(ret == -1)
    {
        perror("shutdown");
        exit(1);
    }
}

struct sockaddr_in sockets::getLocalAddr(int sockfd)
{
    struct sockaddr_in localaddr;
    bzero(&localaddr, sizeof localaddr);
    socklen_t addrlen = sizeof(localaddr);
    if (::getsockname(sockfd, (sockaddr*)(&localaddr), &addrlen) < 0)
    {
        perror("getsockname");
        exit(1);
    }
    return localaddr;
}

struct sockaddr_in sockets::getPeerAddr(int sockfd)
{
    struct sockaddr_in peeraddr;
    bzero(&peeraddr, sizeof peeraddr);
    socklen_t addrlen = sizeof(peeraddr);
    if (::getpeername(sockfd, (sockaddr*)(&peeraddr), &addrlen) < 0)
    {
        perror("getpeername");
        exit(1);
    }
    return peeraddr;
}