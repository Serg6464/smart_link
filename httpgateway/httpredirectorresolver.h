#ifndef HTTPREDIRECTORRESOLVER_H
#define HTTPREDIRECTORRESOLVER_H

#include "iredirector.h"
#include "ijsonobject.h"

class HttpRedirectorResolver : public IRedirector
{
    IJsonObjectPtr _jsonobject;
public:
    HttpRedirectorResolver(IJsonObjectPtr jsonobject);

    // IRedirector interface
public:
    std::string GetLocation();
};



#endif // HTTPREDIRECTORRESOLVER_H
