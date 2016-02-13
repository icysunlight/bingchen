#ifndef __BINGCHEN_NET_TCPSERVER_H_
#define __BINGCHEN_NET_TCPSERVER_H_

#include <boost/scoped_ptr.hpp>

#include <map>
#include <string>

#include "NetTypes.h"
#include "InetAddr.h"
#include "Socket.h"
#include "Acceptor.h"
#include "EventLoopThreadPool.h"

namespace bingchen {

class EventLoop;

class TcpServer {
public:
    typedef std::map<std::string,ConnectionPtr> ConnectionList_t;
    typedef boost::function<void (EventLoop*)> IOLoopInitCb;

    TcpServer(EventLoop* loop,InetAddr addr);

    void setThreadsNum(int num) { threadPool_->setThreadsNum(num); }
    void start();
    void OnConnection(int peerfd);
    void removeConnection(const ConnectionPtr& conn);
    void removeConnectionGuard(const ConnectionPtr& conn);

    void setMessageCb(const MessageCb_t& cb) { messageCb_ = cb; }
    void setConnectionCb(const ConnectionCb_t& cb) { connCb_ = cb; }
    void setWriteCompleteCb(const ConnectionCb_t& cb) { writeCompleteCb_ = cb; }
    void setHighWaterMarkCb(const ConnectionCb_t& cb) { highWaterMarkCb_ = cb; }
    void setIOLoopInitCb(const IOLoopInitCb& cb) { ioLoopInitCb_ = cb; }


private:
    EventLoop* loop_;
    boost::scoped_ptr<Acceptor> acceptor_;
    boost::scoped_ptr<EventLoopThreadPool> threadPool_;
    IOLoopInitCb ioLoopInitCb_;
    ConnectionList_t connList_;
    MessageCb_t messageCb_;
    ConnectionCb_t connCb_;
    ConnectionCb_t writeCompleteCb_;
    ConnectionCb_t highWaterMarkCb_;
    InetAddr localAddr_;

    int connIndex_;

    bool started_;
};

};

#endif
