project(video_analyzer)
cmake_minimum_required(VERSION 2.8)
include_directories(include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenCV REQUIRED)
find_package(Tesseract)

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_BUILD_TYPE Debug)

# LagDetector Library

set(SOURCES_LAGDETECTOR
    src/lagdetector.cpp
    include/lagdetector.h
    include/laginfo.h
    include/roi.h)

add_library(lagdetector SHARED ${SOURCES_LAGDETECTOR})

# TextExtractor Library

set(SOURCES_TEXTEXTRACTOR
    src/textextractor.cpp
    include/textextractor.h)

add_library(textextractor SHARED ${SOURCES_TEXTEXTRACTOR})

# FrameExtractor Library

set(SOURCES_FRAMEEXTRACTOR
    src/frameextractor.cpp
    include/frameextractor.h)

add_library(frameextractor SHARED ${SOURCES_FRAMEEXTRACTOR})

# Executable file

set(SOURCES_ETSII_TEST
    src/main.cpp
    include/lagdetector.h
    include/etsii_test.h
    include/roi.h
    include/laginfo.h)

add_executable(etsii_test ${SOURCES_ETSII_TEST})

target_link_libraries(etsii_test lagdetector frameextractor textextractor ${OpenCV_LIBS} tesseract)
