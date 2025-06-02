#ifndef IREQUESTHANDLER_H
#define IREQUESTHANDLER_H

#include "ihttprequest.h"
#include "ihttpresponse.h"

class IRequestHandler
{
public:
    IRequestHandler() = default;
    virtual bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response) = 0;
};

#endif // IREQUESTHANDLER_H
