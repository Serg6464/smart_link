#include "processpacketcmd.h"
#include <IoC.h>
#include "chainrequesthandler.h"
#include "httpresponse.h"
#include "httpsendconnection.h"

ProcessPacketCmd::ProcessPacketCmd(std::shared_ptr<HttpConnection> connection,std::shared_ptr<IHttpRequest> request)
    :_connection(connection), _request(request)
{
}

std::shared_ptr<ProcessPacketCmd> ProcessPacketCmd::Create(std::shared_ptr<HttpConnection> connection, std::shared_ptr<IHttpRequest> request)
{
    std::shared_ptr<ProcessPacketCmd> cmd = std::make_shared<ProcessPacketCmd>(connection, request);
    return cmd;
}

void ProcessPacketCmd::Execute()
{
    std::shared_ptr<IRequestHandler> handler = IoC::Resolve<std::shared_ptr<IRequestHandler>>("ProcessPacketCmd.GetHandler");
    std::shared_ptr<HttpResponse> response = std::make_shared<HttpResponse>();
    handler->handle(_request, response);
    HttpSendConnection sendconnection(_connection, response);
    sendconnection.send();
}
