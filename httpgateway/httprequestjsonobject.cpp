#include "httprequestjsonobject.h"
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/json.hpp>
#include <iostream>
#include <string>

namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;


HttpRequestJsonObject::HttpRequestJsonObject(std::shared_ptr<IHttpRequest> request)
    :_request(request)
{

}

std::shared_ptr<HttpRequestJsonObject> HttpRequestJsonObject::Create(std::shared_ptr<IHttpRequest> request)
{
    return std::make_shared<HttpRequestJsonObject>(request);
}

JsonPtr HttpRequestJsonObject::getJson()
{
    boost::json::object result;
    std::shared_ptr<http::request<http::string_body>> req = _request->getRequest();

    // Базовый метод, путь и версия
    result["method"] = req->method_string();
    result["target"] = req->target();
    result["version"] = req->version();

    // Заголовки
    boost::json::object headers;
    for (auto& h : req->base()) {
        headers[h.name_string()] = h.value();
    }

    result["headers"] = std::move(headers);

    // Тело запроса
    if (!req->body().empty()) {
        result["body"] = req->body();
    }

    return std::make_shared<Json>(result);
}
