#pragma once
#include <sys/epoll.h>
#include "Callback.h"

class EventLoop;
class Channel;

class Epoll
{
public:
    Epoll(EventLoop* loop);

    ~Epoll();
    
    // 给EventLoop调用的，这些函数必定在EventLoop对象所在线程调用
    // 因为通道是不会改变所处的线程的
    void poll(ChannelList& channels);
    void deleteChannel(Channel* channel);
    void updateChannel(Channel* channel);

private:
    void assertInThisLoop();

    EventLoop* loop_;

    static const int MaxFd = 1024;
    int epollfd_;

    // 表示瞬时需要处理的事件
    struct epoll_event epollEvents_[MaxFd];

    // 记录通道方便回调
    ChannelMap channelMap_;
};