#ifndef __BINGCHEN_NET_INETADDR_H_
#define __BINGCHEN_NET_INETADDR_H_
#include <netinet/in.h>
#include <string>


namespace bingchen {


class InetAddr{
public:
    InetAddr(short port,bool loopbackOnly);
    InetAddr(const std::string& ip,short port);
    InetAddr(struct sockaddr_in addr);

    void setAddr(const struct sockaddr_in& addr);

    std::string ipString() const;
    std::string addrString() const;
    int ip() const;
    short port() const;

    struct sockaddr_in saddr() const {
        return addr_;
    }

    const struct sockaddr* sockaddr() const {
        return (struct sockaddr*)&addr_;
    }

    int socklen() const {
        return sizeof(addr_);
    }

    bool operator == (const InetAddr& addr) const {
        return addr_.sin_port == addr.addr_.sin_port
            && addr_.sin_addr.s_addr == addr.addr_.sin_addr.s_addr;
    }

private:
    struct sockaddr_in addr_;
};
};

#endif
