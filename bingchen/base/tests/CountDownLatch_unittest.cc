#include "CountDownLatch.h"
#include "Condition.h"
#include "Thread.h"

#include <cstdio>
#include <boost/bind.hpp>

using namespace bingchen;

void waitingThreadFunc(CountDownLatch* latch) {
    latch->wait();
    printf("wait complete\n");
}

void preThreadFunc(CountDownLatch* latch) {
    printf("count is %d\n",latch->getCount());
    latch->CountDown();
}


int main() {
    CountDownLatch countLatch(5);
    Thread waitingThread(boost::bind(waitingThreadFunc,&countLatch),"");
    waitingThread.start();

    for (int i = 0 ; i < 5 ; ++i) {
        sleep(1);
        Thread thread(boost::bind(preThreadFunc,&countLatch),"");
        thread.start();
        thread.join();
    }
    waitingThread.join();


    return 0;
}
