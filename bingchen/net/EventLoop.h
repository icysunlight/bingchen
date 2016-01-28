#ifndef __BINGCHEN_NET_EVENTLOOP_H_
#define __BINGCHEN_NET_EVENTLOOP_H_

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>
#include <pthread.h>


namespace bingchen {

class Channel;
class Poller;

class EventLoop
    : boost::noncopyable
{
public:
    
    EventLoop();
    ~EventLoop();

    void loop();
    bool isInLoopThread();
    void updateChannel(Channel*);
    void quit();
    static void getThreadEventLoop();

private:

    pid_t threadId_;
    bool running_;
    boost::scoped_ptr<Poller> poller_;
    std::vector<Channel*> activeChannels_;
    bool quit_;
};

};

#endif
