#ifndef REQUESTHANDLERHEAD_H
#define REQUESTHANDLERHEAD_H

#include "chainrequesthandler.h"

class RequestHandlerHead : public ChainRequestHandler
{
public:
    RequestHandlerHead();

    // ChainRequestHandler interface
public:
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response);
};

#endif // REQUESTHANDLERHEAD_H
