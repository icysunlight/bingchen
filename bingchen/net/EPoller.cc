#include "EPoller.h"
#include <errno.h>
#include <vector>
#include "../base/logging.h"
#include "Channel.h"

using namespace bingchen;

EPoller::EPoller(EventLoop* loop) 
    : Poller(loop),
      epollFd_(::epoll_create(0))
{

}

void EPoller::poll(int timeout,std::vector<Channel*>& activeChannels) {
    int cntEvents = ::epoll_wait(epollFd_,&*epollEvents_.begin(),epollEvents_.size(),timeout);
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

void EPoller::fillChannels(int cntEvents,std::vector<Channel*>& activeChannels) {
    activeChannels.clear();
    for (int i = 0 ; i < epollEvents_.size() ; ++i) {
            Channel* channel = static_cast<Channel*>(epollEvents_[i].data.ptr);
            channel->set_revents(epollEvents_[i].events);
            activeChannels.push_back(channel);
            LOG_TRACE << "new event happens at fd " << channel->fd()
                      << " EventLoop : " << CurrentThread::tid();
    } 
}

void EPoller::updateChannel(Channel* channel) {
    if (channel->index() == -1) {
        struct epoll_event pEvent;
        pEvent.data.ptr = channel;
        pEvent.events = channel->events();
        ::epoll_ctl(epollFd_,EPOLL_CTL_ADD,channel->fd(),&pEvent);
        epollEvents_.push_back(pEvent);
        channel->set_index(epollEvents_.size() - 1);
        LOG_TRACE << "new channel added, fd: " << channel->fd()
                  << " EventLoop: " << CurrentThread::tid();
    }
    else {
        struct epoll_event pEvent;
        pEvent.data.ptr = channel;
        pEvent.events = channel->events();
        ::epoll_ctl(epollFd_,EPOLL_CTL_MOD,channel->fd(),&pEvent);
    }
}

void EPoller::removeChannel(Channel* channel) {
    if (channel->index() == -1) {
        return;
    }
    else {
        struct epoll_event pEvent;
        pEvent.data.ptr = channel;
        pEvent.events = channel->events();
        ::epoll_ctl(epollFd_,EPOLL_CTL_DEL,channel->fd(),&pEvent);
        channel->set_index(-1);
        epollEvents_.pop_back();
        LOG_TRACE << "remove channel, fd:" << channel->fd();
    }
}
