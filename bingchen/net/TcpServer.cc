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

void TcpServer::OnConnection(Socket sock) {
    //FIXME:unnormal use of accept result
    if (sock.fd() == -1)
        return;

    char buf[32];
    snprintf(buf,32,"%d",connIndex_++);
    std::string name = buf;
    
    {
        ConnectionPtr conn(new TcpConnection(loop_,name,sock,localAddr_,sock.getAddr()));
        connList_[name] = conn->shared_from_this();
        conn->setMessageCb(messageCb_);
        conn->setConnectionCb(connCb_);
        conn->establish();

        LOG_TRACE << "new conn bind to " << connList_[name]->getPeerAddr().addrString();
    }
}
