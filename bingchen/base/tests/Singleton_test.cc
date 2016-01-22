#include "Singleton.h"
#include "CurrentThread.h"
#include "Thread.h"
#include <string>
#include <cstdio>
#include <boost/bind.hpp>

class Test {
private:
    std::string name_;
public:
    void setName(std::string newName) {name_ = newName;}
    std::string getName() {return name_;}
};

void ThreadFunc() {
    bingchen::Singleton<Test> test;
    printf("tid:%d\toriName:%s\n",bingchen::CurrentThread::tid(),test.Instance().getName().c_str());
    test.Instance().setName("ThreadFunc");
    printf("tid:%d\tnewName:%s\n",bingchen::CurrentThread::tid(),test.Instance().getName().c_str());
}

int main() {
    
    bingchen::Singleton<Test> test;
    test.Instance().setName("mainThread");
    bingchen::Thread thread(ThreadFunc,"123");
    thread.start();
    thread.join();

    printf("tid:%d\tname:%s\n",bingchen::CurrentThread::tid(),test.Instance().getName().c_str());
    return 0;
}
