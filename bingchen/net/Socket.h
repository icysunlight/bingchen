#ifndef __BINGCHEN_SOCKET_H_
#define __BINGCHEN_SOCKET_H_



namespace bingchen {

class InetAddr;
class noncopyable;

class Socket {
public:
    Socket();
    Socket(int fd);

    void setNodelay(bool on);
    void setAddrReuse(bool on);
    void setPortReuse(bool on);
    void setKeepAlive(bool on);

    void bindAddr(const InetAddr& addr);
    void listen();
    Socket accept();

    InetAddr getAddr();

    int fd() const {return fd_;}
private:
    const int fd_;

};
};

#endif
