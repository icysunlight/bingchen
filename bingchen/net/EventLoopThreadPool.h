#ifndef __BINGCHEN_NET_EVENTLOOPTHREADPOOL_H_
#define __BINGCHEN_NET_EVENTLOOPTHREADPOOL_H_

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include "EventLoop.h"
#include "EventLoopThread.h"

namespace bingchen {

class EventLoopThreadPool 
    : boost::noncopyable
{
public:
    typedef boost::function<void(EventLoop*)> ThreadInitCb;
    EventLoopThreadPool(EventLoop* baseLoop);
    
    void start(const ThreadInitCb& cb);
    void setThreadsNum(int num) { numThreads_ = num; }
    EventLoop* getNext(); 

private:
    int numThreads_;
    int next_;
    bool started_;
    EventLoop* baseLoop_;
    boost::ptr_vector<EventLoopThread> threads_;
    std::vector<EventLoop*> loops_;

};

};

#endif
