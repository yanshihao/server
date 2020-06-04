#include <sys/eventfd.h>
#include "EventLoop.h"
#include "Wakeuper.h"
#include "Channel.h"
#include <functional>
#include <unistd.h>
// EFD_CLOEXEC 创建子进程时不会复制此文件描述符
// EFD_NONBLOCK 非阻塞

int createWakeupfd()
{
    int fd = ::eventfd(0, EFD_NONBLOCK |EFD_CLOEXEC);
    if(-1 == fd)
    {
        perror("eventfd");
        exit(1);
    }
    return fd;
}

Wakeuper::Wakeuper(EventLoop* loop)
: loop_(loop), wakeupfd_(createWakeupfd()),
channel_(loop, wakeupfd_)
{
    channel_.setReadCallback(
        std::bind(&Wakeuper::onReadCallback,this)
    );
    channel_.setReadable();
}

Wakeuper::~Wakeuper()
{
    channel_.assertWorkDone();
    channel_.deleteChannel();
    int ret = ::close(wakeupfd_);
    if(-1 == ret)
    {
        perror("close wakeupfd");
    }
}

void Wakeuper::onReadCallback()
{
    uint64_t cout = 0;
    int ret = ::read(wakeupfd_,&cout, sizeof(cout));
    if(-1 == ret)
    {
        perror("write eventfd");
        exit(1);
    }
}

void Wakeuper::wakeup()
{
    uint64_t cout = 1;
    int ret = ::write(wakeupfd_,&cout, sizeof(cout));
    if(-1 == ret)
    {
        perror("write eventfd");
        exit(1);
    }
}
