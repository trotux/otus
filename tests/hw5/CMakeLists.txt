set(test_name "tests_hw5")

add_executable(${test_name}
    ${CMAKE_CURRENT_SOURCE_DIR}/IoCTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DelegateTest.cpp
)

target_link_libraries(${test_name}
    gtest_main
    otus::hw
)

target_include_directories(${test_name} PUBLIC ${CMAKE_SOURCE_DIR}/tests)

set_target_properties(
    ${test_name}
    PROPERTIES
    CXX_STANDARD 23
    CXX_EXTENSIONS OFF
)

add_test(NAME ${test_name} COMMAND ${test_name})
