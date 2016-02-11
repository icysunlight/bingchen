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

    void bindAddr(const InetAddr& addr);
    void listen();
    int accept();

    InetAddr getAddr();

    int fd() const {return fd_;}

    void close();
    void shutDownWrite();
private:
    const int fd_;

};

};

#endif
