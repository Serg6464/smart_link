#include "requesthandlerbad.h"

RequestHandlerBad::RequestHandlerBad()
{

}


bool RequestHandlerBad::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{
    if (request->getRequest()->method() == http::verb::unknown || request->getRequest()->target().empty()) {
    auto& res = response->getResponse();
    res.result(http::status::bad_request);
    res.set(http::field::content_type, "text/plain");
    res.body() = "Bad Request";
    res.prepare_payload();
    return true;
    }
    return ChainRequestHandler::handle(request, response);
}
