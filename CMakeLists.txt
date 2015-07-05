project(video_analyzer)
cmake_minimum_required(VERSION 2.8)
include_directories(include)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenCV REQUIRED)
find_package(Tesseract)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
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

# PNG Files

file(GLOB PNG_FILES "frames/*.png")
file(COPY ${PNG_FILES} DESTINATION ${CMAKE_BINARY_DIR})

foreach(PNG_FILE_LOOP ${PNG_FILES})
    string(REPLACE "/" ";" STR_LIST ${PNG_FILE_LOOP})
    list(LENGTH STR_LIST len)
    list(REVERSE STR_LIST)
    list(GET STR_LIST 0 PNG_FILE_STRIPPED)
    string(REPLACE ".png" ".o" PNG_OUT_FILE ${PNG_FILE_STRIPPED})
    list(APPEND PNG_OUT_LIST ${PNG_OUT_FILE})
    list(APPEND PNG_COPIED_LIST ${PNG_FILE_STRIPPED})
    add_custom_command(OUTPUT ${PNG_OUT_FILE}
                       COMMAND objcopy --input-format=binary --output-format=binary --output=elf64-x86-64 --binary-architecture i386:x86-64 ${PNG_FILE_STRIPPED} ${PNG_OUT_FILE})
endforeach(PNG_FILE_LOOP)

# Executable file

set(SOURCES_ETSII_TEST
    src/main.cpp
    include/lagdetector.h
    include/etsii_test.h
    include/roi.h
    include/laginfo.h
    include/video_utils.h)


add_executable(etsii_test ${SOURCES_ETSII_TEST} ${PNG_OUT_LIST})
target_link_libraries(etsii_test videoutils lagdetector frameextractor textextractor videofpsmeasurer ${OpenCV_LIBS} tesseract)

add_custom_command(TARGET etsii_test POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_CURRENT_SOURCE_DIR}/frames/
                       $<TARGET_FILE_DIR:etsii_test>
                   )

# Clean files

SET_DIRECTORY_PROPERTIES(PROPERTIES  ADDITIONAL_MAKE_CLEAN_FILES "${PNG_OUT_LIST}")
SET_DIRECTORY_PROPERTIES(PROPERTIES  ADDITIONAL_MAKE_CLEAN_FILES "${PNG_COPIED_LIST}")
