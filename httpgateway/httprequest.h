#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "ihttprequest.h"
#include <memory>

class HttpRequest : public IHttpRequest
{
private:
 std::shared_ptr<http::request<http::string_body>> request_;

public:
    HttpRequest(std::shared_ptr<http::request<http::string_body>> request);;
    static std::shared_ptr<HttpRequest> Create();;

    // IHttpRequest interface
public:
    std::shared_ptr<http::request<http::string_body>> getRequest();;

};

#endif // HTTPREQUEST_H
