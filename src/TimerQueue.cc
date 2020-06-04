#include "EventLoop.h"
#include "TimerQueue.h"
#include <sys/timerfd.h>
#include <unistd.h>
#include <string.h>
#include "Timestamp.h"

// CLOCK_REALTIME   系统实时时间，会随着系统时间的更改而变化
// CLOCK_MONOTONIC  从系统启动的时间开始计算，不受系统时间被用户改变的影响

int createTimerfd()
{
    int fd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC|TFD_NONBLOCK);
    if(fd == -1)
    {
        perror("timerfd_create");
        exit(1);
    }
    return fd;
}

void readTimerfd(int fd)
{
    // 读一下timerfd
    uint64_t time;
    ssize_t n = ::read(fd,&time, sizeof(time));
    if(n != sizeof(time))
    {
        perror("read timerfd");
        exit(1);
    }
}

// 计算相对属性
static struct timespec howMuchTimeFromNow(Timestamp when)
{
    int64_t microseconds = when.microSecondsSinceEpoch()
                          - Timestamp::now().microSecondsSinceEpoch();
    if (microseconds < 100)
    {
      microseconds = 100;
    }
    struct timespec ts;
    ts.tv_sec = static_cast<time_t>(
        microseconds / Timestamp::kMicroSecondsPerSecond);
    ts.tv_nsec = static_cast<long>(
        (microseconds % Timestamp::kMicroSecondsPerSecond) * 1000);
    return ts;
}

void writeTimerfd(int fd, const Timestamp& stamp)
{
    struct itimerspec newValue;
    struct itimerspec oldValue;
    bzero(&newValue,sizeof(newValue));
    bzero(&oldValue, sizeof(oldValue));
    newValue.it_value = howMuchTimeFromNow(stamp);
    int ret = ::timerfd_settime(fd, 0,&newValue,&oldValue);
    if(-1 == ret)
    {
        perror("timerfd_settime");
        exit(1);
    }
}

TimerQueue::TimerQueue(EventLoop* loop)
: loop_(loop), timerfd_(createTimerfd()), channel_(loop,timerfd_)
{
    channel_.setReadCallback(
        std::bind(&TimerQueue::onReadCallback, this)
    );
    channel_.setReadable();
}

TimerQueue::~TimerQueue()
{
    channel_.deleteChannel();
    int ret = ::close(timerfd_);
    if(-1 == ret)
    {
        perror("close timerfd");
    }
}

void TimerQueue::onReadCallback()
{
    assertInThisLoop();
    readTimerfd(timerfd_);
    Timestamp now(Timestamp::now());
    while(now > timerList_.top()->getStamp())
    {
        TimerPtr timerptr = timerList_.top();
        timerList_.pop();
        timerptr->call();
        if(timerptr->repreat())
        {
            timerptr->reuse();
            timerList_.push(timerptr);
        }
    }
    if(!timerList_.empty())
    {
        writeTimerfd(timerfd_, timerList_.top()->getStamp());
    }
}


void TimerQueue::addTimer(const Timestamp& stamp, 
            Callback cb, double interval)
{
    assertInThisLoop();
    // 如果比当前时间还小，直接运行
    if(stamp < Timestamp::now())
    {
        cb();
        return;
    }

    TimerPtr timerptr(new Timer(stamp,cb,interval));
    // 如果小于堆顶时间，则重置
    if(stamp < timerList_.top()->getStamp())
    {
        writeTimerfd(timerfd_, stamp);   
    }
    // 总是要插入堆的
    timerList_.push(timerptr);
}

void TimerQueue::assertInThisLoop()
{
    loop_->assertInThisThread();
}