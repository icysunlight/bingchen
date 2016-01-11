#include "MutexLock.h"
#include "Thread.h"
#include "TimeStamp.h"

#include <vector>
#include <cstdio>

using namespace bingchen;

const int kCount = 1000;
std::vector<int> g_vec;
MutexLock g_mutex;

void ThreadFun() {
    for (int i = 0 ; i < kCount ; ++i) {
        MutexLockGuard mutexlockguard(g_mutex);
        g_vec.push_back(i);
    }
}

int main() {

    bingchen::TimeStamp start = TimeStamp::now();
    for (int i = 0 ; i < kCount ; ++i) {
        g_vec.push_back(i);
    }
    printf("single thread without lock %lf\n",timeDifference(TimeStamp::now(),start));

    g_vec.clear();
    Thread thread(ThreadFun,"");
    start = TimeStamp::now();
    thread.start();
    thread.join();
    printf("single thread with lock %lf\n",timeDifference(TimeStamp::now(),start));




    return 0;
}
