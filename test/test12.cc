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

void onMessageCallback(const TcpConnectionPtr& conptr, Buffer* buffer, Timestamp stamp)
{
    std::cout << stamp.toFormattedString() << " " << conptr->getPeerAddr().to_string() << 
    " -----> " << conptr->getLocalAddr().to_string() << std::endl;
    std::cout << "receive " << buffer->readableBytes() << " bytes : ";
    std::cout << std::string(buffer->peek(),buffer->readableBytes());
    conptr->send(buffer->retrieveAllAsString());
}

void onWriteCompleteCallback(const TcpConnectionPtr& conptr)
{
    std::cout << "write Complete" << std::endl;
    conptr->send("hehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehhehehheheh");
}

int main()
{
    EventLoop loop;
    TcpServer server(&loop,6666);
    server.setMessageCallback(onMessageCallback);
    server.setConnectionCallback(onConnectionCallback);
    server.setWriteCompleteCallback(onWriteCompleteCallback);
    server.start();
    loop.loop();
    return 0;
}