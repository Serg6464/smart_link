#ifndef IHTTPRESPONSE_H
#define IHTTPRESPONSE_H

#include <boost/beast/http.hpp>

namespace http = boost::beast::http;

class IHttpResponse
{
public:
 virtual http::response<http::string_body>& getResponse() = 0;
};

#endif // IHTTPRESPONSE_H
