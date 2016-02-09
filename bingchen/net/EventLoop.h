#ifndef __BINGCHEN_NET_EVENTLOOP_H_
#define __BINGCHEN_NET_EVENTLOOP_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/function.hpp>
#include <vector>
#include <pthread.h>
#include "TimerQueue.h"
#include "../base/MutexLock.h"


namespace bingchen {

class Channel;
class Poller;
class TimerId;

class EventLoop
    : boost::noncopyable
{
public:
    typedef boost::function<void ()> timerCallback;
    typedef boost::function<void ()> Task;
    
    EventLoop();
    ~EventLoop();

    void loop();
    bool isInLoopThread();
    void updateChannel(Channel*);
    void quit();
    static void getThreadEventLoop();

    TimerId runAt(TimeStamp when,const timerCallback& cb);
    TimerId runAfter(int seconds,const timerCallback& cb);
    TimerId runEvery(int seconds,const timerCallback& cb);
    void cancelTimer(TimerId& timerId);

    void runInLoop(const Task& task);
    void queueInLoop(const Task& task);
    void wakeup();
    void handleRead();
    void doPendingTasks();

private:

    pid_t threadId_;
    bool running_;
    boost::scoped_ptr<Poller> poller_;
    std::vector<Channel*> activeChannels_;
    bool quit_;
    TimerQueue timerQueue_;

    int wakeupFd_;
    boost::scoped_ptr<Channel> wakeupChannel_;
    std::vector<Task> pendingTasks_;
    MutexLock mutex_;
    bool runningTasks_;
};

};

#endif
