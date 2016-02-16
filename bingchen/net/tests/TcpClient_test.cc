#include "TcpClient.h"
#include "EventLoop.h"
#include "NetTypes.h"
#include "TcpConnection.h"
#include "Buffer.h"

#include <string>
#include <iostream>

using namespace bingchen;


void connInit(const ConnectionPtr& conn) {
    std::cout << "new connection" << std::endl;
    conn->send("hello\n");
    conn->send("12345");
}

void OnMessage(const ConnectionPtr& conn,Buffer* buf) {
    std::string str = buf->retrieveAsString();
    std::cout << str;
    std::cin >> str;
    conn->send(str);
}




int main() {

    EventLoop loop;
    InetAddr addr("192.168.32.128",55);
    TcpClient client(&loop,addr);
    client.enableRetry();
    client.setInitCb(connInit);
    client.setMessageCb(OnMessage);
    client.connect();
    loop.loop();




    return 0;
}
