#ifndef __BINGCHEN_NET_SOCKETOPS_H_
#define __BINGCHEN_NET_SOCKETOPS_H_

#include "InetAddr.h"

namespace bingchen {

namespace sockets {

int createSocket();
int connect(int fd,const InetAddr& addr);
int getSocketError(int fd);
bool isSelfConnect(int fd);
InetAddr getPeerAddr(int fd);
InetAddr getLocalAddr(int fd);

/*
void setNodelay(int fd,bool on);
void setAddrReuse(int fd,bool on);
void setPortReuse(int fd,bool on);
void setKeepAlive(int fd,bool on);
void setSndBufSize(int fd,int size);
int getSndBufSize(int fd);
void bindAddr(int fd,const InetAddr& addr);
void listen();
int accept();

void close();
void shutDownWrite();
*/

};
};
#endif
