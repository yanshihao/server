#include "EventLoop.h"
#include <thread>
#include <iostream>
#include <chrono>
EventLoop* g_loop;

void callback1()
{
    std::cout << "callback 1" << std::endl;
}
void callback2()
{
    std::cout << "callback 2" << std::endl;
}
void func()
{
    g_loop->runAfter(3, callback1);
    g_loop->runEvery(2, callback2);
    g_loop->runAfter(5, callback1);
    std::this_thread::sleep_for(std::chrono::seconds(15));
    g_loop->quit();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;

    std::thread t1(func);
    loop.loop();
    t1.join();
    return 0;
}