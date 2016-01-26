#include "ThreadLocalSingleton.h"
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
    printf("tid:%d\toriName:%s\n",bingchen::CurrentThread::tid(),bingchen::ThreadLocalSingleton<Test>::Instance().getName().c_str());
    bingchen::ThreadLocalSingleton<Test>::Instance().setName("ThreadFunc");
    printf("tid:%d\tnewName:%s\n",bingchen::CurrentThread::tid(),bingchen::ThreadLocalSingleton<Test>::Instance().getName().c_str());
}

int main() {
    
    bingchen::ThreadLocalSingleton<Test>::Instance().setName("mainThread");
    bingchen::Thread thread(ThreadFunc,"123");
    thread.start();
    thread.join();

    printf("tid:%d\tname:%s\n",bingchen::CurrentThread::tid(),bingchen::ThreadLocalSingleton<Test>::Instance().getName().c_str());
    return 0;
}
