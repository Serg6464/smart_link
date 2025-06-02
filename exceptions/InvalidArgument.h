#ifndef __INVALIDARGUMENT_H_INCLUDED__
#define __INVALIDARGUMENT_H_INCLUDED__

#include <IException.h>
#include <memory>
#include <string>

class InvalidArgument: public IException
{
    std::string m_sMessage;

public:
    InvalidArgument(std::string message);

    std::string WhatHappened() override;
};

typedef std::shared_ptr<InvalidArgument> InvalidArgumentPtr;

#endif