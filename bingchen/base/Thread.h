#ifndef __BINGCHEN_THREAD_H_
#define __BINGCHEN_THREAD_H_
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <pthread.h>
#include <string>
#include <sys/types.h>
#include "atomic.h"


namespace bingchen{

class Thread : public boost::noncopyable
{
public:
    typedef boost::function<void ()> ThreadFunc;
private:
    pthread_t pthreadId_;
    pid_t tid_;
    bool started_;
    bool joined_;
    ThreadFunc func_;
    std::string name_;

    static atomicInt32 numCreated_;

    void setDefaultName(); 
    static void* run(void*);

public:

    Thread(const ThreadFunc& func,const std::string& name);
    ~Thread();

    void start();
    int join();
    

    std::string name() {return name_;}
    pid_t tid() {return tid_;}
    int numCreated() {return numCreated_.get();}

};

};








#endif
