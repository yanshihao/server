#pragma once
#include "Timestamp.h"
#include "Callback.h"
#include "Channel.h"
#include <memory>
#include <queue>
class EventLoop;

class Timer{
public:
    Timer(const Timestamp& stamp, Callback cb, double interval)
    :stamp_(stamp), timeCallback_(cb),
    interval_(interval), repeat_(interval_ > 0 ? true:false)
    {

    }
    const Timestamp& getStamp() {return stamp_;}
    void call() {timeCallback_();}
    bool repreat() {return repeat_;}
    void reuse()
    {
        stamp_  = addTime(stamp_ , interval_);
    }
private:
    Timestamp stamp_;
    Callback timeCallback_;
    int interval_;
    bool repeat_;
};
typedef std::shared_ptr<Timer> TimerPtr;

struct Cmp
{
    bool operator()(const TimerPtr& timer1, const TimerPtr& timer2)
    {
        return timer1->getStamp() > timer2->getStamp();
    }
};

typedef std::priority_queue<TimerPtr, std::vector<TimerPtr>, Cmp> TimerList;


class TimerQueue{
public:
    TimerQueue(EventLoop* loop);
    ~TimerQueue();
    void addTimer(const Timestamp& stamp, Callback cb, double interval);
private:
    void assertInThisLoop();
    void onReadCallback();
    EventLoop* loop_;
    TimerList timerList_;
    int timerfd_;
    Channel channel_;
};