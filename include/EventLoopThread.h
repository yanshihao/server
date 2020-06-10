#pragma once
#include "EventLoop.h"
#include <thread>
#include <mutex>
#include <condition_variable> 
class EventLoopThread
{
public:
    EventLoopThread();
    EventLoop* start();
    ~EventLoopThread();
private:
    void threadFunc();
    EventLoop* loop_;
    bool start_;
    std::thread thread_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
