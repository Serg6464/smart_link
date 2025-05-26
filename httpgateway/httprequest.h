#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "ihttprequest.h"
#include <memory>

class HttpRequest : public IHttpRequest
{
private:
 std::shared_ptr<http::request<http::string_body>> request_;

public:
    HttpRequest(const std::string& raw_request);
    HttpRequest(std::shared_ptr<http::request<http::string_body>> request)
        :request_(request)
    {

    };
    static std::shared_ptr<HttpRequest> Create()
    {
        std::shared_ptr<http::request<http::string_body>> req = std::make_shared<http::request<http::string_body>>();
        return std::make_shared<HttpRequest>(req);
    };

    // IHttpRequest interface
public:
    std::shared_ptr<http::request<http::string_body>> getRequest()
    {
        return request_;
    };

};

#endif // HTTPREQUEST_H
