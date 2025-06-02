#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IocSetScopeRelativeCommand.h>
#include <IException_mock.h>
#include <IScope_mock.h>
#include <IScopeChanger_mock.h>
#include <memory>

using namespace std;
using ::testing::Throw;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;


TEST(IocSetScopeRelativeCommand, SunnyDayTest)
{
    IScopeMockPtr currentScope = make_shared<IScopeMock>();
    IScopeMockPtr targetScope = make_shared<IScopeMock>();
    string targetScopeName = "TestScope";
    IScopeChangerMockPtr scopeChanger = make_shared<IScopeChangerMock>();

    IocSetScopeRelativeCommand cmd(currentScope, scopeChanger, targetScopeName);

    EXPECT_CALL(*currentScope, FindChild(targetScopeName))
        .WillOnce(
            Return(static_pointer_cast<IScope>(targetScope))
        );

    EXPECT_CALL(*scopeChanger, Change(static_pointer_cast<IScope>(targetScope)));

    EXPECT_NO_THROW(cmd.Execute());
}

TEST(IocSetScopeRelativeCommand, WrongScopeNameTest)
{
    IScopeMockPtr currentScope = make_shared<IScopeMock>();
    IScopeMockPtr targetScope = make_shared<IScopeMock>();
    string targetScopeName = "TestScope";
    IScopeChangerMockPtr scopeChanger = make_shared<IScopeChangerMock>();

    IocSetScopeRelativeCommand cmd(currentScope, scopeChanger, targetScopeName);

    EXPECT_CALL(*currentScope, FindChild(targetScopeName))
        .WillOnce(Return(nullptr));

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