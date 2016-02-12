#ifndef __BINGCHEN_NET_BUFFER_H_
#define __BINGCHEN_NET_BUFFER_H_

#include <vector>
#include <string>

namespace bingchen {

class Buffer {
public:
    static const int kPrependInit = 8;
    Buffer();
    
    int readableBytes();
    int writeableBytes();
    int prependableBytes();

    const char* peek() const;
    std::string retrieveAsString();
    void append(const void* data,int len);

    int readFd(int fd);
    void retrieve(int lenth);

    char* begin();
private:
    

    void hasWriten(int lenth);

    void makeSpace(int size);
    void moveReadableData();

    std::vector<char> buffer_;
    int readIndex_;
    int writeIndex_;
};


};

#endif
