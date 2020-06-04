////////////////////////////////////
/////  epoll events字段
//  EPOLLIN  有数据输入
//  EPOLLPRI 有紧急数据输入
//  EPOLLOUT 可输出数据
//  EPOLLRDNORM  有普通数据可读
//  EPOLLRDBAND  有优先数据可读
//  EPOLLWRNORM  写普通数据不会导致阻塞
//  EPOLLWRBAND  写优先数据不会导致阻塞
//  EPOLLERR     对应的文件描述符发生错误
//  EPOLLHUP     挂断
//  EPOLLRDHUP   对端断开
//  EPOLLET      边沿触发

// 对端断开会触发  EPOLLRDHUP|EPOLLIN 这个事件
// 对端有消息会触发 EPOLLIN | EPOLLPRI
// 本端可写会触发   EPOLLOUT
// 边沿触发        EPOLLET

#pragma once
#include <stdint.h>
#include "Callback.h"
class EventLoop;

class Channel
{
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();

    // 供Epoll读取信息
    int getfd() {return fd_;} 
    uint32_t getEvents() {return events_;}

    //给 Epoll调用的，只允许在EventLoop所在的线程调用
    void setRevent(uint32_t revents)
    {
        revents_ = revents;
    }

    // EventLoop调用，只允许在EventLoop所在线程调用
    void handle();

    void setReadCallback(const Callback& cb)
    {
        readCallback_ = cb;
    }
    void setWriteCallback(const Callback& cb)
    {
        writeCallback_ = cb;
    }
    void setErrorCallback(const Callback& cb)
    {
        errorCallback_ = cb;
    }

    void setCloseCallback(const Callback& cb)
    {
        closeCallback_ = cb;
    }
    void setReadable();
    void setWritable();
    void setUnWritable();
    void setErrorable();

private:
    void assertInThisLoop();
    void updateChannel();
    void deleteChannel();
    EventLoop* loop_;
    int fd_;
    uint32_t events_;
    uint32_t revents_;

    Callback readCallback_;
    Callback writeCallback_;
    Callback errorCallback_;
    Callback closeCallback_;
    bool handlework_;
};