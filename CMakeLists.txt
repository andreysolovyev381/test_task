cmake_minimum_required(VERSION 3.28)
project(test_task)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
if(GTest_FOUND)
    message(STATUS "TESTS: FOUND GTest, including and linking...")
    include_directories(${GTEST_INCLUDE_DIRS})
else()
    message(STATUS "TESTS: NOT FOUND GTest")
endif()

set(EXECUTABLE_NAME test_task)

add_executable(${EXECUTABLE_NAME}
        main.cpp
)

add_compile_options(
        -march=native
        -Wall
        -Werror
        -Wextra
        -Wpedantic
)

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC
        GTest::GTest
)

target_compile_definitions(${EXECUTABLE_NAME}
        PUBLIC
        EXECUTABLE_NAME="${EXECUTABLE_NAME}"
        CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)


