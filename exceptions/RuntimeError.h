#ifndef __RUNTIMEERROR_H_INCLUDED__
#define __RUNTIMEERROR_H_INCLUDED__

#include <IException.h>
#include <memory>
#include <string>

class RuntimeError: public IException
{
    std::string m_sMessage;
public:
    RuntimeError(std::string message);
    std::string WhatHappened() override;
};

using RuntimeErrorPtr = std::shared_ptr<RuntimeError>;

#endif