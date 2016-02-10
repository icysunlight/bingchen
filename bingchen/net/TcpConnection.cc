#include "TcpConnection.h"
#include "EventLoop.h"
#include "../base/logging.h"

#include <iostream>
#include <errno.h>

#include <boost/bind.hpp>

using namespace bingchen;

TcpConnection::TcpConnection(EventLoop* loop,std::string name,Socket connSock,InetAddr localAddr,InetAddr peerAddr)
    : loop_(loop),
      connSock_(connSock),
      connChannel_(connSock.fd(),loop),
      localAddr_(localAddr),
      peerAddr_(peerAddr),
      name_(name)
{
    connChannel_.setReadCallback(boost::bind(&TcpConnection::handleRead,this));
}

TcpConnection::~TcpConnection() {
    std::cout << "desruptor" << std::endl;
}

void TcpConnection::establish() {
    if (connCb_)
        connCb_(shared_from_this());

    connChannel_.enableReading();
}

void TcpConnection::handleRead() {
    char buf[65536];
    memset(buf,0,sizeof(buf));
    int ret = ::read(connSock_.fd(),buf,65536);
    if (-1 == ret) {
        LOG_TRACE << strerror(errno);
        return;
    }
    else if (ret != 0)
        messageCb_(shared_from_this(),buf,ret);

}
