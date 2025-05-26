#include "endpoint.h"
#include <IoC.h>

#include "httprequest.h"
#include "httpconnection.h"
#include <ICommand.h>

#include <iostream>

EndPoint::EndPoint()
{

}

void EndPoint::Run()
{
    bool stop = 0;


    while( !stop )
    {
        auto conn = IoC::Resolve<std::shared_ptr<HttpConnection>>("Connection.GetNew");
        auto request = IoC::Resolve<std::shared_ptr<IHttpRequest>>("Request.GetNew",conn);

        std::cout << *(request->getRequest()) << std::endl;
        auto cmd = IoC::Resolve<ICommandPtr>("ProcessPacketCmd.Get", conn, request);
        //Запустить обработку пакета
        cmd->Execute();
    }
}
