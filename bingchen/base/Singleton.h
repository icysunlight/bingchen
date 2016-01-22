#ifndef __BINGCHEN_BASE_SINGLETON_H_
#define __BINGCHEN_BASE_SINGLETON_H_

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <stdlib.h>

namespace bingchen {

template<typename T>
class Singleton : boost::noncopyable
{
public:
    static T& Instance() {
        pthread_once(&once_guard_,&Singleton::init);
        return *val_;
    }
    

private:
    static void init() {
       val_ = new T; 
       ::atexit(destroy);
    }
    static void destroy() {
        typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy;

        delete val_;
        val_ = NULL;
    }
    static pthread_once_t once_guard_;
    static T* val_;
};


template<typename T>
pthread_once_t Singleton<T>::once_guard_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>:: val_ = NULL;

};


#endif
