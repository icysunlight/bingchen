#ifndef __BINGCHEN_NET_CONNECTOR_H_
#define __BINGCHEN_NET_CONNECTOR_H_

#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

#include "InetAddr.h"
#include "TimerId.h"

namespace bingchen {

class EventLoop;
class Channel;

class Connector
    : boost::noncopyable
{
public:
    enum State {connecting,connected,disconnected};
    typedef boost::function<void (int)> NewConnectionCb;
    Connector(EventLoop* loop,const InetAddr& addr);

    void start();
    void restart();
    void stop();
    void setNewConnectionCb(const NewConnectionCb& cb) { newConnectionCb_ = cb; }
    
private:
    void connect();
    void registConnect();
    void unregistConnect();
    void resetChannel();
    void retry();
    void stopInLoop();

    void handleWrite();
    void handleError();

    EventLoop* loop_;
    const InetAddr addr_;
    int fd_;
    boost::scoped_ptr<Channel> channel_; 
    NewConnectionCb newConnectionCb_;

    bool start_;
    int waitTime_;
    TimerId nextTimer_;
    State state_;
};
};


#endif
