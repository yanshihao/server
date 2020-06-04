#include "EventLoop.h"
#include "Channel.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <chrono>
#include <thread>
// 标准输入   STDIN_FILENO
// 标准输出   STDOUT_FILENO
// 标准错误   STDERR_FILENO

int fd = STDIN_FILENO;
EventLoop* g_loop;

enum State{
    INIT, SYS,
};
void onReadCallback()
{
    static int state = INIT;
    char buf[1024];
    memset(buf,0,sizeof(buf));
    int n = ::read(fd,buf, sizeof(buf));
    if(n == -1)
    {
        perror("read");
        exit(1);
    }
    if(state == INIT && (0 == strcmp(buf, "system call\n")))
    {
        state = SYS;
        printf("enhance element \n");
    }
    else
    {
        printf("please use system call to call the menu!\n");
    }
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
    t1.join();
    return 0;
}