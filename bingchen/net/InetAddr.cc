#include <string>
#include <cstring>
#include <cstdio>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "InetAddr.h"

using namespace bingchen;

void setAddrFromIpPort(const std::string& ip,short port,struct sockaddr_in& addr) {
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = ::inet_addr(ip.c_str()); 
}

InetAddr::InetAddr(short port,bool loopbackOnly)
{
    memset(&addr_,0,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = htonl(loopbackOnly ? INADDR_LOOPBACK : INADDR_ANY);
} 

InetAddr::InetAddr(const std::string& ip,short port) {
    setAddrFromIpPort(ip,port,addr_);
}

InetAddr::InetAddr(struct sockaddr_in addr) {
    addr_ = addr;
}

void InetAddr::setAddr(const struct sockaddr_in& addr) {
    addr_ = addr;
}

std::string InetAddr::ipString() const{
    char buf[32];
    inet_ntop(AF_INET,&addr_.sin_addr,buf,32);
    return buf;
}

std::string InetAddr::addrString() const{
    char buf[40];
    snprintf(buf,40,"%s:%d",ipString().c_str(),port());
    return buf;
}

int InetAddr::ip() const{
    return ::ntohl(addr_.sin_addr.s_addr);
}
    
short InetAddr::port() const {
    return ::ntohs(addr_.sin_port);
}
