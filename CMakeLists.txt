project(video_analyzer)
cmake_minimum_required(VERSION 2.8)
include_directories(include)
find_package(OpenCV REQUIRED)
set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_BUILD_TYPE Debug)

# LagDetector Library

set(SOURCES_LAGDETECTOR
    src/lagdetector.cpp
    include/lagdetector.h
    include/laginfo.h
    include/roi.h)

add_library(lagdetector SHARED ${SOURCES_LAGDETECTOR})

# Executable file

set(SOURCES_ETSII_TEST
    src/main.cpp
    include/lagdetector.h
    include/etsii_test.h
    include/roi.h
    include/laginfo.h)

add_executable(etsii_test ${SOURCES_ETSII_TEST})
target_link_libraries(etsii_test lagdetector ${OpenCV_LIBS})
