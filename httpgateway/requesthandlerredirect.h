#ifndef REQUESTHANDLERREDIRECT_H
#define REQUESTHANDLERREDIRECT_H

#include "chainrequesthandler.h"

class RequestHandlerRedirect : public ChainRequestHandler
{
public:
    RequestHandlerRedirect();

    // ChainRequestHandler interface
public:
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response);
};

#endif // REQUESTHANDLERREDIRECT_H
