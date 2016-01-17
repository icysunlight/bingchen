#include "ThreadPool.h"
#include "Thread.h"
#include "CurrentThread.h"
#include <cstdio>
#include <boost/bind.hpp>


using namespace bingchen;

int threadFunc(int num) {
    printf("tid:%d\tnum:%d\n",CurrentThread::tid(),num);
}



int main() {

    ThreadPool pool;
    pool.setMaxQueueSize(10);
    pool.start(3);

    for (int i = 0 ; i < 100 ; ++i) {
        pool.put(boost::bind(threadFunc,i));
    }

    sleep(10);



    return 0;
}
