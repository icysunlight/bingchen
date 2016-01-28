#include "../base/logging.h"
#include "../base/CurrentThread.h"
#include "Channel.h"
#include "Poller.h"
#include "EventLoop.h"


using namespace bingchen;

__thread EventLoop* t_eventloop;

EventLoop::EventLoop()
    : quit_(false),
      running_(false),
      threadId_(CurrentThread::tid()),
      poller_(new Poller(this))
{
    if (t_eventloop) {
        LOG_FATAL << "thread already has eventloop";
    }
    else {
        t_eventloop = this;
        LOG_TRACE << "new EventLoop";
    }
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
    }
}

bool EventLoop::isInLoopThread() {
    return CurrentThread::tid() == threadId_;
}

void EventLoop::updateChannel(Channel* channel) {
    poller_->updateChannel(channel);
}

void EventLoop::quit() {
    quit_ = true;
    running_ = false;
}
