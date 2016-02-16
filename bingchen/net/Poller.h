#ifndef __BINGCHEN_NET_POLLER_H_
#define __BINGCHEN_NET_POLLER_H_

#include <boost/noncopyable.hpp>
#include <vector>
#include "EventLoop.h"

namespace bingchen {

class Channel;

class Poller 
    : boost::noncopyable
{
public:
    Poller(EventLoop*);
    virtual void poll(int timeout,std::vector<Channel*>& activeChannels) = 0;
    virtual void fillChannels(int cntEvents,std::vector<Channel*>& activeChannels) = 0;
    virtual void updateChannel(Channel* channel) = 0;
    virtual void removeChannel(Channel* channel) = 0;

protected:
    EventLoop* loop_;
};


};

#endif
