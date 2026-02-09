cmake_minimum_required(VERSION 3.22)

project(otus CXX)
set(TARGET otus_hw4)

include(GNUInstallDirs)

find_package(Threads)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_BUILD_TYPE)

include(GNUInstallDirs)
include(CMakePrintHelpers)

#file(GLOB
#  SRC_FILES
#  src/*.cpp
#)

#add_library(${TARGET} STATIC ${SRC_FILES})
add_library(${TARGET} INTERFACE)
add_library(otus::hw4 ALIAS ${TARGET})

target_include_directories(${TARGET} INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

set_target_properties(
    ${TARGET}
    PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS OFF
)

include(CTest)
add_subdirectory(3rdparty/gtest)
enable_testing()
add_subdirectory(tests)


