#include "EventLoop.h"
#include <thread>
#include <iostream>
#include <chrono>
#include "Timestamp.h"
EventLoop* g_loop;

void callback1()
{
    std::cout << "callback 1:    " << Timestamp::now().toFormattedString() << std::endl;
    g_loop->runAfter(5, callback1);
}
void callback2()
{
    std::cout << "callback 2:    " << Timestamp::now().toFormattedString() << std::endl;
}


void func()
{
    g_loop->runEvery(3, 2, callback2);
    g_loop->runAfter(5, callback1);
    std::this_thread::sleep_for(std::chrono::seconds(50));
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