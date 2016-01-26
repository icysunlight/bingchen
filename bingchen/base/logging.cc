#include <cstdio>
#include "logging.h"


using namespace bingchen;

const char* levelName[logger::LEVEL_NUM] = {
        "TRACE ",
        "INFO  ",
        "WARN  ",
        "ERROR ",
        "FATAL "
};

logger::loglevel initLoglevel() {
    if (!getenv("bingchen::LOG_TRACE")) {
        return logger::TRACE;
    }
    if (!getenv("bingchen::LOG_DEBUG")) {
        return logger::INFO;
    }
    return logger::ERROR;
}
//为了在加载main之前初始化，所以将其设置为全局变量
logger::loglevel g_loglevel = logger::TRACE;
//logger::loglevel g_loglevel = initloglevel();

void defaultOutputFunc(const void* buf,int lenth) {
    write(1,buf,lenth);
}

void defaultFflush() {
    fflush(stdout);
}

logger::logger(loglevel level,const char* filename,const char* func,const int line)
    : level_(level),
      filename_(getBaseName(filename)),
      func_(func),
      line_(line),
      outputFunc_(defaultOutputFunc),
      flushFunc_(defaultFflush)
    {
        stream_  << TimeStamp::now().toFormattedString(true) << " " 
                 << levelName[level_] << " "
                 << filename_ << " " 
                 << func_ << " "
                 << line_ << " ";
    }

logger::~logger() {
    stream_.finish();
    outputFunc_(stream_.data(),stream_.lenth());
    flushFunc_(); 
}

const char* logger::getBaseName(const char* filename) {
    char* basestart = strrchr(const_cast<char*>(filename),'/');
    if (basestart) {
        return basestart + 1;
    }
    return filename;


}
