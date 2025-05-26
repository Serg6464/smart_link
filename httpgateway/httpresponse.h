#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

// Реализация ответа на базе Boost

#include "ihttpresponse.h"

class HttpResponse : public IHttpResponse
{
private:
 http::response<http::string_body> response_;

public:
 http::response<http::string_body>& getResponse() override {
 return response_;
 }

};

#endif // HTTPRESPONSE_H
