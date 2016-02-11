add_executable(test1 test1.cc)
target_link_libraries(test1 bingchen_net)

add_executable(TimerQueue_test TimerQueue_test.cc)
target_link_libraries(TimerQueue_test bingchen_net)

add_executable(EstablishConn_test EstablishConn_test.cc)
target_link_libraries(EstablishConn_test bingchen_net)

add_executable(Buffer_test Buffer_test.cc)
target_link_libraries(Buffer_test bingchen_net)
