#include "EventLoop.h"
#include <thread>
#include <iostream>

// 测试两个跨线程调用的函数

void task( int i)
{
    std::cout << "this is task: time " << i <<std::endl;
}

EventLoop* gloop;

void threadFunc()
{
    for(int i = 0; i < 3; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(3));
        gloop->queueInLoop(
            std::bind(task, i)
        );
    }
    gloop->quit();
}

int main()
{
    EventLoop loop;
    gloop = &loop;
    std::thread t1(threadFunc);
    loop.loop();
    t1.join();
}