#ifndef CHAINREQUESTHANDLER_H
#define CHAINREQUESTHANDLER_H

#include "irequesthandler.h"
#include <memory>

class ChainRequestHandler:public IRequestHandler
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
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
    {
        if (next_ != nullptr) {
            return next_->handle(request, response);
        }
        return false;
    };

};

#endif // CHAINREQUESTHANDLER_H
