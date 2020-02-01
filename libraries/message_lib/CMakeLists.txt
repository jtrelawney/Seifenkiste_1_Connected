cmake_minimum_required(VERSION 3.0)

#include_directories(/home/jconnor/Seifenkiste/network/0_tcp_ip_basic_lib_message_exchange/)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -Wpedantic")
#SET(GCC_COVERAGE_LINK_FLAGS "-pthread")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
message(STATUS "cxx flags = ${CMAKE_CXX_FLAGS}")

set(OPENCV_LIBS "opencv_core" "opencv_highgui" "opencv_imgproc" "opencv_video" "opencv_videoio")
set(PROJECT_LIBS "time_lib" "address_lib" "camera_message_lib" "message_lib" "header_buffer_lib")
message(STATUS "OPENCV_LIBS = ${OPENCV_LIBS}")
message(STATUS "PROJECT_LIBS = ${PROJECT_LIBS}")

project(time_lib)
add_library(time_lib SHARED time_class.cpp)

project(address_lib)
add_library(address_lib SHARED address_class.cpp)
add_executable(ut_address_lib.exe ut_address_lib.cpp)
target_link_libraries (ut_address_lib.exe address_lib)

project(buffer_lib)
add_library(header_buffer_lib SHARED header_buffer.cpp)
add_executable(ut_buffer_lib.exe ut_buffer_lib.cpp)
target_link_libraries (ut_buffer_lib.exe header_buffer_lib)

project(message_lib)
add_library(message_lib SHARED message_class.cpp)

project(camera_message_lib)
add_library(camera_message_lib SHARED camera_message_class.cpp)

project(ut_test_message_lib)
add_executable(ut_message_lib.exe ut_message_lib.cpp)
#target_link_libraries (ut_message_lib.exe message_lib header_buffer_lib address_lib time_lib)
target_link_libraries (ut_message_lib.exe ${PROJECT_LIBS} ${OPENCV_LIBS})



#[[
project(server_tcp_test)
add_library(tcp_server_class SHARED tcp_server_class.cpp)
add_executable(server_tcp_test.exe network__server_test.cpp)
target_link_libraries (server_tcp_test.exe message_lib tcp_server_class tcp_lib)
]]
