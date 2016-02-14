#include "EventLoop.h"
#include "TcpServer.h"
#include "TcpConnection.h"
#include "InetAddr.h"
#include "Buffer.h"

#include <cstdio>
#include <boost/bind.hpp>

using namespace bingchen;

void OnConn(const ConnectionPtr& conn) {
    printf("new conn from %s\n",conn->getPeerAddr().addrString().c_str());
}

void OnMessage(const ConnectionPtr& conn,Buffer* buf) {
    string msg = buf->retrieveAsString().c_str();
    printf("read msg from %s",msg.c_str());
    conn->send(msg);
}


int main() {

    EventLoop loop;
    TcpServer server(&loop,InetAddr("192.168.32.128",55));
    server.setMessageCb(OnMessage);
    server.setConnectionCb(OnConn);
    server.start();
    loop.loop();


    return 0;
}
