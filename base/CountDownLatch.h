#ifndef __BINGCHEN_BASE_COUNTDOWNLATCH_H_
#define __BINGCHEN_BASE_COUNTDOWNLATCH_H_

#include <boost/noncopyable.hpp>
#include "MutexLock.h"
#include "Condition.h"

namespace bingchen {

class CountDownLatch
    : boost::noncopyable
{
private:
    MutexLock mutexcond_;
    mutable MutexLock mutex_;
    Condition cond_;
    int count_;

public:
    explicit CountDownLatch(int count)
        :   mutex_(),
            mutexcond_(),
            cond_(mutexcond_), 
            count_(count)
    {}

    void wait() {
        MutexLockGuard lock(mutexcond_);
        while (count_ > 0) {
            cond_.wait();
        }
    }
    
    void CountDown() {
        MutexLockGuard lock(mutex_);
        count_--;
        if (0 == count_) {
            cond_.notifyAll();
        }
    }

    int getCount() const {
        MutexLockGuard lock(mutex_);
        return count_;
    }

};
};

#endif
