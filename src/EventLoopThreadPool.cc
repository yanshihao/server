#include "EventLoopThreadPool.h"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* mainLoop)
:mainLoop_(mainLoop),nextNum_(0), nums_(0)
{

}

EventLoopThreadPool::~EventLoopThreadPool()
{

}

void EventLoopThreadPool::start()
{
    if(LoopThreads_.size() > 0)
    {
        for(int i = 0; i < LoopThreads_.size(); i++)
        {
            loops_.push_back(LoopThreads_[i]->start());
        }
    }
}

void EventLoopThreadPool::setThreadNumber(uint16_t n)
{
    if(nums_ != 0) return;
    for(int i = 0; i < n; i++)
    {
        EventLoopThread* loopThread = new EventLoopThread;
        LoopThreads_.push_back(loopThread);
    }
    nums_ = n;
}

EventLoop* EventLoopThreadPool::getNextLoop()
{
    if(nums_ == 0)
    {
        return mainLoop_;
    }
    else
    {
        uint16_t tempnum = nextNum_;
        nextNum_ = (tempnum+1)%nums_;
        return loops_[tempnum];
    }
}