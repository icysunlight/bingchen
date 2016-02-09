#include "EventLoopThread.h"
#include "EventLoop.h"

#include <boost/bind.hpp>

using namespace bingchen;

EventLoopThread::EventLoopThread(const initCallback& cb,const std::string name)
    : initcb_(cb),
      mutex_(),
      cond_(mutex_), 
      thread_(boost::bind(&EventLoopThread::ThreadFunc,this),name)
{}

EventLoopThread::~EventLoopThread() {
    if (loop_) {
        loop_->quit();
        thread_.join();
    }
}

EventLoop* EventLoopThread::start() {
    thread_.start();

    {
        MutexLockGuard lock(mutex_);
        while (NULL == loop_) {
            cond_.wait();
        }
    }
    //FIXME:线程退出后此指针失效，需要用weak_ptr来保存
    return loop_;
}

void EventLoopThread::ThreadFunc() {
    EventLoop loop;

    if (initcb_) {
        initcb_(&loop);
    }

    loop_ = &loop;
    cond_.notify();
    
    loop.loop();

    loop_ = NULL;
}
