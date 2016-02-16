#include "../base/logging.h"
#include "../base/CurrentThread.h"
#include "Channel.h"
#include "Poller.h"
#include "TimerQueue.h"
#include "EventLoop.h"
#include "PPoller.h"
#include "EPoller.h"

#include <sys/eventfd.h>
#include <boost/bind.hpp>

#include <signal.h>
#include <errno.h>

class IgnoreSIGPIPE {
public:
    IgnoreSIGPIPE() {
        ::signal(SIGPIPE,SIG_IGN);
    }
};
IgnoreSIGPIPE ignoreSIGPIPEInit;


using namespace bingchen;

__thread EventLoop* t_eventloop;

int createEventFd() {
    return ::eventfd(0,EFD_NONBLOCK | EFD_CLOEXEC);
}

EventLoop::EventLoop()
    : quit_(false),
      running_(false),
      threadId_(CurrentThread::tid()),
      poller_(new PPoller(this)),
      timerQueue_(this),
      wakeupFd_(createEventFd()),
      wakeupChannel_(new Channel(wakeupFd_,this)),
      runningTasks_(false)
{
    if (t_eventloop) {
        LOG_FATAL << "thread already has eventloop";
    }
    else {
        t_eventloop = this;
        LOG_TRACE << "new EventLoop";
    }
    wakeupChannel_->setReadCallback(boost::bind(&EventLoop::handleRead,this));
    wakeupChannel_->enableReading();
}

EventLoop::~EventLoop() {
    t_eventloop = NULL;
}

void EventLoop::loop() {
    assert(!running_);
    running_ = true;
    while (running_) {
        poller_->poll(-1,activeChannels_);
        for (int nChannel = 0 ; nChannel < activeChannels_.size() ; ++nChannel)
        {
            activeChannels_[nChannel]->handleEvent(); 
        }
        /*
        if (wakeupFd_ == handleRead()) {
            LOG_TRACE << "thread " << threadId_ << " is waked up"
                << "at fd: " << wakeupFd_;
        }
        */
        doPendingTasks();
    }
}

bool EventLoop::isInLoopThread() {
    return CurrentThread::tid() == threadId_;
}

void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}

void EventLoop::removeChannel(Channel* channel) {
    poller_->removeChannel(channel);
}

void EventLoop::quit() {
    quit_ = true;
    running_ = false;
    if (!isInLoopThread()) {
        wakeup();
    }
}
TimerId EventLoop::runAt(TimeStamp when,const boost::function<void ()>& cb) {
    return timerQueue_.addTimer(when,0,cb);
}
TimerId EventLoop::runAfter(int seconds,const boost::function<void ()>& cb) {
    return timerQueue_.addTimer(addTime(TimeStamp::now(),seconds),0,cb);
}
TimerId EventLoop::runEvery(int seconds,const boost::function<void ()>& cb) {
    return timerQueue_.addTimer(addTime(TimeStamp::now(),seconds),seconds,cb);
}
void EventLoop::cancelTimer(TimerId& timerId) {
    timerQueue_.cancel(timerId);
}
void EventLoop::runInLoop(const Task& task) {
    LOG_TRACE << "new task arrive at " << threadId_ << " from " <<  CurrentThread::tid();
    if (isInLoopThread() ) {
        task();
    }
    else {
        queueInLoop(task);
    }
}
void EventLoop::queueInLoop(const Task& task) {
    {
        MutexLockGuard lock(mutex_);
        pendingTasks_.push_back(task);
    } 
    if (!isInLoopThread() || runningTasks_) {
        LOG_TRACE << threadId_;
        wakeup();
    }
    LOG_TRACE << "size: " << (int)pendingTasks_.size()
              << "at thread: " << threadId_;
}
void EventLoop::wakeup() {
    uint64_t context = wakeupFd_;
    int ret = ::write(wakeupFd_,&context,sizeof(context));
    if (-1 == ret) {
        LOG_TRACE << strerror(errno);
    }
}

void EventLoop::handleRead() {
    uint64_t context = 0;
    ::read(wakeupFd_,&context,sizeof(context));
    LOG_TRACE;
}

void EventLoop::doPendingTasks() {
    assert(isInLoopThread());
    std::vector<Task> tasks_;

    {
        MutexLockGuard lock(mutex_);
        tasks_.swap(pendingTasks_);
    }

    runningTasks_ = true;
    for (int i = 0 ; i < tasks_.size() ; ++i) {
       tasks_[i](); 
    }
    runningTasks_ = false;
}

