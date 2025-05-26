cmake_minimum_required(VERSION 3.5)

project(smart_link LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(httpgateway)


add_subdirectory(IoC.test)

include(CTest)
enable_testing()
