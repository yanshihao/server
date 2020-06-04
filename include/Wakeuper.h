#pragma once

#include "Channel.h"
class EventLoop;

class Wakeuper{
public:
    Wakeuper(EventLoop* loop);
    ~Wakeuper();

    // 可以从其他线程调用也可以本线程调用
    // 由于操纵wakeupfd 没有竞态所以不用设计
    void wakeup();

private:
    void onReadCallback();
    EventLoop* loop_;
    int wakeupfd_;
    Channel channel_;
};