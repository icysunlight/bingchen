set(net_SRCS
    Channel.cc
    EventLoop.cc
    Poller.cc
    TimerQueue.cc
    Acceptor.cc
    InetAddr.cc
    Socket.cc
    TcpConnection.cc
    TcpServer.cc
    EventLoopThread.cc
    Buffer.cc
    EventLoopThreadPool.cc
    SocketOps.cc
    Connector.cc
  )

add_library(bingchen_net ${net_SRCS})
target_link_libraries(bingchen_net pthread rt bingchen_base)


install(TARGETS bingchen_net DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/bingchen/net)

add_subdirectory(tests)
