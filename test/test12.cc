#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Timestamp.h"
#include "Buffer.h"
#include <iostream>
#include <functional>

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

void hehe(const TcpConnectionPtr& conptr, Buffer* buffer, Timestamp stamp)
{
    std::cout << stamp.toFormattedString() << " " << conptr->getPeerAddr().to_string() << 
    " -----> " << conptr->getLocalAddr().to_string() << std::endl;
    std::cout << "receive " << buffer->readableBytes() << " bytes : ";
    std::cout <<buffer->retrieveAllAsString();
}
int main()
{
    EventLoop loop;
    TcpServer server(&loop,6666);
    server.setMessageCallback(hehe);
    server.setConnectionCallback(onConnectionCallback);
    server.start();
    loop.loop();
    return 0;
}