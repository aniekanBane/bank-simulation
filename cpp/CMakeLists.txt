cmake_minimum_required(VERSION 3.1.0)
project(Bank-CPP VERSION 2.0.0)

option(BUILD_TESTS "Build tests" ON)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

add_executable(${PROJECT_NAME} src/account.cpp bank.hpp bank.cpp main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
