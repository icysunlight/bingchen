#ifndef __BINGCHEN_NET_TCPCONNECTION_H_
#define __BINGCHEN_NET_TCPCONNECTION_H_

#include "Channel.h"
#include "NetTypes.h"
#include "InetAddr.h"
#include "Socket.h"
#include "Buffer.h"
#include <string>

#include <boost/enable_shared_from_this.hpp>

namespace bingchen {

class EventLoop;

class TcpConnection
    : boost::noncopyable,
      public boost::enable_shared_from_this<TcpConnection>
{
public:
    enum stateE{Connecting,Connected,Disconnecting,Disconnected};

    TcpConnection(EventLoop* loop,std::string name,int peerfd,InetAddr localAddr);
    ~TcpConnection();
    void establish();

    void setInitCb(const ConnectionCb_t& cb) { initCb_ = cb; }
    void setMessageCb(const MessageCb_t& cb) {messageCb_ = cb;}
    void setConnectionCb(const ConnectionCb_t& cb) { connCb_ = cb;}
    void setWriteCompleteCb(const ConnectionCb_t& cb) { writeCompleteCb_ = cb; }
    void setHighWaterMarkCb(const ConnectionCb_t& cb) { highWaterMarkCb_ = cb; }
    void setCloseCb(const ConnectionCb_t& cb) { closeCb_ = cb; }

    void handleRead();
    void handleClose();
    void handleWrite();
    void unregistConn();

    void setTcpNodelay(bool on) { connSock_.setNodelay(on);}
    void setTcpKeepAlive(bool on) { connSock_.setKeepAlive(on); }

    InetAddr getLocalAddr() { return localAddr_; }
    InetAddr getPeerAddr() { return peerAddr_; }

    std::string getName() { return name_; }

    void send(const std::string& content);
    void sendInLoop(const std::string& content);

    void shutdown();
    void shutdownInLoop();

private:
    EventLoop* loop_;
    Socket connSock_;
    Channel connChannel_;
    ConnectionCb_t connCb_;
    ConnectionCb_t closeCb_;
    ConnectionCb_t writeCompleteCb_;
    ConnectionCb_t highWaterMarkCb_;
    ConnectionCb_t initCb_;
    MessageCb_t messageCb_;
    InetAddr localAddr_;
    InetAddr peerAddr_;

    Buffer inBuf_;
    Buffer outputBuffer_;

    stateE state_;

    std::string name_;

    int highWaterMark_;
};


};

#endif
