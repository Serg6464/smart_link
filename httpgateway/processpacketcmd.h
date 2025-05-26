#ifndef PROCESSPACKETCMD_H
#define PROCESSPACKETCMD_H

#include <ICommand.h>
#include "ihttprequest.h"
#include "httpconnection.h"
#include <memory>

class ProcessPacketCmd : public ICommand
{
    std::shared_ptr<HttpConnection> _connection;
    std::shared_ptr<IHttpRequest> _request;
public:
    ProcessPacketCmd(std::shared_ptr<HttpConnection>,std::shared_ptr<IHttpRequest>);
    static std::shared_ptr<ProcessPacketCmd>Create(std::shared_ptr<HttpConnection>,std::shared_ptr<IHttpRequest>);


    // ICommand interface
public:
    void Execute();
};



#endif // PROCESSPACKETCMD_H
