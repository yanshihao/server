#include "EventLoop.h"
#include <thread>
#include <iostream>

// 测试不能跨线程调用的函数
// 会在断言处失败

EventLoop* gloop;

void threadFunc()
{   
    gloop->loop();
}

int main()
{
    EventLoop loop;
    gloop = &loop;
    std::thread t1(threadFunc);   
    t1.join();
}