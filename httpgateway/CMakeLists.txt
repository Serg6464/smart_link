cmake_minimum_required(VERSION 3.5)

project(httpgateway LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Находим Boost и требуемый компонент json
find_package(Boost REQUIRED COMPONENTS json)


include_directories(../IoC)
include_directories(../exceptions)
include_directories(../interface)
include_directories(../commands)
include_directories(../json)
include_directories(.)

add_executable(httpgateway main.cpp
    ihttprequest.h
    ihttpresponse.h
    httprequest.h httprequest.cpp
    httpresponse.h
    chainrequesthandler.h

    requesthandlerhead.h requesthandlerhead.cpp
    requesthandlerbad.h requesthandlerbad.cpp
    requesthandlerredirect.h requesthandlerredirect.cpp
    endpoint.h endpoint.cpp
    socketconnection.h
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
    processpacketcmd.h processpacketcmd.cpp
    requesthandlernotallowed.h requesthandlernotallowed.cpp
    ireadableconnection.h
    isendableconnection.h
    httpreadconnection.h
    httpsendconnection.h
    httprequestjsonobject.h httprequestjsonobject.cpp
    ../json/boostjsonobject.h
#-------------------
    ijsonobject.h
    irequesthandler.h
    ../commands/MacroCommand.cpp ../commands/MacroCommand.h
    ../exceptions/CommandException.cpp ../exceptions/CommandException.h
    httpredirectorresolverservice.h httpredirectorresolverservice.cpp
    )

target_link_libraries( httpgateway
    Boost::json
)

# include(GNUInstallDirs)
# install(TARGETS httpgateway
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
