#include "Connector.h"
#include "EventLoop.h"
#include "Socket.h"
#include "SocketOps.h"
#include "../base/logging.h"
#include "Channel.h"

#include <boost/bind.hpp>

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>

using namespace bingchen;

const int kMaxWaitTime = 30;

Connector::Connector(EventLoop* loop,const InetAddr& addr)
    : loop_(loop),
      addr_(addr),
      start_(false),
      waitTime_(1),
      state_(disconnected)
{}

void Connector::start() {
    state_ = connecting;
    start_ = true;
    loop_->runInLoop(boost::bind(&Connector::connect,this));
}

void Connector::connect() {
    LOG_TRACE << "connect to " << addr_.addrString();
    fd_ = sockets::createSocket();
    int ret = sockets::connect(fd_,addr_);
    int savedError = (ret == 0) ? 0 : errno;
    if (0 == savedError || EINPROGRESS == savedError) {
        registConnect();
        return;
    }
    else {
        retry();
    }
}

    
void Connector::stop() {
    loop_->runInLoop(boost::bind(&Connector::stopInLoop,this));        
}

void Connector::stopInLoop() {
    if (connecting == state_) {
        if (channel_.get()) {
            unregistConnect();
        }
        close(fd_);
    }
}

void Connector::retry() {
    LOG_TRACE << "reconnect to " << addr_.addrString();
    close(fd_);
    nextTimer_ = loop_->runAfter(waitTime_,boost::bind(&Connector::connect,this));
    waitTime_ <<= 1;
    if (waitTime_ > 30) {
        waitTime_ = 30;
    }

}

void Connector::registConnect() {
    channel_.reset(new Channel(fd_,loop_));
    channel_->setWriteCallback(boost::bind(&Connector::handleWrite,this));
    channel_->setErrorCallback(boost::bind(&Connector::handleError,this));
    channel_->enableWriting();
}

void Connector::unregistConnect() {
    channel_->disableAll();
    channel_->remove();
    loop_->queueInLoop(boost::bind(&Connector::resetChannel,this));
}

void Connector::resetChannel() {
    channel_.reset();
}

void Connector::handleWrite() {
    unregistConnect();
    LOG_TRACE << fd_;
    
    int err = sockets::getSocketError(fd_);
    if (err) {
        close(fd_);
    }
    else if (sockets::isSelfConnect(fd_)) {
    }
    else {
        if (newConnectionCb_) {
            state_ = connected;
            newConnectionCb_(fd_);
        }
    }
}

void Connector::handleError() {
    unregistConnect();
    retry(); 
}
