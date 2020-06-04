#include "EventLoop.h"
#include <thread>
#include <chrono>
EventLoop* g_loop;

void func(int i)
{
    printf("this is thread func :times %d\n", i);
}

void threadfunc()
{
    for(int i = 0; i < 5; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        printf("this is thread func :times %d\n", i);
        g_loop->queueInLoop(
            std::bind(func, i)
        );
    }
    printf("i will quit this loop\n");
    g_loop->quit();
}


int main()
{
    EventLoop loop;
    g_loop = &loop;
    std::thread t1(threadfunc);

    loop.loop();

    t1.join();
    return 0;
}