set(test_name "tests_hw4")

add_executable(${test_name}
    ${CMAKE_SOURCE_DIR}/tests/CheckFuelCommandTest.cpp
    ${CMAKE_SOURCE_DIR}/tests/BurnFuelCommandTest.cpp
)

target_link_libraries(${test_name}
    gtest_main
    otus::hw4
)

set_target_properties(
    ${test_name}
    PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS OFF
)

add_test(NAME ${test_name} COMMAND ${test_name})
