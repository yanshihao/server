#pragma once
#include <string>
#include <memory>
#include "Socket.h"
#include "Channel.h"
class EventLoop;
class Channel;

class TcpConnection
:public std::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop, int fd);
    ~TcpConnection();
    
    std::string toHostPortName(){
        return peerAddr_.to_string();
    }
    
    void setConnectionCallback(const ConnectionCallback& cb)
    {
        connectionCallback_ = cb;
    }

    void setRemoveConnectionCallback(const RemoveConnectionCallback& cb)
    {
        removeConnectionCallback_ = cb;
    }

    void handleStartConnection();

    const InetAddr& getPeerAddr() const {return peerAddr_;}
    const InetAddr& getLocalAddr() const {return localAddr_;}
    bool IsConnecting() const {return state_ == Kconnecting;}
    bool isDisConnecting() const {return state_ == KdisConnected;}

private:
    void assertInThisLoop();

    void handleRead();

    void handleKillConnection();
    
    enum State{
        Kconnecting, Kconnected, 
        Kdisconnecting,KdisConnected
    };

    State state_;

    EventLoop* loop_;
    
    int fd_;
    
    Socket socket_;
    
    InetAddr peerAddr_;
    InetAddr localAddr_;

    std::string inputbuf;
    std::string outputbuf;

    Channel channel_;

    ConnectionCallback connectionCallback_;
    RemoveConnectionCallback removeConnectionCallback_;
};