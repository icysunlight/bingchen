#include "Socket.h"
#include "InetAddr.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#include <cstdio>
#include <cstring>


using namespace bingchen;

void setNonBlockAndCloseOnExec(int sockfd) {
    int flags = ::fcntl(sockfd,F_GETFL,0);
    flags |= O_NONBLOCK;
    ::fcntl(sockfd,F_SETFL,flags);

    flags = ::fcntl(sockfd,F_GETFD,0);
    flags |= FD_CLOEXEC;
    ::fcntl(sockfd,F_SETFD,flags);
}

Socket::Socket() 
    : fd_(socket(AF_INET,SOCK_STREAM,0))
{
   setNonBlockAndCloseOnExec(fd_); 
}
    
Socket::Socket(int fd)
    : fd_(fd)
{
   setNonBlockAndCloseOnExec(fd_); 
}


void Socket::setNodelay(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(fd_,IPPROTO_TCP,TCP_NODELAY,
                &optval,sizeof(optval));    
}

void Socket::setAddrReuse(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(fd_,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
}

void Socket::setPortReuse(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(fd_,SOL_SOCKET,SO_REUSEPORT,&optval,sizeof(optval));
}

void Socket::setKeepAlive(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(fd_,SOL_SOCKET,SO_KEEPALIVE,&optval,sizeof(optval));
}

void Socket::bindAddr(const InetAddr& addr) {
    struct sockaddr_in inaddr = addr.saddr();

    int ret = ::bind(fd_,(struct sockaddr*)(&inaddr),sizeof(inaddr));
}

void Socket::listen() {
    ::listen(fd_,SOMAXCONN);
}
    
Socket Socket::accept() {
    struct sockaddr addr;
    int socklen = sizeof(addr);
    int peerfd = ::accept(fd_,&addr,(socklen_t*)&socklen);
    Socket peersocket(peerfd);
    return peersocket;
}

InetAddr Socket::getAddr() {
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
    getsockname(fd_,(struct sockaddr*)&addr,&addrlen);
    return InetAddr(addr); 
}
