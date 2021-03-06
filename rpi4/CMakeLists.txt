cmake_minimum_required(VERSION 3.0)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

message(STATUS "\n\nBuilding RPI4 project")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dirs/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY = ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message(STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY = ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

project(rpi4)

set(OPENCV_LIBS "opencv_core" "opencv_highgui" "opencv_imgproc" "opencv_video" "opencv_videoio")
set(PROJECT_LIBS "camera_lib" "camera_message_lib" "message_lib" "header_buffer_lib" "address_lib" "time_lib")

#rpi4_main

include_directories(/usr/local/include/opencv4)
add_executable(rpi4_main.exe rpi4_main.cpp)

target_include_directories(rpi4_main.exe PUBLIC "../libraries/message_lib")
target_include_directories(rpi4_main.exe PUBLIC "../libraries/sensor_lib")
target_link_libraries (rpi4_main.exe ${PROJECT_LIBS} ${OPENCV_LIBS})


#target_link_libraries (rpi4_main.exe opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio)



#[[
set_target_properties( rpi4_main.exe
  PROPERTIES
  #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  #LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../dirs/bin"
)
]]

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -pthread -O2 -g")
#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -fsanitize=thread -pthread -O2 -g")

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_FLAGS}")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
message(STATUS "cxx compile flags = ${CMAKE_CXX_FLAGS}")


#target_include_directories(src PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")#/../dirs)

#message(STATUS "src = ${src}")


#add_subdirectory(pc_cockpit)


#[[
#SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -pthread -O2 -g")
SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -pedantic -Wextra -Werror -fsanitize=thread -pthread -O2 -g")

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_ADDITIONAL_FLAGS}")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
message(STATUS "cxx compile flags = ${CMAKE_CXX_FLAGS}")

SET(GCC_COVERAGE_LINK_FLAGS "-lpthread")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
message(STATUS "cxx link flags = ${CMAKE_EXE_LINKER_FLAGS}")

set(GENERAL_LIBS rt)

project(pc_cockpit)
add_executable(pc_main.exe pc_main.cpp)



project(test_streamer)

set(PROJECT_PATH "~/home/ethan/projects/Seifenkiste_1")
set(DIR_COMMON ${PROJECT_PATH}/common)
set(DIR_PC ${PROJECT_PATH}/PC_cockpit_1)
set(DIR_DEV_TEST ${DIR_PC}/dev_tests)
set(DIR_MAIN ${DIR_PC}/src)

message ("\n using the following source and lib directories :\n")
message (${DIR_COMMON} "\n")
message (${DIR_PC} "\n")
message (${DIR_DEV_TEST} "\n")
message (${DIR_MAIN} "\n")



SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall -Werror")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)


set(PROJECT_SOURCES stream_rpi_camera/stream_rpi_camera.cpp)
add_executable(streamer PRIVATE ${PROJECT_SOURCES} )


# how many dires above does the project start

target_include_directories( streamer ${DIR_COMMON} )

add_library(tcp_server SHARED ../tcp_server/tcp_server.cpp)
add_library(message_class SHARED ../../common/message_class.cpp)
add_library(common_stuff SHARED ../../common/defs.cpp)


set(OPENCV_LIBS opencv_core opencv_highgui opencv_imgproc opencv_video opencv_videoio)
set(MY_LIBS tcp_server message_class common_stuff)
set(PROJECT_LIBS ${OPENCV_LIBS} ${MY_LIBS})
message ("\n\nsetting libraries as :\n" ${PROJECT_LIBS} "\n")


#target_link_libraries(streamer tcp_server)
#target_link_libraries(streamer message_class)
#target_link_libraries(streamer common_stuff)
target_link_libraries (streamer ${PROJECT_LIBS})

]]
