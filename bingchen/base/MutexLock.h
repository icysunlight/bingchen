#ifndef __BINGCHEN_BASE_MUTEXLOCK_H_
#define __BINGCHEN_BASE_MUTEXLOCK_H_

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include "CurrentThread.h"
#include <cassert>

namespace bingchen {

class MutexLock : public boost::noncopyable
{
private:
    pthread_mutex_t mutex_;
    pid_t holder_;

    friend class Condition;

    class UnAssignGuard 
    {
    public:
        UnAssignGuard(MutexLock& mutexlock)
            : mutexlock_(mutexlock)
        {
            mutexlock_.unAssignHolder(); 
        }
        ~UnAssignGuard() {
            mutexlock_.assignHolder();
        }

    private:
        MutexLock& mutexlock_;
        
    };

    void assignHolder() {
        holder_ = CurrentThread::tid();
    }
    void unAssignHolder() {
        holder_ = 0;
    }


public:
    MutexLock() {
        holder_ = 0;
        assert(0 == pthread_mutex_init(&mutex_,NULL));
    }

    ~MutexLock() {
        assert(0 == holder_);
        assert(0 == pthread_mutex_destroy(&mutex_));
    }

    void lock() {
        pthread_mutex_lock(&mutex_);
        holder_ = CurrentThread::tid();
    }

    void unlock() {
        pthread_mutex_unlock(&mutex_);
        holder_ = 0;
    }

    bool isLocked() {
        return holder_ != 0;
    }

    pthread_mutex_t* getPthreadMutex() {
        return &mutex_;
    }
};

class MutexLockGuard : public boost::noncopyable
{
private:
    MutexLock& mutexLock_;

public:
    MutexLockGuard(MutexLock& mutexlock) 
        : mutexLock_(mutexlock) 
    {
        mutexLock_.lock(); 
    }

    ~MutexLockGuard(){
        mutexLock_.unlock();
    }
};


};

#endif
