#define __STDC_FORMAT_MACROS
#include <inttypes.h> 
#undef __STDC_FORMAT_MACROS
#include "TimeStamp.h"
#include <boost/static_assert.hpp>
#include <time.h>
#include <stdio.h>

using namespace bingchen;

BOOST_STATIC_ASSERT(sizeof(TimeStamp) == sizeof(int64_t));

string TimeStamp::toString() const {
    char buf[32] = {0}; 
    int64_t seconds = microSecondsSinceEpoc_ / kMicroSecondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoc_ / kMicroSecondsPerSecond;
    snprintf(buf,sizeof(buf) - 1,"%" PRId64 ".%06" PRId64,seconds,microseconds);
    return buf;
}

string TimeStamp::toFormattedString(bool showMicroSeconds) const {
    char buf[32] = {0};

    time_t seconds = static_cast<time_t>(microSecondsSinceEpoc_ / kMicroSecondsPerSecond);
    struct tm tm_time;
    gmtime_r(&seconds,&tm_time);
    
    if (showMicroSeconds) {
        int microSeconds = static_cast<int>(microSecondsSinceEpoc_ % kMicroSecondsPerSecond);
        snprintf(buf,sizeof(buf) - 1,"%04d%02d%02d %02d:%02d:%02d.%06d",tm_time.tm_year + 1900,
                tm_time.tm_mon + 1,tm_time.tm_mday,tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                microSeconds);
    }
    else {
        snprintf(buf,sizeof(buf) - 1,"%04d%02d%02d %02d:%02d:%02d",tm_time.tm_year + 1900,
                tm_time.tm_mon + 1,tm_time.tm_mday,tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

