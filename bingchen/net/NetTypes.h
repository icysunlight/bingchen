#ifndef __BINGCHEN_NET_NETTYPES_H_
#define __BINGCHEN_NET_NETTYPES_H_

#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>

namespace bingchen {

class TcpConnection;

typedef boost::shared_ptr<TcpConnection> ConnectionPtr;

typedef boost::function<void (const ConnectionPtr&)> ConnectionCb_t;
typedef boost::function<void (const ConnectionPtr&,void*,int)> MessageCb_t;



}


#endif
