#ifndef __BINGCHEN_NET_PPOLLER_H_
#define __BINGCHEN_NET_PPOLLER_H_

#include <boost/noncopyable.hpp>
#include <map>
#include <vector>
#include <poll.h>
#include "EventLoop.h"
#include "Poller.h"

namespace bingchen {

class Channel;


class PPoller 
    : boost::noncopyable,
      public Poller
{
public:
    PPoller(EventLoop*);
    void poll(int timeout,std::vector<Channel*>& activeChannels);
    void fillChannels(int cntEvents,std::vector<Channel*>& activeChannels);
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

private:
    std::vector<struct pollfd> pollfds_;
    std::map<int,Channel*> channelMap_;
};


};

#endif
