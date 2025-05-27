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

#include "httpconnection.h"
#include "httpreadsocketconnection.h"
#include "processpacketcmd.h"
#include "httprequestjsonobject.h"
#include "httpredirectorresolver.h"

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
    std::string json_str = R"(
    {
      "version": "1.0",
      "rules": [
        {
          "name": "Правило для мобильных устройств",
          "conditions": [
            {
              "type": "target",
              "value": "/welcome"
            },
            {
              "type": "user_agent_contain",
              "value": "Mobile"
            },
          ],
          "redirect_url": "https://mobile.example.com",
          }
        },
        {
          "name": "Правило для Chrome до начала рабочего времени",
          "conditions": [
            {
              "type": "user_agent_contain",
              "value": "Chrome"
            },
            {
              "type": "time_of_day_before",
              "value": "08:00:00"
            }
          ],
          "actions": {
            "redirect_url": "https://early.example.com",
          }
        }
      ]
    }
    )";

    JsonPtr jsonRules = std::make_shared<Json>(boost::json::parse(json_str));

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

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.GetRedirector",
        make_container(std::function<IRedirectorPtr(std::shared_ptr<IHttpRequest>)>( [](std::shared_ptr<IHttpRequest> req) {
                auto json_request = HttpRequestJsonObject::Create(req);
                IRedirectorPtr res = std::make_shared<HttpRedirectorResolver>(json_request);
                return res;
            } )))->Execute();

 }
