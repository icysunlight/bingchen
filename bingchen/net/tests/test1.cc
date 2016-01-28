#include "Channel.h"
#include "Poller.h"
#include "EventLoop.h"

#include <sys/timerfd.h>
#include <cstdio>
#include <cstring>
#include <boost/function.hpp>

using namespace bingchen;

EventLoop* g_loop;

void timeout() {
    printf("Timeout\n");
    g_loop->quit();
}

int main() {
    EventLoop loop;
    g_loop = &loop;

    int timefd = ::timerfd_create(CLOCK_MONOTONIC,TFD_NONBLOCK | TFD_CLOEXEC);
    Channel channel(timefd,&loop);
    channel.setReadCallback(timeout);
    channel.enableReading();

    struct itimerspec howlong;
    memset(&howlong,0,sizeof(howlong));
    howlong.it_value.tv_sec = 5;
    ::timerfd_settime(timefd,0,&howlong,NULL);
    
    loop.loop();

    ::close(timefd);
}
