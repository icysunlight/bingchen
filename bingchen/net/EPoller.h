#ifndef __BINGCHEN_NET_EPOLLER_H_
#define __BINGCHEN_NET_EPOLLER_H_

#include <boost/noncopyable.hpp>
#include <map>
#include <vector>
#include <sys/epoll.h>
#include "EventLoop.h"
#include "Poller.h"

namespace bingchen {

class Channel;


class EPoller 
    : public Poller
{
public:
    EPoller(EventLoop*);
    ~EPoller();
    void poll(int timeout,std::vector<Channel*>& activeChannels);
    void fillChannels(int cntEvents,std::vector<Channel*>& activeChannels);
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

private:
    std::vector<struct epoll_event> epollEvents_;
    std::map<int,Channel*> channelMap_;
    int epollFd_;
};


};

#endif
