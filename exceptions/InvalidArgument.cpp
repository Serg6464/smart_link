#include <InvalidArgument.h>

InvalidArgument::InvalidArgument(std::string message)
    :m_sMessage(message)
{
}

std::string InvalidArgument::WhatHappened()
{
    return m_sMessage;
}
