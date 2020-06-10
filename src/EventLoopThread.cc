#include "EventLoopThread.h"
#include <functional>
EventLoopThread::EventLoopThread()
:loop_(nullptr), start_(false),
thread_(std::bind(&EventLoopThread::threadFunc,this))
{

}


EventLoopThread::~EventLoopThread()
{
    loop_->quit();
    thread_.join();
}

void EventLoopThread::threadFunc()
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while(start_ == false)
            cv_.wait(lock);
    }
    EventLoop threadLoop;
    loop_ = &threadLoop;
    cv_.notify_one();
    loop_->loop();
}


EventLoop* EventLoopThread::start()
{
    start_ = true;
    cv_.notify_one();
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (loop_ == nullptr)
        {
            cv_.wait(lock);
        }
    }
    return loop_;
}