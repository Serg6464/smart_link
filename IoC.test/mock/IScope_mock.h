#ifndef __ISCOPE_MOCK_H_INCLUDED__
#define __ISCOPE_MOCK_H_INCLUDED__

#include <IScope.h>
#include <IResolverContainer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

using namespace std;

class IScopeMock: public IScope
{
public:
    MOCK_METHOD(string, getName, ());
    MOCK_METHOD(void, AddChild, (IScopePtr));
    MOCK_METHOD(IScopePtr, FindChild, (string));
    MOCK_METHOD(IResolverContainerPtr, getResolver, (string));
    MOCK_METHOD(void, setResolver, (string, IResolverContainerPtr));
};

using IScopeMockPtr = shared_ptr<IScopeMock>;

#endif