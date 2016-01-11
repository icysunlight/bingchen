#include "exception.h"
#include <execinfo.h>
#include <stdio.h>
#include <cstdlib>

using namespace bingchen;


void exception::fillBackTrace() {
    const int bufSize = 200;
    void* buf[bufSize];
    int cntBackTrace = ::backtrace(buf,bufSize);

    char** backTrace = ::backtrace_symbols(buf,cntBackTrace);
    //TODO: use api::__cxa_demangle
    for (int i = 0 ; i < cntBackTrace ; ++i) {
        backTrace_.append(backTrace[i]);
        backTrace_.push_back('\n');
    }
    free(static_cast<void*>(backTrace));
}

exception::exception(const char* msg)
    : message_(msg) {
        fillBackTrace();
    }

exception::exception(const std::string& msg) 
    : message_(msg) {
        fillBackTrace();
    }

exception::~exception() throw() {
}

const char* exception::what() const throw() {
    return message_.c_str();
}

const char* exception::getBackTrace() const throw() {
    return backTrace_.c_str();
}
