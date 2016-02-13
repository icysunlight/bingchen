#include "Acceptor.h"
#include "EventLoop.h"
#include "../base/logging.h"

#include <boost/bind.hpp>

using namespace bingchen;

Acceptor::Acceptor(EventLoop* loop,InetAddr addr) 
    : loop_(loop),
      acceptSock_(),
      acceptChannel_(acceptSock_.fd(),loop),
      listening_(false)
{
    acceptSock_.setAddrReuse(true);
    acceptSock_.bindAddr(addr);
    acceptSock_.setAddrReuse(true);
    acceptChannel_.setReadCallback(boost::bind(&Acceptor::handleRead,this));
}

bool Acceptor::listen() {
    if (listening_) {
        return false;
    }

    listening_ = true;
    acceptSock_.listen();
    acceptChannel_.enableReading();
    LOG_TRACE << "listen at " << acceptSock_.getAddr().addrString()
              << " tid: " << CurrentThread::tid();
}

void Acceptor::handleRead() {
    int peerfd = acceptSock_.accept();

    if (peerfd) {
        newConnectionCb_(peerfd);
        //LOG_TRACE << "new connection from " << peerSock.getAddr().addrString();
    }
}
