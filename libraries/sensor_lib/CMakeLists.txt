cmake_minimum_required(VERSION 3.0)

#include_directories(/home/jconnor/Seifenkiste/network/0_tcp_ip_basic_lib_message_exchange/)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -Wpedantic")
#SET(GCC_COVERAGE_LINK_FLAGS "-pthread")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
message(STATUS "cxx flags = ${CMAKE_CXX_FLAGS}")


project(sensor_lib)
add_library(camera_lib SHARED sensor_base_class.cpp sensor_camera_class.cpp)
add_executable(ut_sensor_camera.exe ut_sensor_camera.cpp)

target_include_directories(camera_lib PUBLIC "../message_lib") #${message_lib})
target_link_libraries(ut_sensor_camera.exe camera_lib message_lib address_lib time_lib)
target_link_libraries (ut_sensor_camera.exe opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio)
