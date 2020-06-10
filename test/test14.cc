#include "EventLoop.h"
#include "EventLoopThread.h"
#include <stdio.h>

void fun1()
{
    printf("heheda\n");
}

void fun2(EventLoop* loop)
{
    loop->quit();
}

int main()
{
    EventLoopThread threadLoop;
    EventLoop* loop = threadLoop.start();
    loop->runEvery(1,1,fun1);
    loop->runAfter(10,std::bind(fun2,loop));
    return 0;
}