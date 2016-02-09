#include "TimerQueue.h"
#include "EventLoop.h"

#include "../../base/Thread.h"

#include <cstdio>
#include <boost/bind.hpp>

using namespace bingchen;

EventLoop* g_loop;

void cb(int id) {
    printf("expiration %d\n",id);
}

void ThreadFunc() {
    g_loop->runEvery(2,boost::bind(cb,1));
}


int main() {


    EventLoop loop;
    g_loop = &loop;
    loop.runEvery(2,boost::bind(cb,2));

    Thread thread(ThreadFunc,"");
    thread.start();

    loop.loop();


    return 0;
}
