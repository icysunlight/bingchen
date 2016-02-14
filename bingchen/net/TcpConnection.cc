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
      name_(name),
      state_(Connecting),
      highWaterMark_(10 * 1024 * 1024)
{
    connChannel_.setReadCallback(boost::bind(&TcpConnection::handleRead,this));
//    LOG_TRACE << "buf size: " << connSock_.getSndBufSize();
//    connSock_.setSndBufSize(10);
//    LOG_TRACE << "buf size: " << connSock_.getSndBufSize();
}

TcpConnection::~TcpConnection() {
}

void TcpConnection::establish() {
    LOG_TRACE << "new conn bind to " << getPeerAddr().addrString() 
              << "at thread: " << CurrentThread::tid();
    assert(loop_->isInLoopThread()); 
    if (connCb_)
        connCb_(shared_from_this());

    connChannel_.enableReading();
    state_ = Connected;
    LOG_TRACE << "new conn bind to " << getPeerAddr().addrString() 
              << "at thread: " << CurrentThread::tid();
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
    else if (ret != 0) {
        messageCb_(shared_from_this(),&inBuf_);
    }
}

void TcpConnection::handleClose() {
    LOG_TRACE << "peer close at " << connSock_.getPeerAddr().addrString()
              << "fd : " << connSock_.fd()
              << "thread: " << CurrentThread::tid();
    connChannel_.disableAll();
    loop_->runInLoop(boost::bind(&TcpConnection::unregistConn,shared_from_this()));
}
    
void TcpConnection::handleWrite() {
    const int twrite = outputBuffer_.readableBytes();
    int nwrote = ::write(connSock_.fd(),outputBuffer_.begin(),twrite);
    if (nwrote < 0) {
        LOG_ERROR << "handleWrite";
    }
    else {
       outputBuffer_.retrieve(nwrote); 
       if (nwrote == twrite) {
           connChannel_.disbleWriting();
           if (writeCompleteCb_) {
               loop_->runInLoop(boost::bind(&TcpConnection::writeCompleteCb_,shared_from_this()));
           }
           if (state_ == Disconnecting) {
               shutdownInLoop();
           }
       }
    }
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

void TcpConnection::send(const std::string& content){
    if (loop_->isInLoopThread()) {
        sendInLoop(content);
    }
    else {
        loop_->runInLoop(boost::bind(&TcpConnection::sendInLoop,this,content));
    }
}
    
void TcpConnection::sendInLoop(const std::string& content) {
    int nwrote = 0;
    if (!connChannel_.isWriting()) {
        nwrote = ::write(connSock_.fd(),content.c_str(),content.size());
        LOG_TRACE << nwrote;
        if (nwrote < 0) {
           nwrote = 0; 
        }
    }
    if (nwrote == content.size()) {
        if (writeCompleteCb_) {
            loop_->runInLoop(boost::bind(&TcpConnection::writeCompleteCb_,shared_from_this()));
        }
    }
    else if (nwrote < content.size()) {
        int oriSize = outputBuffer_.readableBytes();
        outputBuffer_.append(content.c_str() + nwrote,content.size() - nwrote);
        if (oriSize < highWaterMark_
         && outputBuffer_.readableBytes() >= highWaterMark_
         && highWaterMark_)
        {
            loop_->runInLoop(boost::bind(&TcpConnection::highWaterMarkCb_,shared_from_this()));
        }
        if (!connChannel_.isWriting()) {
            connChannel_.enableWriting();
        }
    }
}

void TcpConnection::shutdown() {
    if (loop_->isInLoopThread()) {
        shutdownInLoop();
    }
    else {
        loop_->runInLoop(boost::bind(&TcpConnection::shutdownInLoop,this));
    }
}
    
void TcpConnection::shutdownInLoop() {
    state_ = Disconnecting;
    if (!connChannel_.isWriting()) {
       connChannel_.disableReading();
       connSock_.shutDownWrite(); 
    }
}
