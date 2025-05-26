#ifndef IHTTPREQUEST_H
#define IHTTPREQUEST_H

#include <boost/beast/http.hpp>
#include <memory>

namespace http = boost::beast::http;

class IHttpRequest
{
public:
    //virtual const http::request<http::string_body>& getRequest() const = 0;
    virtual std::shared_ptr<http::request<http::string_body>> getRequest() = 0;

};

#endif // IHTTPREQUEST_H
