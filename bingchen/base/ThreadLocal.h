#ifndef __BINGCHEN_BASE_THREADLOACL_H_
#define __BINGCHEN_BASE_THREADLOACL_H_

#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace bingchen {

template<typename T>
class ThreadLocal : public boost::noncopyable
{
public:
    ThreadLocal() 
    {
        pthread_key_create(&key_,&ThreadLocal::destructor); 
    }

    ~ThreadLocal()
    {
        pthread_key_delete(key_); 
    }

    T& value() {
        T* val = static_cast<T*>(pthread_getspecific(key_));
        if (NULL == val) {
            val = new T();
            pthread_setspecific(key_,static_cast<void*>(val));
        }
        return *val;
    }
private:
    static void destructor(void* arg) {
        typedef char TYPE_MUST_BE_COMPLETE_TYPE[sizeof(T) == 0 ? -1 : 1];
        TYPE_MUST_BE_COMPLETE_TYPE dummy;
        T* val = static_cast<T*>(arg);
        delete val;
    }

private:
    pthread_key_t key_;
};
};

#endif
