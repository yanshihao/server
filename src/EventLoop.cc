#include "EventLoop.h"
#include "Channel.h"
#include <chrono>
#include <stdio.h>
#include <assert.h>
#include "Epoll.h"

__thread EventLoop* t_loop = nullptr;

EventLoop::EventLoop()
:threadId_(std::this_thread::get_id()),
epoll_(new Epoll(this)), callingPendingFunctors_(false),
loop_(false), quit_(false)
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
    std::unique_lock<std::mutex> lock(mutex_);
    pendingWorks_.push_back(task);
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