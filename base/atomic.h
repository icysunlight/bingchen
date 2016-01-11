#ifndef __BINGCHEN_BASE_ATOMIC
#define __BINGCHEN_BASE_ATOMIC

#include <boost/noncopyable.hpp>

namespace bingchen {

namespace base {

template<typename T>
class atomicInt : public boost::noncopyable 
{ 
private:
    T val_;

public:
    atomicInt() : val_(0) {
    }

    T get() {
        return __sync_val_compare_and_swap(&val_,0,0);
    }

    T getAndAdd(T x) {
        return __sync_fetch_and_add(&val_,x);
    }

    T addAndGet(T x) {
        return getAndAdd(x) + x;
    }

    T incrementAndGet() {
        return addAndGet(1);
    }

    T decrementAndGet() {
        return addAndGet(-1);
    }

    void increment() {
        incrementAndGet();
    }

    void decrement(T x) {
        decrementAndGet();
    }

    T getAndSet(T x) {
        __sync_lock_test_and_set(&val_,x);
    }
};
};
typedef base::atomicInt<int32_t> atomicInt32;
typedef base::atomicInt<int64_t> atomicInt64;
};

#endif
