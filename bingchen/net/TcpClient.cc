#include "TcpClient.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "SocketOps.h"
#include "../base/logging.h"

#include <boost/bind.hpp>

using namespace bingchen;


TcpClient::TcpClient(EventLoop* loop,const InetAddr& addr)
    : loop_(loop),
      addr_(addr),
      retry_(false),
      started_(false),
      connector_(new Connector(loop,addr))
{
    connector_->setNewConnectionCb(boost::bind(&TcpClient::OnNewConnection,this,_1));
}

void TcpClient::connect() {
    LOG_TRACE;
    connector_->start();
}
    
void TcpClient::OnNewConnection(int fd) {
    if (fd == -1)
        return;

    LOG_TRACE;

    {
        InetAddr peerAddr = sockets::getLocalAddr(fd);
        ConnectionPtr conn(new TcpConnection(loop_,"",fd,peerAddr));
        conn_ = conn;

        conn->setMessageCb(messageCb_);
        conn->setConnectionCb(connCb_);
        conn->setHighWaterMarkCb(highWaterMarkCb_);
        conn->setWriteCompleteCb(writeCompleteCb_);
        conn->setCloseCb(boost::bind(&TcpClient::removeConnection,this));
        conn->setInitCb(initCb_);
        loop_->runInLoop(boost::bind(&TcpConnection::establish,conn));

    }
}
    
void TcpClient::disconnect() { 
    if (conn_) {
        conn_->shutdown();
    }
}

void TcpClient::stop() {
    connector_->stop();
}
    
void TcpClient::removeConnection() {
    conn_.reset();
    if (retry_) {
        loop_->runInLoop(boost::bind(&TcpClient::connect,this));
    }
}
