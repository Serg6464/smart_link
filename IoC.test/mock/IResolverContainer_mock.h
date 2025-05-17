#ifndef __IRESOLVERCONTAINER_MOCK_H_INCLUDED__
#define __IRESOLVERCONTAINER_MOCK_H_INCLUDED__

#include <IResolverContainer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

class IResolverContainerMock: public IResolverContainer
{
public:
};

using IResolverContainerMockPtr = std::shared_ptr<IResolverContainerMock>;

#endif