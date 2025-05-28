#ifndef HTTPREDIRECTORRESOLVERSERVICE_H
#define HTTPREDIRECTORRESOLVERSERVICE_H

#include "iredirector.h"

class HttpRedirectorResolverService;
using HttpRedirectorResolverServicePtr = std::shared_ptr<HttpRedirectorResolverService>;

class HttpRedirectorResolverService : public IRedirector
{
    IJsonObjectPtr _jsonobject;
    std::string _serverAddress;
    unsigned short _serverPort;
public:
    HttpRedirectorResolverService(IJsonObjectPtr jsonobject, const std::string& serverAddress, unsigned short serverPort)
        :_jsonobject(jsonobject), _serverAddress(serverAddress), _serverPort(serverPort)
    {};

    // IRedirector interface
public:
    std::string GetLocation();
};

#endif // HTTPREDIRECTORRESOLVERSERVICE_H
