cmake_minimum_required(VERSION 3.5)

project(target_contains LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./interface)

function(copy_plugin_to_target_dir target)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            "$<TARGET_PROPERTY:${target},BINARY_DIR>/$<TARGET_FILE_NAME:${target}>"
            "${DOCKER_DIR}/apps/plugins/$<TARGET_FILE_NAME:${target}>"
    )
endfunction(copy_plugin_to_target_dir)

function(newplugin target)
    add_library(${target} SHARED ${target}.cpp)
    set_target_properties(target_contains PROPERTIES
        COMPILE_FLAGS "-fPIC"
    )
    copy_plugin_to_target_dir(${target})
endfunction(newplugin)

newplugin(target_contains)
newplugin(date_before)

