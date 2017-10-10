cmake_minimum_required(VERSION 3.8)
project(SIFT_oneway)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenCV REQUIRED)
set(SOURCE_FILES main.cpp sift.h sift_function.cpp)
add_executable(SIFT_oneway ${SOURCE_FILES})
target_link_libraries( SIFT_oneway ${OpenCV_LIBS} )