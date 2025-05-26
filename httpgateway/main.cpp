#include <iostream>
#include <memory>
#include <IoC.h>
#include <ICommand.h>

#include "requesthandlerhead.h"
#include "requesthandlerbad.h"
#include "requesthandlerredirect.h"
#include "requesthandlernotallowed.h"
#include "httprequest.h"
#include "httpresponse.h"
#include "endpoint.h"

#include "httpconnection.h"
#include "httpreadsocketconnection.h"
#include "processpacketcmd.h"


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
        make_container(std::function<std::shared_ptr<HttpConnection>()>( []() {
                boost::asio::io_context io_context;
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
    std::cout << "start waiting request\n";
                std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
                std::shared_ptr<HttpConnection> conn = std::make_shared<HttpConnection>(socket);
                acceptor.accept( conn->socket() );
                return conn;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Request.GetNew",
                make_container(std::function<std::shared_ptr<IHttpRequest>(std::shared_ptr<HttpConnection>)>( [](std::shared_ptr<HttpConnection> conn) {
                        std::shared_ptr<IHttpRequest> req = HttpRequest::Create();
                        std::shared_ptr<IReadableConnection> readconn = std::make_shared<HttpReadSocketConnection>(conn,req);
                        readconn->read();
                        return req;
                    } )))->Execute();
    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.GetHandler",
        make_container(std::function<std::shared_ptr<ChainRequestHandler>()>( []() {
               std::shared_ptr<RequestHandlerHead> headHandler = std::make_shared<RequestHandlerHead>() ;
               std::shared_ptr<RequestHandlerBad> badHandler = std::make_shared<RequestHandlerBad>() ;
               std::shared_ptr<RequestHandlerRedirect> redirectHandler = std::make_shared<RequestHandlerRedirect>() ;
               std::shared_ptr<RequestHandlerNotAllowed> notallowHandler = std::make_shared<RequestHandlerNotAllowed>() ;
               headHandler->setNext(badHandler);
               badHandler->setNext(redirectHandler);
               redirectHandler->setNext(notallowHandler);
                return (std::shared_ptr<ChainRequestHandler>)headHandler;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.Get",
        make_container(std::function<ICommandPtr(std::shared_ptr<HttpConnection>,std::shared_ptr<IHttpRequest>)>( [](std::shared_ptr<HttpConnection> conn, std::shared_ptr<IHttpRequest> req) {
                std::shared_ptr<HttpResponse> resp = std::make_shared<HttpResponse>();
                ICommandPtr cmd = ProcessPacketCmd::Create(conn, req);
                return cmd;
            } )))->Execute();

}
