#include "EventLoopThreadPool.h"
#include "EventLoop.h"
#include <iostream>

EventLoopThreadPool* gpool = nullptr;
int times = 0;
void func()
{
    for(int i = 0; i < 4; i++)
    {
        EventLoop* tloop = gpool->getNextLoop();
        std::cout << tloop << std::endl;
        tloop->runInLoop(            
           std::bind([](int times)
            {
                printf("haha%d\n",times);
            },times)
        );
    }
    times ++;
}

int main()
{
    EventLoop Loop;
    EventLoopThreadPool threadPool(&Loop);
    gpool = &threadPool;
    threadPool.setThreadNumber(4);
    threadPool.start();
    Loop.runEvery(1,2,func);
    Loop.runAfter(30,
        [&Loop]()
        {
            Loop.quit();
        }
    );
    Loop.loop();
    return 0;
}