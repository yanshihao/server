#include "EventLoop.h"
#include "Channel.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <thread>
#include "Timestamp.h"
// 标准输入   STDIN_FILENO
// 标准输出   STDOUT_FILENO
// 标准错误   STDERR_FILENO

int fd = STDIN_FILENO;
EventLoop* g_loop;

void func()
{
    std::cout << "this is time clock  " << Timestamp::now().toFormattedString() << std::endl;
}

void onReadCallback()
{    
    char buf[1024];
    memset(buf,0,sizeof(buf));
    int n = ::read(fd,buf, sizeof(buf));
    std::cout << buf << Timestamp::now().toFormattedString()<< std::endl;
    g_loop->runAfter(3,func);
    g_loop->quit();
}

void stop()
{
    std::this_thread::sleep_for(std::chrono::seconds(20));
    g_loop->quit();
}

int main()
{
    std::thread t1(stop);
    EventLoop loop;
    g_loop = &loop;
    Channel channel(&loop, fd);
    channel.setReadCallback(onReadCallback);
    channel.setReadable();
    loop.loop();
    std::cout << "heheda" << std::endl;
    t1.join();
    return 0;
}