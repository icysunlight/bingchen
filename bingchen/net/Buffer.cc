#include "Buffer.h"
#include <algorithm>
#include <cstring>
#include <sys/uio.h>

using namespace bingchen;

Buffer::Buffer()
    : writeIndex_(kPrependInit),
      readIndex_(kPrependInit)
{
    buffer_.resize(1024);
}
    
int Buffer::readableBytes() {
    return writeIndex_ - readIndex_;
}

int Buffer::writeableBytes() {
    return buffer_.size() - writeIndex_;
}

int Buffer::prependableBytes() {
    return readIndex_;
}

const char* Buffer::peek() const {
    return &*buffer_.begin() + readIndex_;
}

std::string Buffer::retrieveAsString() {
    std::string ret(begin() + readIndex_, begin() + writeIndex_);
    readIndex_ = writeIndex_ = kPrependInit;
    return ret;
}

void Buffer::append(const void* data,int len) {
    makeSpace(len);
    std::copy((char*)data,(char*)data + len,begin() + writeIndex_);
    hasWriten(len);
}
    

char* Buffer::begin() {
    return const_cast<char*>(&*buffer_.begin());
}
    
void Buffer::retrieve(int lenth) {
    readIndex_ += lenth;
}

void Buffer::hasWriten(int lenth) {
    writeIndex_ += lenth;
}

void Buffer::makeSpace(int size) {
    if (writeableBytes() >= size) {
        return;
    }

    moveReadableData();
    if (size > writeableBytes() ) {
        buffer_.resize(size - writeableBytes() + buffer_.size());
    }

}

void Buffer::moveReadableData() {
    int orisize = readableBytes();
    ::memmove(begin() + kPrependInit,begin() + readIndex_,readableBytes());
    readIndex_ = kPrependInit;
    writeIndex_ = orisize + readIndex_;
}

int Buffer::readFd(int fd) {
    char extraBuff[65536];

    const int writable = writeableBytes();

    struct iovec iovc[2];
    iovc[0].iov_base = begin() + writeIndex_;
    iovc[0].iov_len = writable;
    iovc[1].iov_base = extraBuff;
    iovc[1].iov_len = 65536;
    int readIn = readv(fd,iovc,2);

    if (readIn > writable) {
        hasWriten(writable);
        append(iovc[1].iov_base,readIn - writable);
    }
    else if (readIn > 0){
        hasWriten(readIn);
    }
    return readIn;
}
