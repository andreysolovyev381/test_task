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

set(EXECUTABLE_NAME tse_tests)

add_executable(${EXECUTABLE_NAME}
        main.cpp
)

target_include_directories(${EXECUTABLE_NAME}
        PUBLIC
)

target_link_directories(${EXECUTABLE_NAME}
        PUBLIC
)

target_link_libraries(${EXECUTABLE_NAME}
        PUBLIC
        GTest::GTest
        pthread
)
target_compile_definitions(${EXECUTABLE_NAME}
        PUBLIC
        EXECUTABLE_NAME="${EXECUTABLE_NAME}"
        CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)


