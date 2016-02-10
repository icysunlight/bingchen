#ifndef __BINGCHEN_NET_ACCEPTOR_H_
#define __BINGCHEN_NET_ACCEPTOR_H_

#include <boost/noncopyable.hpp>

#include "Socket.h"
#include "InetAddr.h"
#include "Channel.h"

namespace bingchen {

class EventLoop;

class Acceptor 
    : boost::noncopyable
{
public:
    typedef boost::function<void (Socket)> newConnectionCb_t;

    Acceptor(EventLoop* loop,InetAddr addr);

    InetAddr getAddr() { return acceptSock_.getAddr(); }

    bool listen();
    void handleRead();
    void setNewConnectionCb(const newConnectionCb_t& cb) { newConnectionCb_ = cb; }

private:
    EventLoop* loop_;
    Socket acceptSock_;
    Channel acceptChannel_;
    bool listening_;
    newConnectionCb_t newConnectionCb_;
};

};


#endif
