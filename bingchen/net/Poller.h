#ifndef __BINGCHEN_NET_POLLER_H_
#define __BINGCHEN_NET_POLLER_H_

#include <boost/noncopyable.hpp>
#include <map>
#include <vector>
#include <poll.h>
#include "EventLoop.h"

namespace bingchen {

class Channel;


class Poller 
    : boost::noncopyable
{
public:
    Poller(EventLoop*);
    void poll(int timeout,std::vector<Channel*>& activeChannels);
    void fillChannels(int cntEvents,std::vector<Channel*>& activeChannels);
    void updateChannel(Channel* channel);

private:
    std::vector<struct pollfd> pollfds_;
    std::map<int,Channel*> channelMap_;
    EventLoop* loop_;
};


};

#endif
