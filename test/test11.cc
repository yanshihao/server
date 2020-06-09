#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include <iostream>

void onConnectionCallback(const TcpConnectionPtr& connectionPtr)
{
    if(connectionPtr->IsConnecting())
        std::cout << connectionPtr->getPeerAddr().to_string() <<
    "--------> " << connectionPtr->getLocalAddr().to_string() <<
    std::endl;
    if(connectionPtr->isDisConnecting())
        std::cout << connectionPtr->getPeerAddr().to_string() <<
    "---||---> " << connectionPtr->getLocalAddr().to_string() <<
    std::endl;
}


int main()
{
    EventLoop loop;
    TcpServer server(&loop,6666);
    server.setConnectionCallback(onConnectionCallback);
    server.start();
    loop.loop();
    return 0;
}
