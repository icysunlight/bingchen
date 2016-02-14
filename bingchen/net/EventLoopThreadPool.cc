#include "EventLoopThreadPool.h"
#include <cstdio>
#include <boost/bind.hpp>

#include "../base/logging.cc"

using namespace bingchen;

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop)
    : numThreads_(0),
      baseLoop_(baseLoop),
      next_(0),
      started_(false)
{}
    
void EventLoopThreadPool::start(const ThreadInitCb& cb) {
    assert(!started_);

    for (int i = 0 ; i < numThreads_ ; ++i) {
        char name[32];
        snprintf(name,32,"%d",i);
        threads_.push_back(new EventLoopThread(cb,name));
        EventLoop* ioLoop = threads_[i].start();
        loops_.push_back(ioLoop);
        if (cb) {
           ioLoop->runInLoop(boost::bind(cb,ioLoop)); 
        }
    }
    if (0 == numThreads_ && cb) {
        baseLoop_->runInLoop(boost::bind(cb,baseLoop_));
    }

}
    
EventLoop* EventLoopThreadPool::getNext() {
    if (numThreads_ <= 0) {
        return baseLoop_;
    }
    else {
        EventLoop* ret = loops_[next_];
        next_ = (next_ + 1) % numThreads_;
        return ret;
    }
}
