cmake_minimum_required(VERSION 3.12)

enable_testing()
add_subdirectory(googletest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(path_test ${CMAKE_CURRENT_SOURCE_DIR}/src/path_test.cpp)
target_include_directories(path_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(path_test PUBLIC gtest_main)

add_executable(utility_test ${CMAKE_CURRENT_SOURCE_DIR}/src/utility_test.cpp)
target_include_directories(utility_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(utility_test PUBLIC gtest_main)

add_executable(config_test ${CMAKE_CURRENT_SOURCE_DIR}/src/config_test.cpp)
target_include_directories(config_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(config_test PUBLIC gtest_main)

add_test(
    NAME PathTest
    COMMAND path_test
)
add_test(
    NAME UtilityTest
    COMMAND utility_test
)
add_test(
    NAME ConfigTest
    COMMAND config_test
)
