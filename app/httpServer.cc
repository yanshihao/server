#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "Timestamp.h"
#include "Buffer.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include "http.h"


long int findCRLFx2(const Buffer* buf)
{
    const char kCRLFX2[5] = "\r\n\r\n";
    const char* crlfx2 = std::search(buf->peek(), buf->beginWrite(), kCRLFX2, kCRLFX2 + 4);
    return crlfx2 == buf->beginWrite()?-1:(crlfx2 - buf->peek());
}

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

    // 下面处理Http数据
    long int loc = findCRLFx2(buffer);
    if(loc != -1)
    {
        std::string httpRequestStr_ = buffer->retrieveAsString(loc + 4);
        HttpProcessor httpprocess(httpRequestStr_);
        std::string responsestr;
        if(true ==httpprocess.parseResult())
        {
            httpprocess.HttpProcess(responsestr);
            conptr->send(responsestr);
            if(false == httpprocess.keepalive())
            {
                conptr->shutdown();
            }
        }
        else
        {
            conptr->shutdown();
        }
    }
}

int main()
{
    EventLoop loop;
    TcpServer server(&loop,80);
    server.setMessageCallback(onMessageCallback);
    server.setConnectionCallback(onConnectionCallback);
    server.setThreadNum(4);
    server.start();
    loop.loop();
    return 0;
}