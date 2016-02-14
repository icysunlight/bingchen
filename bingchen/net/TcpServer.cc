#include <boost/bind.hpp>
#include <cstdio>

#include "TcpServer.h"
#include "TcpConnection.h"
#include "EventLoop.h"
#include "../base/logging.h"

using namespace bingchen;
    
TcpServer::TcpServer(EventLoop* loop,InetAddr addr) 
    : loop_(loop),
      acceptor_(new Acceptor(loop,addr)),
      localAddr_(acceptor_->getAddr()),
      connIndex_(0),
      threadPool_(new EventLoopThreadPool(loop)),
      started_(false)
{
    acceptor_->setNewConnectionCb(boost::bind(&TcpServer::OnConnection,this,_1));
}

void TcpServer::start() {
    assert(!started_);
    started_ = true;
    threadPool_->start(ioLoopInitCb_);
    acceptor_->listen();
}

void TcpServer::OnConnection(int fd) {
    //FIXME:unnormal use of accept result
    if (fd == -1)
        return;

    LOG_TRACE;

    char buf[32];
    snprintf(buf,32,"%d",connIndex_++);
    std::string name = buf;
    
    {
        EventLoop* ioLoop = threadPool_->getNext();

        ConnectionPtr conn(new TcpConnection(ioLoop,name,fd,localAddr_));
        connList_[name] = conn->shared_from_this();

        conn->setMessageCb(messageCb_);
        conn->setConnectionCb(connCb_);
        conn->setHighWaterMarkCb(highWaterMarkCb_);
        conn->setWriteCompleteCb(writeCompleteCb_);
        conn->setCloseCb(boost::bind(&TcpServer::removeConnection,this,_1));
        ioLoop->runInLoop(boost::bind(&TcpConnection::establish,conn));

    }
}
    

void TcpServer::removeConnection(const ConnectionPtr& conn) {
    if (loop_->isInLoopThread()) {
    connList_.erase(conn->getName());
    }
    else {
        LOG_TRACE << "remove conn from diffrent thread";
        loop_->runInLoop(boost::bind(&TcpServer::removeConnectionGuard,this,conn));
    }
}
    
void TcpServer::removeConnectionGuard(const ConnectionPtr& conn) {
    LOG_TRACE << "remove connection, name: " << conn->getName();
    connList_.erase(conn->getName());
}
