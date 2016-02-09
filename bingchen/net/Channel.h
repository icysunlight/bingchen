#ifndef __BINGCHEN_NET_CHANNEL_H_
#define __BINGCHEN_NET_CHANNEL_H_

#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

namespace bingchen{

class EventLoop;

class Channel
    : boost::noncopyable
{
public:
    typedef boost::function<void ()> EventCallback;

    Channel(int fd,EventLoop* loop_);

    void setReadCallback(const EventCallback& readCallback) { readCallback_ = readCallback;}
    void setWriteCallback(const EventCallback& writeCallback) { writeCallback_ = writeCallback;}
    void setErrorCallback(const EventCallback& errorCallback) { errorCallback_ = errorCallback;}

    void set_revents(int revents) { revents_ = revents;}
    int events() { return events_;}
    int fd() const { return fd_;}
    void update();
    void handleEvent();
    
    void enableReading();
    void disableReading();

    void set_index(int index) { index_ = index; }
    int index() { return index_;}

private:
    const int fd_;
    EventLoop* loop_;
    int events_;
    int revents_;
    int index_;

    EventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;



};


};

#endif
