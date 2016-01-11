#include "atomic.h"
#include <cassert>
#include <stdio.h>


int main() {
    
    {
        bingchen::atomicInt64 a0;
        assert(0 == a0.get());
        assert(0 == a0.getAndAdd(5));
        assert(5 == a0.get());
        assert(10 == a0.addAndGet(5));
        assert(10 == a0.get());
        assert(11 == a0.incrementAndGet());
        assert(11 == a0.get());
        assert(10 == a0.decrementAndGet());
        assert(10 == a0.get());
        a0.increment();
        assert(11 == a0.get());
        assert(11 == a0.getAndSet(100));
        assert(100 == a0.get());
    }


    {
        bingchen::atomicInt32 a0;
        assert(0 == a0.get());
        assert(0 == a0.getAndAdd(5));
        assert(5 == a0.get());
        assert(10 == a0.addAndGet(5));
        assert(10 == a0.get());
        assert(11 == a0.incrementAndGet());
        assert(11 == a0.get());
        assert(10 == a0.decrementAndGet());
        assert(10 == a0.get());
        a0.increment();
        assert(11 == a0.get());
        printf("%d\n",a0.getAndSet(20));
        assert(20 == a0.getAndSet(20));
        assert(100 == a0.get());
    }





    return 0;
}
