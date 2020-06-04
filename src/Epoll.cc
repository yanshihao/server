#include "Epoll.h"
#include <sys/epoll.h>
#include "Channel.h"
#include "EventLoop.h"
#include <assert.h>
#include <unistd.h>
// 更加精细的错误处理

int createEpollFd()
{
    int fd = epoll_create(1024);
    if(fd == -1)
    {
        perror("epoll_create");
        exit(1);
    }
    return fd;
}

Epoll::Epoll(EventLoop* loop)
:loop_(loop), epollfd_(createEpollFd())
{

}

Epoll::~Epoll()
{
    int ret = ::close(epollfd_);
    if(ret == -1)
    {
        perror("close");
        // 就不强制退出了
    }
}

void Epoll::assertInThisLoop()
{
    loop_->assertInThisThread();
}

void Epoll::deleteChannel(Channel* channel)
{
    assertInThisLoop();
    // 首先是删除ChannelMap的记录
    int fd = channel->getfd();
    auto iter = channelMap_.find(fd);
    assert(iter != channelMap_.end());
    channelMap_.erase(iter);
    int ret = epoll_ctl(epollfd_,EPOLL_CTL_DEL,fd,nullptr);
    if(ret == -1)
    {
        perror("epoll_ctl del");
        exit(1);
    }
}

void Epoll::updateChannel(Channel* channel)
{
    assertInThisLoop();
    // 首先寻找
    struct epoll_event newEvent;
    int fd = channel->getfd();
    newEvent.data.fd = fd;
    newEvent.events = channel->getEvents();

    // 存在则更新
    if(channelMap_.find(fd) != channelMap_.end())
    {
        assert(channelMap_[fd] == channel);
        if(-1 == epoll_ctl(epollfd_,EPOLL_CTL_MOD,fd, &newEvent))
        {
            perror("epoll_ctl mod");
            exit(1);
        }
    }
    else  // 不存在则插入
    {
        if(-1 == epoll_ctl(epollfd_,EPOLL_CTL_ADD,fd, &newEvent))
        {
            perror("epoll_ctl mod");
            exit(1);
        }
        channelMap_[fd] = channel;
    }
}

void Epoll::poll(ChannelList& channels)
{
    int numbers = epoll_wait(epollfd_, epollEvents_,MaxFd,5000);
    if(numbers == -1)
    {
        perror("epoll_wait");
        // 错误事件处理可以更加精细
        exit(1);
    }
    else if(numbers == 0)
    {
        ;
    }
    else
    {
        for(int i = 0; i < numbers; ++i)
        {
            int fd = epollEvents_[i].data.fd;
            int events = epollEvents_[i].events;
            auto iter = channelMap_.find(fd);

            // 断言存在
            assert(iter != channelMap_.end());
            // 更新事件
            iter->second->setRevent(events);
            // 返回通道列表
            channels.push_back(iter->second);
        }    
    }
}