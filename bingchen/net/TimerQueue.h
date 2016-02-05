#ifndef __BINGCHEN_TIMERQUEUE_H_
#define __BINGCHEN_TIMERQUEUE_H_
#include "Channel.h"
#include "../base/TimeStamp.h"
#include "Timer.h"
#include "TimerId.h"
#include <set>
#include <queue>

namespace bingchen {

class EventLoop;

class TimerQueue {

public:
    TimerQueue(EventLoop* loop);

    TimerId addTimer(TimeStamp expiration,double internval,boost::function<void ()> cb);
    void cancelTimer(TimerId id);
    void reset();
    void handleRead();


private:
    void cancelTimerInloop(TimerId id);

    typedef std::pair<TimeStamp,Timer*> Entry;

    std::set<Entry> activeTimers_;
//    std::queue<Timer*> cancelingTimers_;

    int timerfd_;
    EventLoop* loop_;
    Channel channel_;
    TimeStamp expiration_;
};


};




#endif
