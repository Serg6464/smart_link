#ifndef __IEXCEPTION_MOCK_H_INCLUDED__
#define __IEXCEPTION_MOCK_H_INCLUDED__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IException.h>

class IExceptionMock: public IException
{
public:
    MOCK_METHOD(std::string, WhatHappened, ());
};

#endif