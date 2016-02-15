#include "TimerQueue.h"
#include "TimerId.h"
#include "EventLoop.h"
#include "../base/logging.h"
#include <sys/timerfd.h>
#include <boost/bind.hpp>
#include <algorithm>
#include <cstdint>


using namespace bingchen;


int createTimerfd()
{
    return timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK | TFD_CLOEXEC);
}

void setTimerfd(TimeStamp newExpiration,int fd) {
    struct itimerspec new_value;
    struct itimerspec old_value;
    memset(&new_value,0,sizeof(new_value));
    int diff = newExpiration.microSecondsSinceEpoc() - TimeStamp::now().microSecondsSinceEpoc();
    new_value.it_value.tv_sec = diff / TimeStamp::kMicroSecondsPerSecond;
    new_value.it_value.tv_nsec = diff % TimeStamp::kMicroSecondsPerSecond * 1000;

    timerfd_settime(fd,0,&new_value,&old_value); 
}

uint64_t readTimerfd(int fd) {
    uint64_t howmany;
    read(fd,&howmany,sizeof(howmany));
    return howmany;
}


TimerQueue::TimerQueue(EventLoop* loop)
    : loop_(loop),
      timerfd_(createTimerfd()),
      channel_(timerfd_,loop),
      expiration_(TimeStamp::invalid()),
      callingTimers_(false)
{
    channel_.setReadCallback(boost::bind(&TimerQueue::handleRead,this));
    channel_.enableReading();
}

TimerId TimerQueue::addTimer(TimeStamp expiration,double interval,boost::function<void ()> cb) {
    Timer* timer = new Timer(expiration,interval,cb);
    loop_->runInLoop(boost::bind(&TimerQueue::addTimerInThread,this,timer));
    return TimerId(timer);
}

void TimerQueue::addTimerInThread(Timer* timer) {
    activeTimers_.insert(std::make_pair(timer->expiration(),timer));
    reset();
}

void TimerQueue::reset() {
    if (activeTimers_.empty() ) {
        expiration_ = TimeStamp::invalid();
        channel_.disableReading();
        return;
    }
    else if (activeTimers_.begin()->first == expiration_) {
        return;
    }
    else {
        expiration_ = activeTimers_.begin()->first;
        setTimerfd(expiration_,timerfd_);
    }
    if (activeTimers_.size() == 1) {
        channel_.enableReading();
    }
}

void TimerQueue::handleRead() {
    {
        std::vector<Entry> expiration;
        Entry entry = std::make_pair(TimeStamp::now(),reinterpret_cast<Timer*>(UINTPTR_MAX)); 

        readTimerfd(timerfd_);

        std::set<Entry>::iterator it = lower_bound(activeTimers_.begin(),activeTimers_.end(),entry);
        std::copy(activeTimers_.begin(),it,back_inserter(expiration));
        activeTimers_.erase(activeTimers_.begin(),it);
    
        callingTimers_ = true;
        cancelingTimers_.clear();
        for (std::vector<Entry>::iterator it = expiration.begin() ; it != expiration.end() ; it++) {
            it->second->run();
        }
        callingTimers_ = false;

        for (std::vector<Entry>::iterator it = expiration.begin() ; it != expiration.end() ; it++) {
            if (it->second->repeat() && cancelingTimers_.find(entry) != cancelingTimers_.end()) {
                LOG_TRACE;
                it->second->restart();
                activeTimers_.insert(std::make_pair(it->second->expiration(),it->second));
            }
            else {
                LOG_TRACE;
                delete it->second;
            }
        }

    }

    reset();
}

void TimerQueue::cancel(TimerId id) {
    loop_->runInLoop(boost::bind(&TimerQueue::cancelInLoop,this,id));
}

void TimerQueue::cancelInLoop(TimerId id) {
    Entry entry = std::make_pair(id.timer_->expiration(),id.timer_);
    std::set<Entry>::iterator it = activeTimers_.find(entry);
    if (it != activeTimers_.end()) {
        delete it->second;
        activeTimers_.erase(it);
        reset();
        LOG_TRACE << "delete a Timer";
    }
    else if (callingTimers_) {
        cancelingTimers_.insert(entry);
        LOG_TRACE << "delete a expired Timer";
    }
}
