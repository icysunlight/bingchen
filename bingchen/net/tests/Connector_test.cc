#include "Connector.h"
#include "EventLoop.h"
#include "InetAddr.h"
#include "SocketOps.h"

#include <boost/bind.hpp>

#include <cstdio>

using namespace bingchen;

void OnNewConnection(int fd) {
    printf("new connection\n");
    ::close(fd);
}

int main() {

    EventLoop loop;
    InetAddr addr("192.168.32.128",55);
    Connector conn(&loop,addr);
    conn.setNewConnectionCb(OnNewConnection);
    conn.start();
    loop.loop();



    return 0;
}
