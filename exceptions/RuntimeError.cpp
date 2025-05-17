#include <RuntimeError.h>

RuntimeError::RuntimeError(std::string message)
    :m_sMessage(message)
{
}

std::string RuntimeError::WhatHappened()
{
    return m_sMessage;
}
