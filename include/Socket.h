#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

class InetAddr
{
public:
    InetAddr(){}

    InetAddr(std::string&& ipAddress, uint16_t port);
    InetAddr(const struct sockaddr_in addr)
    : addr_(addr){};
    
    // 主机地址
    InetAddr(uint16_t port);

    struct sockaddr_in getAddr() const {return addr_;}
    
    void setAddr(const struct sockaddr_in& addr)
    {
        addr_ = addr;
    }

    std::string to_string() const;

private:
    struct sockaddr_in addr_;
};

// 封装好的类
class Socket
{
public:
    Socket(int fd):fd_(fd){}
    ~Socket();
    void bind(const InetAddr& localAddr);
    void listen();

    // 返回-1 或者文件描述符
    int accept(InetAddr& peerAddr);

    // 设置无延迟
    void setTcpNoDelay(bool on);
    // 设置子进程不可重用
    void setReuseAddr(bool on);
    // 单方面关闭通道
    void shutdownWrite();
private:
    int fd_;
};

namespace sockets
{
    struct sockaddr_in getLocalAddr(int sockfd);
    struct sockaddr_in getPeerAddr(int sockfd);
    void setReuseAddr(int fd);
    int createListenfd();
};