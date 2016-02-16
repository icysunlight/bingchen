#include "Poller.h"
#include <errno.h>
#include <vector>
#include "../base/logging.h"
#include "Channel.h"

using namespace bingchen;

Poller::Poller(EventLoop* loop) 
    : loop_(loop)
{
}
