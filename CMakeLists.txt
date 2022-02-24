cmake_minimum_required(VERSION 3.1.0)
project(Bank VERSION 0.1.0)

include(CTest)
enable_testing()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(nlohmann_json REQUIRED)
find_package(Boost 1.76.0 REQUIRED COMPONENTS serialization)

set(CMAKE_CXX_STANDARD 11)

include_directories(${BOOST_INCLUDE_DIRS})

add_executable(Bank bank.hpp bank.cpp main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
