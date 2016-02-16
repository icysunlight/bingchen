#ifndef __BINGCHEN_NET_TCPCLIENT_H_
#define __BINGCHEN_NET_TCPCLIENT_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "NetTypes.h"
#include "InetAddr.h"
#include "Connector.h"


namespace bingchen {

class EventLoop;

class TcpClient
    : boost::noncopyable
{
public:
    TcpClient(EventLoop* loop,const InetAddr& addr);


    void connect();
    void disconnect();
    void stop();

    bool retry() { return retry_; }
    void enableRetry() { retry_ = true; }

    void removeConnection(const ConnectionPtr& conn);

    void setMessageCb(const MessageCb_t& cb) { messageCb_ = cb; }
    void setConnectionCb(const ConnectionCb_t& cb) { connCb_ = cb; }
    void setWriteCompleteCb(const ConnectionCb_t& cb) { writeCompleteCb_ = cb; }
    void setHighWaterMarkCb(const ConnectionCb_t& cb) { highWaterMarkCb_ = cb; }
    void setInitCb(const ConnectionCb_t& cb) { initCb_ = cb; }

private:
    void OnNewConnection(int peerfd);
    void removeConnection();

    EventLoop* loop_;
    InetAddr addr_;
    boost::scoped_ptr<Connector> connector_;
    ConnectionPtr conn_;

    MessageCb_t messageCb_;
    ConnectionCb_t connCb_;
    ConnectionCb_t writeCompleteCb_;
    ConnectionCb_t highWaterMarkCb_;
    ConnectionCb_t initCb_;

    bool started_;
    bool retry_;
    TimerId nextTimer_;
};
};


#endif
