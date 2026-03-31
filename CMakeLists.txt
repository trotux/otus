cmake_minimum_required(VERSION 3.22)

project(otus CXX)
set(TARGET otus_hw)

include(GNUInstallDirs)

find_package(Threads)

set (CMAKE_POSITION_INDEPENDENT_CODE ON)
if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE RelWithDebInfo)
endif (NOT CMAKE_BUILD_TYPE)

include(GNUInstallDirs)
include(CMakePrintHelpers)

include(FetchContent)

FetchContent_Declare(
  json 
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(json)

file(GLOB
  SRC_FILES
  src/*.cpp
  src/engine/*.cpp
)

add_library(${TARGET} STATIC ${SRC_FILES})
add_library(otus::hw ALIAS ${TARGET})

target_include_directories(${TARGET} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_include_directories(${TARGET} PUBLIC ${CMAKE_SOURCE_DIR}/3rdparty/cpp-httplib/include)

target_link_libraries(
    ${TARGET}
    PUBLIC
    pthread
    nlohmann_json::nlohmann_json
)

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


