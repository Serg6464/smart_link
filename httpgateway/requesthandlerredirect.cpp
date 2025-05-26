#include "requesthandlerredirect.h"

RequestHandlerRedirect::RequestHandlerRedirect()
{

}


bool RequestHandlerRedirect::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{
    if (request->getRequest()->method() == http::verb::get) {
    auto& res = response->getResponse();
    res.result(http::status::temporary_redirect);
    res.set(http::field::location, "http://www.ya.ru");
    res.set(http::field::content_type, "text/plain");
    res.body() = "Redirect";
    res.prepare_payload();
    return true;
    }
    return ChainRequestHandler::handle(request, response);
}
