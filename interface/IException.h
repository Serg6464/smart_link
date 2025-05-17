#ifndef __IEXCEPTION_H_INCLUDED__
#define __IEXCEPTION_H_INCLUDED__

#include <string>
#include <memory>

class IException
{
public:
    virtual ~IException() = default;

    virtual std::string WhatHappened() = 0;
};

typedef std::shared_ptr<IException> IExceptionPtr;

#endif