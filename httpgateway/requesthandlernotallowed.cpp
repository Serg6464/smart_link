#include "requesthandlernotallowed.h"

RequestHandlerNotAllowed::RequestHandlerNotAllowed()
{

}

bool RequestHandlerNotAllowed::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{
    auto& res = response->getResponse();
    res.result(http::status::method_not_allowed);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Не поддерживается";
    return true;
}
