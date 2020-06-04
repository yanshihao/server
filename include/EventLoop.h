#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <memory>
#include <mutex>
class Epoll;
class Channel;
typedef std::function<void()> Task;

// EventLoop在每一个事件循环线程都有且只有一个实例
// 通过线程全局对象可以实现一个线程只有一个

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    // 主循环
    void loop();
    // 退出函数可以在其他线程运行
    void quit();

    // 插入任务
    void runInLoop(const Task& task);

    // 此函数需要线程安全，需要在多个线程运行的函数
    void queueInLoop(const Task& task);
    
    // 判断是否在此线程
    bool inThisThread();
    void assertInThisThread();

    // 提供通道更新和通道注销
    void updateChannel(Channel* channel);
    void deleteChannel(Channel* channel);

private:

    // 执行插入任务
    void doPendingWorks();

    // 线程ID
    std::thread::id threadId_;
  
    // 每个EventLoop拥有一个epoll，且不转让其所有权
    std::unique_ptr<Epoll> epoll_;
    
    // 保护 pendingWorks_ 的访问
    std::mutex mutex_;
    
    // 插入任务与运行状态
    std::vector<Task> pendingWorks_;
    bool callingPendingFunctors_;

    bool loop_;
    bool quit_;
};