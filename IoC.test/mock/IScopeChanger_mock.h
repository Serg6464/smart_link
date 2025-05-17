#ifndef __ISOPECHANGER_MOCK_H_INCLUDED__
#define __ISOPECHANGER_MOCK_H_INCLUDED__

#include <IScopeChanger.h>
#include <IScope.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

class IScopeChangerMock: public IScopeChanger
{
public:
    MOCK_METHOD(void, Change, (IScopePtr));
};

using IScopeChangerMockPtr = std::shared_ptr<IScopeChangerMock>;

#endif