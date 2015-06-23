project(video_analyzer)
cmake_minimum_required(VERSION 2.8)
include_directories(include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenCV REQUIRED)
find_package(Tesseract)

set(CMAKE_CXX_FLAGS "-std=c++0x")
set(CMAKE_BUILD_TYPE Debug)

# Video Utils Library

set(SOURCES_VIDEOUTILS
    include/video_utils.h
    src/video_utils.cpp)

add_library(videoutils SHARED ${SOURCES_VIDEOUTILS})

# LagDetector Library

set(SOURCES_LAGDETECTOR
    src/lagdetector.cpp
    include/lagdetector.h
    include/laginfo.h
    include/roi.h
    include/video_utils.h)

add_library(lagdetector SHARED ${SOURCES_LAGDETECTOR})

# TextExtractor Library

set(SOURCES_TEXTEXTRACTOR
    src/textextractor.cpp
    include/textextractor.h
    include/video_utils.h)

add_library(textextractor SHARED ${SOURCES_TEXTEXTRACTOR})

# FrameExtractor Library

set(SOURCES_FRAMEEXTRACTOR
    src/frameextractor.cpp
    include/frameextractor.h
    include/video_utils.h)

add_library(frameextractor SHARED ${SOURCES_FRAMEEXTRACTOR})

# FPS Measure Library

set(SOURCES_FPSMEASURER
    src/videofpsmeasurer.cpp
    include/videofpsmeasurer.h
    include/fpsinfo.h
    include/video_utils.h)

add_library(videofpsmeasurer SHARED ${SOURCES_FPSMEASURER})

# Executable file

set(SOURCES_ETSII_TEST
    src/main.cpp
    include/lagdetector.h
    include/etsii_test.h
    include/roi.h
    include/laginfo.h
    include/video_utils.h)

add_executable(etsii_test ${SOURCES_ETSII_TEST})

target_link_libraries(etsii_test videoutils lagdetector frameextractor textextractor videofpsmeasurer ${OpenCV_LIBS} tesseract)
