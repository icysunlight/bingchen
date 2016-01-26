#ifndef __BINGCHEN_BASE_THREADLOCALSINGLETON_H_
#define __BINGCHEN_BASE_THREADLOCALSINGLETON_H_

#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <cassert>

namespace bingchen {

template<typename T>
class ThreadLocalSingleton
    : public boost::noncopyable
{
public:
    static T& Instance() {
        if (NULL == pointer_) {
            pointer_ = new T();
            deleter_.set(pointer_);
        } 
        return *pointer_;
    }
private:
    ThreadLocalSingleton();
    ~ThreadLocalSingleton();

    static void destroy(void* pointer) {
        assert(pointer == pointer_);
        typedef char MUST_BE_COMPLETE_TYPE[sizeof(*pointer_) == 0 ? -1 : 1];
        MUST_BE_COMPLETE_TYPE dummy;
        if (pointer_)
            delete pointer_;
    }

    class deleter {
    public:
        deleter() {
            pthread_key_create(&key_,&ThreadLocalSingleton::destroy);    
        }
        ~deleter() {
            pthread_key_delete(key_);
        }
        void set(T* pointer) {
            pthread_setspecific(key_,pointer);
        }

    private:
        pthread_key_t key_;
    };

    static __thread T* pointer_;
    static deleter deleter_;


};

template<typename T>
__thread T* ThreadLocalSingleton<T>::pointer_ = NULL;

template<typename T>
typename ThreadLocalSingleton<T>::deleter ThreadLocalSingleton<T>::deleter_;

};


#endif
