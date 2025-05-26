#ifndef CHAINREQUESTHANDLER_H
#define CHAINREQUESTHANDLER_H

#include "ihttprequest.h"
#include "ihttpresponse.h"
#include <memory>

class ChainRequestHandler
{
protected:
 std::shared_ptr<ChainRequestHandler> next_;
public:
    ChainRequestHandler():
        next_(nullptr)
    {};

    virtual void setNext(std::shared_ptr<ChainRequestHandler> next)
    {
        next_ = next;
    };
    virtual bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
    {
        if (next_ != nullptr) {
            return next_->handle(request, response);
        }
        return false;
    };

};

#endif // CHAINREQUESTHANDLER_H
