#include "EventLoop.h"
#include "TimerQueue.h"

#include <cstdio>

using namespace bingchen;

EventLoop* g_loop = NULL;
TimerId id;

void print() {
    printf("timer expiration\n");
    g_loop->cancelTimer(id);
}

int main() {

    EventLoop loop;
    id = loop.runEvery(1,print);
    g_loop = &loop;
    loop.loop();




    return 0;
}
