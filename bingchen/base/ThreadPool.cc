#include <cassert>
#include <cstdio>
#include <boost/bind.hpp>
#include "ThreadPool.h"
#include "Thread.h"
#include "MutexLock.h"

using namespace bingchen;

ThreadPool::~ThreadPool(){
    if (running_)
        stop();
}


void ThreadPool::setMaxQueueSize(int maxSize) {
    assert(!running_);
    MutexLockGuard lock(mutex_);
    maxQueueSize_ = maxSize;
}

bool ThreadPool::full() {
    assert(mutex_.isLocked());
    return maxQueueSize_ != 0 && (queue_.size() == maxQueueSize_);
}

bool ThreadPool::notEmpty() {
    assert(mutex_.isLocked());
    return queue_.size();
}

ThreadPool::Task ThreadPool::take() {
    MutexLockGuard lock(mutex_);
    while (!notEmpty()) {
        notEmpty_.wait();
    }
    assert(notEmpty());

    Task task = queue_.front();
    queue_.pop();
    notFull_.notify();
    return task;
}

void ThreadPool::put(const Task& task) {
    MutexLockGuard lock(mutex_);
    while (full()) {
        notFull_.wait(); 
    }
    assert(!full());

    queue_.push(task);
    notEmpty_.notify();
}

void ThreadPool::start(int numThreads) {
    assert(running_ == false);
    {
        MutexLockGuard lock(mutex_);
        running_ = true;

        for (int i = 0 ; i < numThreads ; ++i) {
            char name[32];
            snprintf(name,31,"ThreadPool%d",i);
            threads_.push_back(new Thread(boost::bind(&bingchen::ThreadPool::runInThread,this),name));
        }
    }

    for (int i = 0 ; i < numThreads ; ++i) {
        threads_[i].start();
    }
}

void ThreadPool::stop() {
    assert(running_);

    {
        MutexLockGuard lock(mutex_);
        running_ = false;    
        notEmpty_.notifyAll();
    }
    for_each(threads_.begin(),threads_.end(),boost::bind(&bingchen::Thread::join,_1));
}

void ThreadPool::runInThread() {
    
    while (running_) {
        {
            MutexLockGuard lock(mutex_);
            while (running_ && !notEmpty() ) {
                notEmpty_.wait();
            }
        }

        if (!running_) {
            return;
        }

        Task task = take();
        if (task) {
            task();
        }
    }
}

