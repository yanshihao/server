// 此测试文件主要用来测试 Socket类和 InetAddr类
// 这些类通过面向对象，简化了操作
#include "Socket.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
// 服务端
int main()
{
    int serverfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    Socket soc(serverfd);
    InetAddr inetAddr(6666);
    soc.setReuseAddr(true);
    soc.setTcpNoDelay(true);
    soc.bind(inetAddr);
    soc.listen();
    InetAddr peerAddr;
    int fd;
    while(fd = soc.accept(peerAddr))
    {
        std::cout << fd << std::endl;
        std::cout << peerAddr.to_string() << "----->" << inetAddr.to_string() << std::endl;
    }
}