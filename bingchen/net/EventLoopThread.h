#ifndef __BINGCHEN_EVENTLOOPTHREAD_H_
#define __BINGCHEN_EVENTLOOPTHREAD_H_

#include <boost/noncopyable.hpp>
#include <string>

#include "../base/MutexLock.h"
#include "../base/Condition.h"
#include "../base/Thread.h"

namespace bingchen {

class EventLoop;

class EventLoopThread
    : boost::noncopyable
{
public:
    typedef boost::function<void (EventLoop*)> initCallback; 

    EventLoopThread(const initCallback& cb,const std::string name);
    ~EventLoopThread();

    EventLoop* start();

private:
    void ThreadFunc();

    initCallback initcb_;
    MutexLock mutex_;
    Condition cond_;
    Thread thread_;
    EventLoop* loop_;

};
};


#endif
