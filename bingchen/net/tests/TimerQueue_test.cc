#include "TimerQueue.h"
#include "EventLoop.h"

#include <cstdio>
#include <boost/bind.hpp>

using namespace bingchen;

void cb(int id) {
    printf("expiration %d\n",id);
}


int main() {


    EventLoop loop;
    loop.runEvery(2,boost::bind(cb,1));
    loop.runEvery(4,boost::bind(cb,3));
    TimerId id = loop.runAfter(4,boost::bind(cb,2));
    loop.cancelTimer(id);
    loop.loop();


    return 0;
}
