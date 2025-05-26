#include "requesthandlerhead.h"

RequestHandlerHead::RequestHandlerHead()
{

}


bool RequestHandlerHead::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{
    if (request->getRequest()->method() == http::verb::head) {
        auto& res = response->getResponse();
        res.result(http::status::no_content);
        return true;
    }
    return ChainRequestHandler::handle(request, response);
}
