#ifndef __BINGCHEN_BASE_LOGSTREAM_H_
#define __BINGCHEN_BASE_LOGSTREAM_H_

#include <boost/noncopyable.hpp>
#include <cstring>
#include <string>
#include <cstdio>

namespace bingchen {

template<int SIZE>
class FixedBuffer
    : boost::noncopyable
{
public:
    FixedBuffer()
        : cur_(data_)
    {}

    int avail() {
        return static_cast<int>(end() - cur_);
    }

    void append(const void* str,int len) {
        if (avail() > len) {
            memcpy(cur_,str,len);
            cur_ += len;
        } 
    }

    void reset() { cur_ = data_; }

    int lenth() const { return static_cast<int>(cur_ - data_); }
    const char* data() { return data_; }

private:
    char* end() {
        return data_ + SIZE;
    }

    char data_[SIZE];
    char* cur_;
};


class logstream
    : boost::noncopyable
{
public:
    typedef FixedBuffer<1000> Buffer;

    int lenth() { return buffer_.lenth(); }
    const char* data() { return buffer_.data(); }
    void finish() { buffer_.append("\n",1); }

    logstream& operator << (const std::string& str) {
        if (str.size())
            buffer_.append(str.c_str(),str.size());
        else
            buffer_.append("(null)",6);
        return *this;
    }

    logstream& operator << (const char* str) {
        buffer_.append(str,strlen(str));
        return *this;
    }

    logstream& operator << (char chr) {
        buffer_.append(&chr,1);
        return *this;
    }
    
    logstream& operator << (bool val) {
        buffer_.append(val ? "1" : "0",1);
        return *this;
    }

    logstream& operator << (int val);
    logstream& operator << (short val);
    logstream& operator << (long long val);
    logstream& operator << (double val);

private:
    Buffer buffer_;
};

};

#endif
