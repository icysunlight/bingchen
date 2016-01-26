#ifndef __BINGCHEN_BASE_LOGGING_H_
#define __BINGCHEN_BASE_LOGGING_H_
#include <boost/noncopyable.hpp>
#include "TimeStamp.h"
#include "logstream.h"

namespace bingchen {

/*
 * 1.控制日志级别，高于日志级别的日志才输出
 *      使用g_loglevel标志日志级别，在cc文件中定义，h文件中声明extern
 * 2.控制输出函数和清空缓存的方式，采用函数定义
 * 3.控制输出缓冲区的内容
 *
 */
class logger
    : boost::noncopyable 
{
public:
    enum loglevel{
        TRACE,
        INFO,
        WARN,
        ERROR,
        FATAL,
        LEVEL_NUM
    };

    typedef void (*outputFunc)(const void* buf,int len);
    typedef void (*flushFunc)();

    logger(loglevel level,const char* filename,const char* func,const int line);
    ~logger();

    logstream& stream() { return stream_; }

    const char* getBaseName(const char* filename);


private:
    TimeStamp time_;
    loglevel level_;
    const char* filename_;
    const char* func_;
    const int line_;
    logstream stream_;
    bool abort_;

    outputFunc outputFunc_;
    flushFunc flushFunc_;
};

extern logger::loglevel g_loglevel;
inline logger::loglevel getLoglevel() { return g_loglevel;}

#define LOG_TRACE (if(logger::getLoglevel() <= logger::TRACE) \
        logger(logger::TRACE,__FILE__,__func__,__LINE__).stream())

#define LOG_INFO (if(logger::getLoglevel() <= logger::INFO) \
        logger(logger::INFO,__FILE__,__func__,__LINE__).stream())

#define LOG_WARN (if(logger::getLoglevel() <= logger::WARN) \
        logger(logger::WARN,__FILE__,__func__,__LINE__).stream())

#define LOG_ERROR logger(bingchen::logger::ERROR,__FILE__,__func__,__LINE__).stream()
#define LOG_FATAL logger(logger::FATAL,__FILE__,__func__,__LINE__).stream()


};





#endif
