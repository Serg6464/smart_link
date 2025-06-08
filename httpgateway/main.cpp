#include <iostream>
#include <memory>
#include <string>
#include <IoC.h>
#include <ICommand.h>

#include "requesthandlerhead.h"
#include "requesthandlerbad.h"
#include "requesthandlerredirect.h"
#include "requesthandlernotallowed.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "endpoint.h"

#include "socketconnection.h"
#include "httpreadconnection.h"
#include "processpacketcmd.h"
#include "httprequestjsonobject.h"
#include "httpredirectorresolverservice.h"


//All logic dependency initialization. 
void IoC_Init();

int main(void)
{
    try
    {
        IoC_Init();

        EndPoint mainLoop;
        mainLoop.Run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}

void IoC_Init()
{

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Connection.GetNew",
        make_container(std::function<std::shared_ptr<SocketConnection>()>( []() {
                boost::asio::io_context io_context;
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
                std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
                std::shared_ptr<SocketConnection> conn = std::make_shared<SocketConnection>(socket);
                acceptor.accept( conn->socket() );
                return conn;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Request.GetNew",
                make_container(std::function<std::shared_ptr<IHttpRequest>(std::shared_ptr<SocketConnection>)>( [](std::shared_ptr<SocketConnection> conn) {
                        std::shared_ptr<IHttpRequest> req = HttpRequest::Create();
                        std::shared_ptr<IReadableConnection> readconn = std::make_shared<HttpReadConnection>(conn,req);
                        readconn->read();
                        return req;
                    } )))->Execute();
    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.GetHandler",
        make_container(std::function<std::shared_ptr<IRequestHandler>()>( []() {
               std::shared_ptr<RequestHandlerHead> headHandler = std::make_shared<RequestHandlerHead>() ;
               std::shared_ptr<RequestHandlerBad> badHandler = std::make_shared<RequestHandlerBad>() ;
               std::shared_ptr<RequestHandlerRedirect> redirectHandler = std::make_shared<RequestHandlerRedirect>() ;
               std::shared_ptr<RequestHandlerNotAllowed> notallowHandler = std::make_shared<RequestHandlerNotAllowed>() ;
               headHandler->setNext(badHandler);
               badHandler->setNext(redirectHandler);
               redirectHandler->setNext(notallowHandler);
                return (std::shared_ptr<IRequestHandler>)headHandler;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.Get",
        make_container(std::function<ICommandPtr(std::shared_ptr<SocketConnection>,std::shared_ptr<IHttpRequest>)>( [](std::shared_ptr<SocketConnection> conn, std::shared_ptr<IHttpRequest> req) {
                std::shared_ptr<HttpResponse> resp = std::make_shared<HttpResponse>();
                ICommandPtr cmd = ProcessPacketCmd::Create(conn, req);
                return cmd;
            } )))->Execute();


    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.GetRedirector",
        make_container(std::function<IRedirectorPtr(std::shared_ptr<IHttpRequest>)>( [](std::shared_ptr<IHttpRequest> req) {
                auto json_request = HttpRequestJsonObject::Create(req);
                IRedirectorPtr res = std::make_shared<HttpRedirectorResolverService>(json_request, "redirector", 8091);
                return res;
            } )))->Execute();

 }
