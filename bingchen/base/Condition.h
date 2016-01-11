#ifndef __BINGCHEN_BASE_CONDITION_H_
#define __BINGCHEN_BASE_CONDITION_H_

#include "MutexLock.h"
#include <pthread.h>
#include <boost/noncopyable.hpp>
#include <time.h>
#include <cassert>

namespace bingchen {

class Condition : public boost::noncopyable
{
private:
    MutexLock& mutex_;
    pthread_cond_t cond_;

public:
    Condition(MutexLock& mutex)
        : mutex_(mutex)
    {
        assert(0 == pthread_cond_init(&cond_,NULL)); 
    }

    ~Condition() {
        assert(0 == pthread_cond_destroy(&cond_));
    }

    int wait() {
        MutexLock::UnAssignGuard ug(mutex_);
        return pthread_cond_wait(&cond_,mutex_.getPthreadMutex());
    }

    int notify() {
        pthread_cond_signal(&cond_);
    }

    int notifyAll() {
        pthread_cond_broadcast(&cond_);
    }

    int timedWait(int seconds) {
        timespec timeToWait;
        timeToWait.tv_sec = seconds;
        timeToWait.tv_nsec = 0;
        MutexLock::UnAssignGuard ug(mutex_);
        pthread_cond_timedwait(&cond_,mutex_.getPthreadMutex(),&timeToWait);
    }

};
};

#endif
