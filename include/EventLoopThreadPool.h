#pragma once
#include <vector>
#include "EventLoopThread.h"
class EventLoop;


class EventLoopThreadPool
{
public:
    EventLoopThreadPool(EventLoop* mainLoop);

    // 只能调用1次
    void setThreadNumber(uint16_t n);
    void start();
    EventLoop* getNextLoop();
    ~EventLoopThreadPool();

private:
    EventLoop* mainLoop_;
    std::vector<EventLoopThread*> LoopThreads_;
    std::vector<EventLoop*>  loops_;
    uint16_t nums_;
    uint16_t nextNum_;// 下一个线程的数字
};

