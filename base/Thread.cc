#include "Thread.h"
#include <pthread.h>
#include <cassert>
#include <cstdio>
#include <sys/types.h>
#include <sys/syscall.h>
#include "CurrentThread.h"

namespace bingchen {

namespace CurrentThread {
    __thread pid_t t_cachedTid = 0;
    __thread char t_tidString[32];
    __thread const char* t_threadName;
    void cacheTid();
    pid_t tid();

void cacheTid() {
    if (0 == t_cachedTid) {
        CurrentThread::t_cachedTid = ::syscall(SYS_gettid);
        snprintf(t_tidString,31,"%d",t_cachedTid);
    }
}
pid_t tid() {
    if (0 == t_cachedTid)
        cacheTid();
    return t_cachedTid;
}
const char* tidString() {
    return t_tidString;
}
const char* threadname() {
    return t_threadName;
}
    
};
};

using namespace bingchen;

class ThreadNameInit{
public:
    ThreadNameInit() {
        CurrentThread::t_cachedTid = 0;
        CurrentThread::t_threadName = "mainThread";
        CurrentThread::cacheTid();
    }
};
ThreadNameInit threadNameInit;



atomicInt32 Thread::numCreated_;

Thread::Thread(const Thread::ThreadFunc& func,const std::string& name) :
    func_(func),
    name_(name),
    tid_(0),
    pthreadId_(0),
    started_(false),
    joined_(false) 
{
    setDefaultName();
}

Thread::~Thread() {
    if (started_ && !joined_)
        pthread_detach(pthreadId_);
}

void Thread::setDefaultName() {
    int num = numCreated_.incrementAndGet();
    if (name_.size() != 0)
        return;
    const int nameLenth = 32;
    char name[nameLenth];
    snprintf(name,nameLenth - 1,"thread_%d",numCreated());
    name_ = name;
}

void Thread::start() {
    assert(!started_);
    started_ = true;
    pthread_create(&pthreadId_,NULL,run,this);
}

void* Thread::run(void* arg) { 
    Thread* thread = static_cast<Thread*>(arg);
    CurrentThread::cacheTid();
    CurrentThread::t_threadName = thread->name_.c_str();
    thread->tid_ = CurrentThread::t_cachedTid;

    thread->func_();
}

int Thread::join() {
    assert(false == joined_);
    assert(true == started_);
    joined_ = true;
    return pthread_join(pthreadId_,NULL);
}
