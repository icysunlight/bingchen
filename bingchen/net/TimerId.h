#ifndef __BINGCHEN_NET_TIMERID_H_
#define __BINGCHEN_NET_TIMERID_H_

#include "Timer.h"

namespace bingchen {


class TimerId {
public:

    TimerId(Timer* timer)
        : timer_(timer)
    {}

    bool valid() {
        return timer_ != NULL;
    }

    friend class TimerQueue;

private:
    Timer* timer_;

};

};




#endif
