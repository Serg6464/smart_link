cmake_minimum_required(VERSION 3.5)

project(smart_link LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(DOCKER_DIR "${CMAKE_SOURCE_DIR}/docker.dir")
 message(STATUS "Project Root Directory: ${CMAKE_SOURCE_DIR}")

add_subdirectory(httpredirector.plugins)
add_subdirectory(httpredirector)
add_subdirectory(httpgateway)
add_subdirectory(monitor.service)

add_subdirectory(IoC.test)
#add_subdirectory(httpgateway.test)

include(CTest)
enable_testing()
