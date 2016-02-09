#include "Acceptor.h"
#include "InetAddr.h"
#include "Socket.h"
#include "EventLoop.h"
#include "../base/logging.h"

using namespace bingchen;

void connection(Socket sock) {
    char buf[] = "Hello and ByeBye!";
    ::write(sock.fd(),buf,sizeof(buf));
    sock.close();
}

int main() {

    EventLoop loop;
    Acceptor accept(&loop,InetAddr("192.168.32.128",8888));
    accept.setNewConnectionCb(connection);
    accept.listen();
    loop.loop();

    return 0;
}
