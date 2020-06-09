// 测试 Acceptor
#include "Acceptor.h"
#include "EventLoop.h"
#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>

void func(int fd, InetAddr peerAddr)
{
    std::cout << peerAddr.to_string() << std::endl;
    ::close(fd);
}
EventLoop* g_loop;
void threadFunc()
{
    std::this_thread::sleep_for(std::chrono::seconds(20));
    g_loop->quit();
}

int main()
{
    EventLoop loop;
    g_loop = &loop;
    std::thread t1(threadFunc);
    InetAddr localAddr(6666);
    Acceptor acceptor(&loop, localAddr);
    acceptor.setAccptorCallback(func);
    acceptor.start();
    loop.loop();
    t1.join();
    return 0;
}