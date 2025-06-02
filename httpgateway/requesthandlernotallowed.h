#ifndef REQUESTHANDLERNOTALLOWED_H
#define REQUESTHANDLERNOTALLOWED_H

#include "chainrequesthandler.h"

class RequestHandlerNotAllowed : public ChainRequestHandler
{
public:
    RequestHandlerNotAllowed();

    // ChainRequestHandler interface
public:
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response);
};



#endif // REQUESTHANDLERNOTALLOWED_H
