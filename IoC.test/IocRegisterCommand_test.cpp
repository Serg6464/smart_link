#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IocRegisterCommand.h>
#include <IException.h>
#include <IScope_mock.h>
#include <IResolverContainer.h>
#include <IResolverContainer_mock.h>
#include <IException_mock.h>

using namespace std;
using ::testing::Throw;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;


TEST(IocRegisterCommand, SunnyDayTest)
{
    IScopeMockPtr currentScope = make_shared<IScopeMock>();
    IResolverContainerMockPtr container = make_shared<IResolverContainerMock>();
    string dependecyName = "testDependecy";
    IocRegisterCommand cmd(currentScope, dependecyName, container);

    EXPECT_CALL(*currentScope, setResolver(dependecyName, static_pointer_cast<IResolverContainer>(container)));

    EXPECT_NO_THROW(cmd.Execute());
}

TEST(IocRegisterCommand, InvalidArguments)
{
    IResolverContainerMockPtr container = make_shared<IResolverContainerMock>();
    string dependecyName = "testDependecy";
    IocRegisterCommand cmd(nullptr, dependecyName, container);

    try
    {
        cmd.Execute();
        FAIL();
    }
    catch(IException *exception)
    {
        delete exception;
        SUCCEED();
    }
}

TEST(IocRegisterCommand, DependecyAlreadyExists)
{
    IScopeMockPtr currentScope = make_shared<IScopeMock>();
    IResolverContainerMockPtr container = make_shared<IResolverContainerMock>();
    string dependecyName = "testDependecy";
    IocRegisterCommand cmd(currentScope, dependecyName, container);

    EXPECT_CALL(*currentScope, setResolver(dependecyName, static_pointer_cast<IResolverContainer>(container)))
        .WillOnce(Throw(new IExceptionMock()));

    try
    {
        cmd.Execute();
        FAIL();
    }
    catch(IException *exception)
    {
        delete exception;
        SUCCEED();
    }
}
