project(video_analyzer)
cmake_minimum_required(VERSION 2.8)
include_directories(include)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++0x")

# LagDetector Library

set(SOURCES_LAGDETECTOR
    src/lagdetector.cpp
    include/lagdetector.h
    include/laginfo.h
    include/roi.h)

add_library(lagdetector SHARED ${SOURCES_LAGDETECTOR})

# Executable file

set(SOURCES_MAIN src/main.cpp include/lagdetector.h)
add_executable(${PROJECT_NAME} ${SOURCES_MAIN})
target_link_libraries(${PROJECT_NAME} lagdetector ${OpenCV_LIBS})
