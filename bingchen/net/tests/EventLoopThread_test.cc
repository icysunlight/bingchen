#include "EventLoopThread.h"
#include "EventLoop.h"
#include <cstdio>

using namespace bingchen;

void timerThread() {
    printf("expiration\n");
}


void threadTask(EventLoop* loop) {
    loop->runAfter(2,timerThread);
}


int main() {
    
    EventLoopThread thread(threadTask,"");
    thread.start();
    sleep(1000);

    return 0;
}
