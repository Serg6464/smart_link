#ifndef HTTPREQUESTJSONOBJECT_H
#define HTTPREQUESTJSONOBJECT_H

#include "ijsonobject.h"
#include "ihttprequest.h"
#include <memory>

class HttpRequestJsonObject : public IJsonObject
{
    std::shared_ptr<IHttpRequest> _request;
public:
    HttpRequestJsonObject(std::shared_ptr<IHttpRequest> request);
    static std::shared_ptr<HttpRequestJsonObject> Create(std::shared_ptr<IHttpRequest> request);
    // IJsonObject interface
public:
    JsonPtr getJson();
};



#endif // HTTPREQUESTJSONOBJECT_H
