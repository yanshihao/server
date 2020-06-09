#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include "Socket.h"
// 客户端

int main()
{
    int clientfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    InetAddr peerAddr("127.0.0.1", 6666);
    struct sockaddr_in addr = peerAddr.getAddr();
    if(::connect(clientfd,(sockaddr*)&addr,sizeof(addr))== -1 )
    {
        perror("connect");
        exit(1);
    }
    InetAddr localAddr(sockets::getLocalAddr(clientfd));
    std::cout << localAddr.to_string() << "---->" << peerAddr.to_string() << std::endl;
    return 0;
}