cmake_minimum_required(VERSION 3.5)

project(target_contains LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./interface)
#include_directories(../json)

add_library(target_contains SHARED target_contains.cpp
    )


# Установка флагов компиляции
set_target_properties(target_contains PROPERTIES
    COMPILE_FLAGS "-fPIC"
)

add_library(date_before SHARED date_before.cpp
    )

set_target_properties(date_before PROPERTIES
    COMPILE_FLAGS "-fPIC"
)


# include(GNUInstallDirs)
# install(TARGETS httpgateway
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
