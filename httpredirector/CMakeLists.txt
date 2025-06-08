cmake_minimum_required(VERSION 3.5)

project(httpredirector LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим Boost и требуемый компонент json
find_package(Boost REQUIRED COMPONENTS json)

include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../commands)
include_directories(../httpgateway)
include_directories(../json)

add_executable(httpredirector main.cpp
    endpoint.h endpoint.cpp
    ../IoC/IoC.cpp ../IoC/IoC.h
    ../IoC/IocNewScopeCommand.cpp ../IoC/IocNewScopeCommand.h
    ../IoC/IocRegisterCommand.cpp ../IoC/IocRegisterCommand.h
    ../IoC/IocSetScopeAbsoluteCommand.cpp ../IoC/IocSetScopeAbsoluteCommand.h
    ../IoC/IocSetScopeRelativeCommand.cpp ../IoC/IocSetScopeRelativeCommand.h
    ../IoC/IResolverCollection.h ../IoC/IResolverContainer.h
    ../IoC/IScope.h ../IoC/IScopeChanger.h
    ../IoC/ResolverCollection.cpp ../IoC/ResolverCollection.h
    ../IoC/ResolverContainer.h
    ../IoC/Scope.cpp ../IoC/Scope.h
    ../IoC/ScopeChangerAdapter.cpp ../IoC/ScopeChangerAdapter.h
    ../IoC/ScopeContainer.cpp ../IoC/ScopeContainer.h
    ../exceptions/RuntimeError.cpp ../exceptions/RuntimeError.h
    ../commands/FallbackCommand.cpp ../commands/FallbackCommand.h
    ../exceptions/InvalidArgument.cpp ../exceptions/InvalidArgument.h
    jsonreadconnection.h
    jsonsendconnection.h
    ../json/boostjsonobject.h
    resolveredirectioncommand.h resolveredirectioncommand.cpp
    httpredirectorresolver.h httpredirectorresolver.cpp
    checkconditioncommand.h checkconditioncommand.cpp
    irules.h
    ruleshandler.h ruleshandler.cpp
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h
    ../exceptions/CommandException.cpp ../exceptions/CommandException.h
    sendnewlocationcommand.h
    conditiontarget.h
    plugindllcondition.h plugindllcondition.cpp
    config/redirection_rules.json
    )

target_link_libraries( httpredirector
    Boost::json
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/config
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/config
)

#copy to docker environment
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "$<TARGET_PROPERTY:${PROJECT_NAME},BINARY_DIR>/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
        "${DOCKER_DIR}/apps/$<TARGET_FILE_NAME:${PROJECT_NAME}>"
)
add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/config
    "${DOCKER_DIR}/apps/config"
)
