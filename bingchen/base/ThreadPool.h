#ifndef __BINGCHEN_BASE_THREADPOOL_
#define __BINGCHEN_BASE_THREADPOOL_
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>
#include <boost/ptr_container/ptr_container.hpp>
#include <string>
#include <queue>
#include "Condition.h"
#include "MutexLock.h"
#include "Thread.h"

using std::string;


namespace bingchen {

class ThreadPool
    : public boost::noncopyable
{
public:
    typedef boost::function<void ()> Task;
private:
    std::string name_;
    MutexLock mutex_;
    Condition notFull_;
    Condition notEmpty_;
    std::queue<Task> queue_;
    int maxQueueSize_;

    boost::ptr_vector<Thread> threads_;

    bool running_;

public:
    ThreadPool(const string& name = "ThreadPool") 
        : name_(name),
          mutex_(),
          notFull_(mutex_),
          notEmpty_(mutex_),
          running_(false),
          maxQueueSize_(0)
          {}

    ~ThreadPool();

    void setMaxQueueSize(int maxSize);
    bool full();
    bool notEmpty();
    Task take();
    void put(const Task& task);

    void start(int numThreads);
    void stop();
    void runInThread();



};
};







#endif

