set(base_SRCS
  Exception.cc
  TimeStamp.cc
  Thread.cc
  ThreadPool.cc
  logging.cc
  logstream.cc
  )

add_library(bingchen_base ${base_SRCS})
target_link_libraries(bingchen_base pthread rt)


install(TARGETS bingchen_base DESTINATION lib)

file(GLOB HEADERS "*.h")
install(FILES ${HEADERS} DESTINATION include/bingchen/base)

if(NOT CMAKE_BUILD_NO_EXAMPLES)
  add_subdirectory(tests)
endif()
