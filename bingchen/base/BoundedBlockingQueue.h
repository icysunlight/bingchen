#ifndef __BINGCHEN_BASE_BOUNDEDBLOCKINGQUEUE_
#define __BINGCHEN_BASE_BOUNDEDBLOCKINGQUEUE_
#include <boost/noncopyable.hpp>
#include <boost/circular_buffer.hpp>
#include "Condition.h"
#include "MutexLock.h"


namespace bingchen {

template<typename T>
class BoundedBlockingQueue
    : public boost::noncopyable
{
private:
    mutable MutexLock mutex_;
    Condition notEmpty_;
    Condition notFull_;
    boost::circular_buffer<T> queue_;

public:
    explicit BoundedBlockingQueue(int maxSize)
        : mutex_(),
          notEmpty_(mutex_),
          notFull_(mutex_),
          queue_(maxSize)
    {}


    void put(const T& x) {
        MutexLockGuard lock(mutex_);
        while (queue_.full()) {
           notFull_.wait(); 
        }
        notEmpty_.notify();
        queue_.push_back(x);
    }

    T take() {
        MutexLockGuard lock(mutex_);
        while (queue_.empty()) {
            notEmpty_.wait();
        }
        T x = queue_.front();
        notFull_.notify();
        return x;
    }

    bool empty() const{
        MutexLockGuard lock(mutex_);
        return queue_.empty();
    }

    bool full() const {
        MutexLockGuard lock(mutex_);
        return queue_.full();
    }


    int size() const {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }

    int capacity() const {
        MutexLockGuard lock(mutex_);
        return queue_.capacity();
    }
};
};

#endif
