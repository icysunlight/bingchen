#include "TcpConnection.h"
#include "EventLoop.h"
#include "../base/logging.h"

#include <iostream>
#include <errno.h>

#include <boost/bind.hpp>

using namespace bingchen;

TcpConnection::TcpConnection(EventLoop* loop,std::string name,int fd,InetAddr localAddr)
    : loop_(loop),
      connSock_(fd),
      connChannel_(fd,loop),
      localAddr_(localAddr),
      peerAddr_(connSock_.getAddr()),
      name_(name)
{
    connChannel_.setReadCallback(boost::bind(&TcpConnection::handleRead,this));
}

TcpConnection::~TcpConnection() {
}

void TcpConnection::establish() {
    if (connCb_)
        connCb_(shared_from_this());

    connChannel_.enableReading();
}

void TcpConnection::handleRead() {
    char buf[65536];
    memset(buf,0,sizeof(buf));
    int ret = inBuf_.readFd(connSock_.fd());
    if (0 == ret) {
        handleClose();
    }
    else if (-1 == ret) {
        LOG_TRACE << strerror(errno);
        return;
    }
    else if (ret != 0)
        messageCb_(shared_from_this(),&inBuf_);

}

void TcpConnection::handleClose() {
    connChannel_.disableAll();
    loop_->queueInLoop(boost::bind(&TcpConnection::unregistConn,shared_from_this()));
}
    
void TcpConnection::unregistConn() {
    connChannel_.disableAll();
    //在TcpServer中反注册
    if (closeCb_) {
        closeCb_(shared_from_this());
    }
    //在EventLoop中反注册
    connChannel_.remove();
}
