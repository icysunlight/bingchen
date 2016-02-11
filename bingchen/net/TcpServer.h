#ifndef __BINGCHEN_NET_TCPSERVER_H_
#define __BINGCHEN_NET_TCPSERVER_H_

#include <boost/scoped_ptr.hpp>

#include <map>
#include <string>

#include "NetTypes.h"
#include "InetAddr.h"
#include "Socket.h"
#include "Acceptor.h"

namespace bingchen {

class EventLoop;

class TcpServer {
public:
    typedef std::map<std::string,ConnectionPtr> ConnectionList_t;

    TcpServer(EventLoop* loop,InetAddr addr);

    void start();
    void OnConnection(int peerfd);
    void removeConnection(const ConnectionPtr& conn);

    void setMessageCb(const MessageCb_t& cb) { messageCb_ = cb; }
    void setConnectionCb(const ConnectionCb_t& cb) { connCb_ = cb; }


private:
    EventLoop* loop_;
    boost::scoped_ptr<Acceptor> acceptor_;
    ConnectionList_t connList_;
    MessageCb_t messageCb_;
    ConnectionCb_t connCb_;
    InetAddr localAddr_;

    int connIndex_;
};

};

#endif
