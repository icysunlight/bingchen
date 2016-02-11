#include "Channel.h"
#include "EventLoop.h"
#include <poll.h>

using namespace bingchen;

Channel::Channel(int fd,EventLoop* loop)
    : fd_(fd),
      loop_(loop),
      events_(0),
      revents_(0),
      index_(-1),
      tied_(false),
      handlingEvents_(false)
{}

Channel::~Channel() {
    assert(!handlingEvents_);
}

void Channel::handleEvent() {
    boost::shared_ptr<void> guard;
    if (tied_) {
        guard = tie_.lock();
        if (guard) {
            handleEventWithGuard();
        }
    }
    else {
        handleEventWithGuard();
    }
}

void Channel::handleEventWithGuard() {

    handlingEvents_ = true;

    if (revents_ & (POLLIN | POLLPRI | POLLRDHUP))
    {
        if (readCallback_) {
            readCallback_();
        } 
    }
    if (revents_ & (POLLOUT))
    {
        if (writeCallback_) {
            writeCallback_();
        } 
    }
    if (revents_ & (POLLERR | POLLNVAL))
    {
        if (errorCallback_) {
            errorCallback_();
        } 
    }

    handlingEvents_ = false;
}
void Channel::update() { 
    loop_->updateChannel(this);
}

void Channel::remove() {
    loop_->removeChannel(this);
}

//FIXME: enableReading应该在Poller类中调用
void Channel::enableReading() {
    events_ |= POLLIN;
    update();
}
void Channel::disableReading() {
    events_ &= ~POLLIN;
    update();
}

void Channel::disableAll() {
    events_ = 0;
}

void Channel::tie(const boost::shared_ptr<void>& obj) {
    tied_ = true;
    tie_ = obj;
}

