#include "httpredirectorresolver.h"
#include <IoC.h>


HttpRedirectorResolver::HttpRedirectorResolver(IJsonObjectPtr jsonobject)
    :_jsonobject(jsonobject)
{

}

std::string HttpRedirectorResolver::GetLocation()
{
    return "http://www.ya.ru";
}
