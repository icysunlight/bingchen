#ifndef __BINGCHEN_BASE_BLOCKINGQUEUE_H_
#define __BINGCHEN_BASE_BLOCKINGQUEUE_H_

#include <boost/noncopyable.hpp>
#include <queue>
#include "MutexLock.h"
#include "Condition.h"

namespace bingchen {

template<typename T>
class BlockingQueue 
    : public boost::noncopyable
{
private:
    MutexLock mutex_;
    Condition notEmpty_;
    std::deque<T> que_;

public:
    BlockingQueue()
        : mutex_(),
          notEmpty_(mutex_),
          que_()
    {}

    int size() {
        MutexLockGuard(mutex_);
        return que_.size();
    }

    void put(T x) {
        MutexLockGuard lock(mutex_);
        que_.push_back(x);
    }

    T take() {
        MutexLockGuard lock(mutex_);
        while (que_.empty()) {
            notEmpty_.wait();
        }
        T front = que_.front();
        que_.pop_front();
        return front; 
    }

};
};













#endif
