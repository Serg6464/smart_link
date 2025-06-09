#include "httprequest.h"
#include <boost/beast/core.hpp>

HttpRequest::HttpRequest(std::shared_ptr<http::request<http::string_body> > request)
    :request_(request)
{

}

std::shared_ptr<HttpRequest> HttpRequest::Create()
{
    std::shared_ptr<http::request<http::string_body>> req = std::make_shared<http::request<http::string_body>>();
    return std::make_shared<HttpRequest>(req);
}

std::shared_ptr<http::request<http::string_body> > HttpRequest::getRequest()
{
    return request_;
}



