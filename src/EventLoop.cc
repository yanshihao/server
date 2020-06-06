#include "EventLoop.h"
#include "Channel.h"
#include <chrono>
#include <stdio.h>
#include <assert.h>
#include "Epoll.h"
#include "Wakeuper.h"
#include "TimerQueue.h"
__thread EventLoop* t_loop = nullptr;

EventLoop::EventLoop()
:threadId_(std::this_thread::get_id()),
epoll_(new Epoll(this)), callingPendingFunctors_(false),
loop_(false), quit_(false),wakeuper_(new Wakeuper(this)),
timerQueue_(new TimerQueue(this))
{
    if(t_loop == nullptr)
        t_loop = this;
    else
    {
        printf("one thread only one loop");
        exit(1);   
    }
}

EventLoop::~EventLoop()
{
    assert(loop_ == false);
    t_loop = nullptr;
}

void EventLoop::loop()
{
    assertInThisThread();
    loop_ = true;
    while(!quit_)
    {
        ChannelList channels;
        epoll_->poll(channels);

        for(auto iter = channels.begin(); iter !=channels.end(); ++iter)
        {
            (*iter)->handle();
        }
        
        doPendingWorks();
    }
    loop_ = false;
}

void EventLoop::quit()
{
    quit_ = true;
    wakeup();
}

bool EventLoop::inThisThread()
{
    return threadId_ == std::this_thread::get_id();
}

void EventLoop::assertInThisThread()
{
    assert(true == inThisThread());
}

void EventLoop::doPendingWorks()
{
    callingPendingFunctors_ = true;
    std::vector<Task> functors;
    {
        std::unique_lock<std::mutex> lock(mutex_);
        functors.swap(pendingWorks_);
    }

    for(auto func:functors)
        func();
    
    callingPendingFunctors_ = false;
}


void EventLoop::queueInLoop(const Task& task)
{
    {
        std::unique_lock<std::mutex> lock(mutex_);
        pendingWorks_.push_back(task);
    }

    if(!inThisThread() || (callingPendingFunctors_ == true))
    {
        wakeup();
    }
}

void EventLoop::runInLoop(const Task& task)
{
    if(inThisThread())
    {
        task();
    }
    else
    {
        queueInLoop(task);
    }
}


void EventLoop::updateChannel(Channel* channel)
{
    epoll_->updateChannel(channel);
}

void EventLoop::deleteChannel(Channel* channel)
{
    epoll_->deleteChannel(channel);
}

void EventLoop::wakeup()
{
    wakeuper_->wakeup();
}

void EventLoop::runAt(const Timestamp& stamp, const Callback& cb)
{  
    runInLoop(
        std::bind(&EventLoop::addTimer,this,
        stamp, cb, 0)
    );
}

void EventLoop::runAfter(double after, const Callback& cb)
{
    Timestamp when = addTime(Timestamp::now(),after);
    runAt(when,cb);
}

void EventLoop::runEvery(double after, double interval, const Callback& cb)
{
    runInLoop(
        std::bind(&EventLoop::addTimer,this,
        addTime(Timestamp::now(),after), cb, interval)
    );
}

void EventLoop::addTimer(Timestamp stamp, const Callback& cb, double interval)
{
    timerQueue_->addTimer(stamp,cb,interval);
}