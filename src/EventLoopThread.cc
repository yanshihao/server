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
    EventLoop threadLoop;

    {
        std::unique_lock<std::mutex>  lock(mutex_);
        loop_ = &threadLoop;
        cv_.notify_one();
    }
    loop_->loop();
}


EventLoop* EventLoopThread::start()
{
    start_ = true;
    
    {
        std::unique_lock<std::mutex> lock(mutex_);
        while (loop_ == nullptr)
        {
            cv_.wait(lock);
        }
    }

    return loop_;
}