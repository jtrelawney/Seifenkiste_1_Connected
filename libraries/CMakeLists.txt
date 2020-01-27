cmake_minimum_required(VERSION 3.0)

message(STATUS "\n\nBuilding library project")


# set the required paths
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/unit_tests)

include_directories(/usr/local/include/opencv4)

add_subdirectory(message_lib)

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")

message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")


# the the flags
#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -pthread -O2 -g")
#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -fsanitize=thread -pthread -O2 -g")
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror")
#SET(GCC_COVERAGE_LINK_FLAGS "-pthread")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
message(STATUS "cxx flags = ${CMAKE_CXX_FLAGS}")

#[[
# set the project
project(all_libs)

add_library(camera_lib SHARED sensor_base_class.cpp sensor_camera_class.cpp)
add_executable(ut_sensor_camera.exe ut_sensor_camera.cpp)

target_include_directories(camera_lib PUBLIC "./message_lib") #${message_lib})
target_link_libraries(ut_sensor_camera.exe camera_lib address_lib)
target_link_libraries (ut_sensor_camera.exe opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio)
]]

#[[
#include_directories(/usr/local/include/opencv4)
add_library(message_lib SHARED message_class.cpp)
add_library(camera_message_lib SHARED message_camera_class.cpp)
target_link_libraries(camera_message_lib message_lib)
add_library(tcp_lib SHARED tcp_lib.cpp)
add_library(tcp_client_lib SHARED tcp_client_class.cpp)
add_library(tcp_server_lib SHARED tcp_server_class.cpp)
add_executable(client_network_test.exe network_client_test.cpp)
add_executable(server_network_test.exe network_server_test.cpp)
target_link_libraries (client_network_test.exe camera_message_lib message_lib tcp_client_lib tcp_lib)
target_link_libraries (server_network_test.exe camera_message_lib message_lib tcp_server_lib tcp_lib)
#target_link_libraries (create_mat.exe opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio)
]]

#[[

set_target_properties( all_libs
  PROPERTIES
  #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
)

get_target_property(out1 tcp_lib LIBRARY_OUTPUT_DIRECTORY)
message(STATUS "LIBRARY_OUTPUT_DIRECTORY = ${out1}")

get_target_property(out1 tcp_lib RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "RUNTIME_OUTPUT_DIRECTORY = ${out1}")




SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../dirs/bin")

project(tcp_lib)
add_library(tcp_lib SHARED tcp_lib.cpp)

project(message_lib)
add_library(message_lib SHARED message_class.cpp)

project(client_tcp_test)
add_library(tcp_client_class SHARED tcp_client_class.cpp)
add_executable(client_tcp_test.exe network__client_test.cpp)
target_link_libraries (client_tcp_test.exe message_lib tcp_client_class tcp_lib)

project(server_tcp_test)
add_library(tcp_server_class SHARED tcp_server_class.cpp)
add_executable(server_tcp_test.exe network__server_test.cpp)
target_link_libraries (server_tcp_test.exe message_lib tcp_server_class tcp_lib)

]]
