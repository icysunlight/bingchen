#ifndef __BINGCHEN_NET_TCPCONNECTION_H_
#define __BINGCHEN_NET_TCPCONNECTION_H_

#include "Channel.h"
#include "NetTypes.h"
#include "InetAddr.h"
#include "Socket.h"
#include <string>

#include <boost/enable_shared_from_this.hpp>

namespace bingchen {

class EventLoop;

class TcpConnection
    : boost::noncopyable,
      public boost::enable_shared_from_this<TcpConnection>
{
public:
    TcpConnection(EventLoop* loop,std::string name,Socket connSock,InetAddr localAddr,InetAddr peerAddr);
    ~TcpConnection();
    void establish();

    void setMessageCb(MessageCb_t cb) {messageCb_ = cb;}
    void setConnectionCb(ConnectionCb_t cb) { connCb_ = cb;}

    void handleRead();

    InetAddr getLocalAddr() { return localAddr_; }
    InetAddr getPeerAddr() { return peerAddr_; }

    std::string getName() { return name_; }

private:
    EventLoop* loop_;
    Socket connSock_;
    Channel connChannel_;
    ConnectionCb_t connCb_;
    MessageCb_t messageCb_;
    InetAddr localAddr_;
    InetAddr peerAddr_;

    std::string name_;
};


};

#endif
