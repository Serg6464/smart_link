#include "endpoint.h"
#include <IoC.h>

#include "socketconnection.h"
#include <ijsonobject.h>
#include <ICommand.h>

#include <iostream>

#include <boost/json.hpp>

using Json = boost::json::value;
using JsonPtr = std::shared_ptr<Json>;

EndPoint::EndPoint()
{

}

void EndPoint::Run()
{
    bool stop = 0;


    while( !stop )
    {
        auto conn = IoC::Resolve<std::shared_ptr<SocketConnection>>("Connection.GetNew");
        auto request = IoC::Resolve<IJsonObjectPtr>("Request.GetNew",conn);

        auto cmd = IoC::Resolve<ICommandPtr>("ProcessPacketCmd.Get", conn, request);
        //Запустить обработку пакета
        cmd->Execute();
    }
}
