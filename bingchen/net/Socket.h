#ifndef __BINGCHEN_NET_SOCKET_H_
#define __BINGCHEN_NET_SOCKET_H_

#include "InetAddr.h"
namespace bingchen {

class Socket{
public:
    Socket();
    Socket(int fd);
    ~Socket();

    void setNodelay(bool on);
    void setAddrReuse(bool on);
    void setPortReuse(bool on);
    void setKeepAlive(bool on);

    void setSndBufSize(int size);
    int getSndBufSize();

    void bindAddr(const InetAddr& addr);
    void listen();
    int accept();
    int connect(const InetAddr& addr);
    int getSocketError();


    InetAddr getAddr();
    InetAddr getPeerAddr();
    InetAddr getLocalAddr();

    int fd() const {return fd_;}

    void close();
    void shutDownWrite();

    bool isSelfConnect();
private:
    int fd_;

};

};

#endif
