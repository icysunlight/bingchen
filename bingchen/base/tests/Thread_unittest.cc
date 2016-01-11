#include "Thread.h"
#include "CurrentThread.h"
#include <stdio.h>
#include <boost/bind.hpp>

void threadFun1() {
    printf("tid = %d\n",bingchen::CurrentThread::tid());
}

void threadFun2(int a) {
    printf("tid = %d\tinput = %d\n",bingchen::CurrentThread::tid(),a);
}

class Bar {
private:
    int x_;
public:
    Bar(int x) : x_(x) {}
    void threadFun1() {
        printf("tid = %d\tx = %d\n",bingchen::CurrentThread::tid(),x_);
    }

    void threadFun2(int a) {
        printf("tid = %d\tinput = %d\n",bingchen::CurrentThread::tid(),a);
    }
};



int main() {

    printf("pid = %d\ttid = %d\n",::getpid(),bingchen::CurrentThread::tid());

    bingchen::Thread t1(threadFun1,"normal func with no argument");
    t1.start();
    t1.join();

    bingchen::Thread t2(boost::bind(threadFun2,5),"normal func with one argument");
    t2.start();
    t2.join();

    Bar bar1(1);
    bingchen::Thread t3(boost::bind(&Bar::threadFun1,&bar1),"member func with no argument");
    t3.start();
    t3.join();

    bingchen::Thread t4(boost::bind(&Bar::threadFun2,&bar1,3),"normal func with one argument");
    t4.start();
    t4.join();

    {
        bingchen::Thread t5(boost::bind(sleep,10),"normal func with one argument");
        t5.start();
    }


    return 0;
}

