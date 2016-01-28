#include "Poller.h"
#include <errno.h>
#include <poll.h>
#include <vector>
#include "../base/logging.h"
#include "Channel.h"

using namespace bingchen;

Poller::Poller(EventLoop* loop) 
    : loop_(loop)
{
}
void Poller::poll(int timeout,std::vector<Channel*>& activeChannels) {
    int cntEvents = ::poll(&*pollfds_.begin(),pollfds_.size(),timeout);
    if (cntEvents > 0) {
        LOG_TRACE << "some events happens";
        fillChannels(cntEvents,activeChannels);
    }
    if (cntEvents == 0) {
        LOG_TRACE << "no event happen";
    }
    if (cntEvents < 0) {
        LOG_ERROR << "error happens:" << strerror(errno);
    }
}
void Poller::fillChannels(int cntEvents,std::vector<Channel*>& activeChannels) {
   for (int i = 0 ; i < pollfds_.size() && cntEvents ; ++i) {
       if (pollfds_[i].revents != 0) {
           cntEvents--;
           Channel* channel = channelMap_[pollfds_[i].fd];
           channel->set_revents(pollfds_[i].revents);
           activeChannels.push_back(channel);
       }
   } 
}

void Poller::updateChannel(Channel* channel) {
    if (channel->index() == -1) {
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = channel->events();
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        channelMap_[channel->fd()] = channel;
        channel->set_index(pollfds_.size() - 1);
    }
    else {
        pollfds_[channel->index()].events = channel->events();
    }
}