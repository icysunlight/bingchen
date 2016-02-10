#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "InetAddr.h"

#include <cstdio>
#include <boost/bind.hpp>

using namespace bingchen;

void OnConn(const ConnectionPtr& conn) {
    printf("new conn from %s\n",conn->getPeerAddr().addrString().c_str());
}

void OnMessage(const ConnectionPtr& conn,void* buf,int len) {
    printf("read msg from %s\n",buf);
}


int main() {

    EventLoop loop;
    TcpServer server(&loop,InetAddr("192.168.32.128",55));
    server.setMessageCb(OnMessage);
    server.setConnectionCb(OnConn);
    server.start();




    return 0;
}