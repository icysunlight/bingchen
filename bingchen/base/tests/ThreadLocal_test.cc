#include "ThreadLocal.h"
#include "Thread.h"
#include "CurrentThread.h"
#include <cstdio>
#include <string>

using namespace bingchen;

class Test
{
public:
    Test() {
        name_ = "oriName";
        printf("tid:%d\tconstructing...\n",CurrentThread::tid());
    }
    ~Test() {
        printf("tid:%d\tdestructing...\n",CurrentThread::tid());
    }
    void setName(std::string name) {
        name_ = name;
    }
    std::string getName() {
        return name_;
    }
private:
    std::string name_;
};

ThreadLocal<Test> test;

void print() {
    printf("tid:%d\tname:%s\n",CurrentThread::tid(),test.value().getName().c_str());
}

void ThreadFunc() {
    print();
    test.value().setName("hahaha");
    print();
}

int main() {

    test.value().setName("mainThread");
    print();

    Thread thread(ThreadFunc,"");
    thread.start();
    thread.join();
    print();

    return 0;
}
