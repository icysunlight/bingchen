#include "SocketOps.h"

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

int sockets::createSocket() {
    int fd = socket(AF_INET,SOCK_STREAM,0);
    setNonBlockAndCloseOnExec(fd); 
    return fd;
}
    
int sockets::connect(int fd,const InetAddr& addr) {
    return ::connect(fd,addr.sockaddr(),addr.socklen());
}

int sockets::getSocketError(int fd) {
    int optval;
    socklen_t len = sizeof(optval);
    ::getsockopt(fd,SOL_SOCKET,SO_ERROR,&optval,&len);
    return optval;
}

bool sockets::isSelfConnect(int fd) {
    return getLocalAddr(fd) == getPeerAddr(fd);
}

InetAddr sockets::getPeerAddr(int fd) {
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
    ::getpeername(fd,(struct sockaddr*)&addr,&addrlen);
    return InetAddr(addr); 
}

InetAddr sockets::getLocalAddr(int fd) {
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
    ::getsockname(fd,(struct sockaddr*)&addr,&addrlen);
    return InetAddr(addr); 
}
/*
 *
 *
Socket::Socket(int fd)
    : fd_(fd)
{
   setNonBlockAndCloseOnExec(fd_); 
}

Socket::~Socket() {
}

void Socket::setNodelay(bool on) {
    int optval = on ? 1 : 0;
    ::setsockopt(fd_,IPPROTO_TCP,TCP_NODELAY,&optval,sizeof(optval));    
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

void Socket::setSndBufSize(int size) {
    ::setsockopt(fd_,SOL_SOCKET,SO_SNDBUF,&size,sizeof(size));
}
    
int Socket::getSndBufSize() {
    int size = 0;
    int len = sizeof(size);
    ::getsockopt(fd_,SOL_SOCKET,SO_SNDBUF,&size,(unsigned int*)&len);
    return size;
}

void Socket::bindAddr(const InetAddr& addr) {
    struct sockaddr_in inaddr = addr.saddr();

    int ret = ::bind(fd_,(struct sockaddr*)(&inaddr),sizeof(inaddr));
}

void Socket::listen() {
    ::listen(fd_,SOMAXCONN);
}
    
int Socket::accept() {
    struct sockaddr addr;
    int socklen = sizeof(addr);
    int peerfd = ::accept(fd_,&addr,(socklen_t*)&socklen);
    return peerfd;
}


InetAddr Socket::getAddr() {
    struct sockaddr_in addr;
    memset(&addr,0,sizeof(addr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof(addr));
    getsockname(fd_,(struct sockaddr*)&addr,&addrlen);
    return InetAddr(addr); 
}


void Socket::close() {
    ::close(fd_);
}

void Socket::shutDownWrite() {
    ::shutdown(fd_,SHUT_WR);
}

*/
