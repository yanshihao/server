#include "Channel.h"
#include "EventLoop.h"
#include <assert.h>
#include <sys/epoll.h>

Channel::Channel(EventLoop* loop, int fd)
:loop_(loop), fd_(fd), events_(EPOLLET),
 revents_(0), handlework_(false)
{

}

void Channel::assertWorkDone()
{
    assert(handlework_ == false);
}

Channel::~Channel()
{
}

void Channel::handle()
{
    assertInThisLoop();
    handlework_ = true;

    // 先处理错误事件
    if(revents_ & EPOLLERR)
    {
        if(errorCallback_) errorCallback_();
    }
    if(revents_ & EPOLLIN)
        if(readCallback_) readCallback_();
    if(revents_ & EPOLLOUT)
        if(writeCallback_) writeCallback_();
    handlework_ = false;
}

void Channel::setReadable()
{
    events_ |= (EPOLLIN |EPOLLPRI);
    updateChannel();
}

void Channel::setWritable()
{
    events_ |= EPOLLOUT;
    updateChannel();
}

void Channel::setErrorable()
{
    events_ |= EPOLLERR;
    updateChannel();
}

void Channel::setUnWritable()
{
    events_ &= ~ (uint32_t) EPOLLERR;
    updateChannel();
}

void Channel::assertInThisLoop()
{
    loop_->assertInThisThread();
}

void Channel::updateChannel()
{
    loop_->updateChannel(this);
}

void Channel::deleteChannel()
{
    assertInThisLoop();
    loop_->deleteChannel(this);
}