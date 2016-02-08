#ifndef __BINGCHEN_NEW_INETADDR_H_
#define __BINGCHEN_NEW_INETADDR_H_
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

private:
    struct sockaddr_in addr_;
};
};

#endif
