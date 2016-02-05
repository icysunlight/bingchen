#ifndef __BINGCHEN_NET_TIMER_H_
#define __BINGCHEN_NET_TIMER_H_

#include "../base/TimeStamp.h"
#include <boost/function.hpp>
#include <cmath> 

namespace bingchen { 
class Timer 
{
public:
    Timer(TimeStamp expiration,double interval,const boost::function<void ()>& cb)
        : expiration_(expiration),
          interval_(interval),
          repeat_(fabs(interval) > 1e-6),
          cb_(cb)
    {}

    void run() {
        cb_();
    }

    void restart() {
        expiration_ = addTime(TimeStamp::now(),interval_);
    }
    
    bool repeat() {
        return repeat_;
    }

    TimeStamp expiration() {
        return expiration_;
    }

private:
    TimeStamp expiration_;
    const boost::function<void ()> cb_;
    bool repeat_;
    double interval_;

};



};



#endif
