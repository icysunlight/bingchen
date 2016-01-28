#include "Channel.h"
#include "EventLoop.h"
#include <poll.h>

using namespace bingchen;

Channel::Channel(int fd,EventLoop* loop)
    : fd_(fd),
      loop_(loop),
      events_(0),
      revents_(0),
      index_(-1)
{}

void Channel::handleEvent() {
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
}
void Channel::update() { 
    loop_->updateChannel(this);
}

//FIXME: enableReading应该在Poller类中调用
void Channel::enableReading() {
    events_ |= POLLIN;
    update();
}
