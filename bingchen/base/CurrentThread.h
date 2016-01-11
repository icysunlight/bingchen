#ifndef __BINGCHEN_CURRENTTHREAD_H_
#define __BINGCHEN_CURRENTTHREAD_H_


namespace bingchen 
{
namespace CurrentThread 
{
    extern __thread pid_t t_cachedTid;
    extern __thread char t_tidString[32];
    extern __thread const char* t_threadName;
    pid_t tid();
    const char* threadname();
    void cacheTid();
    const char* tidString();
};
};



#endif
