#ifndef BINGCHEN_BASE_TIMESTAMP
#define BINGCHEN_BASE_TIMESTAMP

#include <string>
#include <sys/time.h>
#include "copyable.h"
#include <boost/operators.hpp>

using std::string;

namespace bingchen {

//时间戳类，用于标记时间，是值语意，可以复制


class TimeStamp : public bingchen::copyable
                , public boost::less_than_comparable<TimeStamp>
{
private:
    int64_t microSecondsSinceEpoc_;
public:
    const static int kMicroSecondsPerSecond = 1000 * 1000;
    
public:
    TimeStamp()
        : microSecondsSinceEpoc_(0)
    {}

    explicit TimeStamp(int64_t microSecondsSinceEpoc)
        : microSecondsSinceEpoc_(microSecondsSinceEpoc)
    {}

    void swap(TimeStamp& that) {
        int64_t tmp = microSecondsSinceEpoc_;
        microSecondsSinceEpoc_ = that.microSecondsSinceEpoc_;
        that.microSecondsSinceEpoc_ = tmp;
    } 

    string toString() const;
    string toFormattedString(bool showMicroSeconds) const;

    bool isInvalid() {
        return microSecondsSinceEpoc_ > 0;
    }

    int64_t microSecondsSinceEpoc() const {
        return microSecondsSinceEpoc_;
    }

    time_t secondsSinceEpoch() {
        return static_cast<time_t>(microSecondsSinceEpoc_ / kMicroSecondsPerSecond);
    }

    static TimeStamp now() {
        struct timeval tv;
        if (-1 == gettimeofday(&tv,NULL))
            return TimeStamp();

        int64_t seconds = tv.tv_sec;
        return TimeStamp(seconds * kMicroSecondsPerSecond + tv.tv_usec);
    }

    static TimeStamp invalid() {
        return TimeStamp();
    }

    bool operator < (const TimeStamp& that) const {
        return microSecondsSinceEpoc_ < that.microSecondsSinceEpoc_;
    }

    bool operator == (const TimeStamp& that) const {
        return microSecondsSinceEpoc_ == that.microSecondsSinceEpoc_;
    }


};

inline double timeDifference(TimeStamp high,TimeStamp low) {
    int64_t diff = high.microSecondsSinceEpoc() - low.microSecondsSinceEpoc();
    return static_cast<double>(diff) / TimeStamp::kMicroSecondsPerSecond;
} 

inline TimeStamp addTime(TimeStamp timestamp,double seconds) {
    int64_t delta = static_cast<int64_t>(seconds) * TimeStamp::kMicroSecondsPerSecond;
    return TimeStamp(TimeStamp::now().microSecondsSinceEpoc() + delta);
}


};





#endif
