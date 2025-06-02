#ifndef REQUESTHANDLERBAD_H
#define REQUESTHANDLERBAD_H

#include "chainrequesthandler.h"

class RequestHandlerBad : public ChainRequestHandler
{
public:
    RequestHandlerBad();

    // ChainRequestHandler interface
public:
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response);
};

#endif // REQUESTHANDLERBAD_H
