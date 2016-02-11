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
      connIndex_(0)
{
    acceptor_->setNewConnectionCb(boost::bind(&TcpServer::OnConnection,this,_1));
}

void TcpServer::start() {
    acceptor_->listen();
    loop_->loop();
}

void TcpServer::OnConnection(int fd) {
    //FIXME:unnormal use of accept result
    if (fd == -1)
        return;

    char buf[32];
    snprintf(buf,32,"%d",connIndex_++);
    std::string name = buf;
    
    {
        ConnectionPtr conn(new TcpConnection(loop_,name,fd,localAddr_));
        connList_[name] = conn->shared_from_this();
        conn->setMessageCb(messageCb_);
        conn->setConnectionCb(connCb_);
        conn->setCloseCb(boost::bind(&TcpServer::removeConnection,this,_1));
        conn->establish();

        LOG_TRACE << "new conn bind to " << connList_[name]->getPeerAddr().addrString();
    }
}
    

void TcpServer::removeConnection(const ConnectionPtr& conn) {
    connList_.erase(conn->getName());
    LOG_TRACE << "remove connection, name: " << conn->getName();
}
