#include "logstream.h"
#include <cstdio>

using namespace bingchen;

logstream& logstream::operator << (int val) {
    char buf[32];
    snprintf(buf,31,"%d",val);
    buffer_.append(buf,strlen(buf));
    return *this;
}

logstream& logstream::operator << (short val) {
    char buf[32];
    snprintf(buf,31,"%d",val);
    buffer_.append(buf,strlen(buf));
    return *this;
}
//FIXME : use PRI64
logstream& logstream::operator << (long long val) {
    char buf[32];
    snprintf(buf,31,"%lld",val);
    buffer_.append(buf,strlen(buf));
    return *this;
}

logstream& logstream::operator << (double val) {
    char buf[32];
    snprintf(buf,31,"%.8lf",val);
    buffer_.append(buf,strlen(buf));
    return *this;
}
