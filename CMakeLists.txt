cmake_minimum_required(VERSION 3.16)
find_package(YARP COMPONENTS os REQUIRED)
add_executable(talker)
target_sources(talker PRIVATE talker.cpp)
target_link_libraries(talker PRIVATE YARP::YARP_os
                                     YARP::YARP_init)
