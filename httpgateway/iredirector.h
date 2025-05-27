#ifndef _IREDIRECTOR_H_INCLUDED_
#define _IREDIRECTOR_H_INCLUDED_

#include "ijsonobject.h"
#include <memory>
#include <string>

class IRedirector
{
public:
    virtual ~IRedirector() = default;
    virtual std::string GetLocation() = 0;
};

using IRedirectorPtr = std::shared_ptr<IRedirector>;

#endif
