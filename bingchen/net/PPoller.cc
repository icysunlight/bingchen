#include "PPoller.h"
#include <errno.h>
#include <poll.h>
#include <vector>
#include "../base/logging.h"
#include "Channel.h"

using namespace bingchen;

PPoller::PPoller(EventLoop* loop) 
    : Poller(loop)
{
}
void PPoller::poll(int timeout,std::vector<Channel*>& activeChannels) {
    int cntEvents = ::poll(&*pollfds_.begin(),pollfds_.size(),timeout);
    if (cntEvents > 0) {
        LOG_TRACE << cntEvents << " events happens";
        fillChannels(cntEvents,activeChannels);
    }
    if (cntEvents == 0) {
        LOG_TRACE << "no event happen";
    }
    if (cntEvents < 0) {
        LOG_ERROR << "error happens:" << strerror(errno);
    }
}
void PPoller::fillChannels(int cntEvents,std::vector<Channel*>& activeChannels) {
    activeChannels.clear();
    for (int i = 0 ; i < pollfds_.size() && cntEvents ; ++i) {
        if (pollfds_[i].revents != 0) {
            cntEvents--;
            Channel* channel = channelMap_[pollfds_[i].fd];
            channel->set_revents(pollfds_[i].revents);
            activeChannels.push_back(channel);
            LOG_TRACE << "new event happens at fd " << channel->fd()
                      << " EventLoop : " << CurrentThread::tid();
        }
    } 
}

void PPoller::updateChannel(Channel* channel) {
    if (channel->index() == -1) {
        struct pollfd pfd;
        pfd.fd = channel->fd();
        pfd.events = channel->events();
        pfd.revents = 0;
        pollfds_.push_back(pfd);
        channelMap_[channel->fd()] = channel;
        channel->set_index(pollfds_.size() - 1);
        LOG_TRACE << "new channel added, fd: " << channel->fd()
                  << " EventLoop: " << CurrentThread::tid();
    }
    else {
        pollfds_[channel->index()].events = channel->events();
    }
}

void PPoller::removeChannel(Channel* channel) {
    if (channel->index() == -1) {
        return;
    }
    else {
        int removeIndex = channel->index();
        int endIndex = pollfds_.size() - 1;
        std::swap(pollfds_[endIndex],pollfds_[removeIndex]);
        pollfds_.pop_back();
        LOG_TRACE << "remove channel, fd:" << channel->fd();
    }
}
