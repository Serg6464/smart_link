cmake_minimum_required(VERSION 3.5)

project(monitor.service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим Boost и требуемый компонент json
find_package(Boost REQUIRED COMPONENTS json)

add_executable(monitor.service main.cpp
    )

#target_link_libraries( monitor.service
#    
#)

#copy to docker environment
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        "${DOCKER_DIR}/monitor/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
)
