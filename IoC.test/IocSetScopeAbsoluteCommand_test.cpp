#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IocSetScopeAbsoluteCommand.h>
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


TEST(IocSetScopeAbsoluteCommand, ChangeScopeToRoot)
{
    IScopeMockPtr rootScope = make_shared<IScopeMock>();
    string targetScopeName = "/";
    IScopeChangerMockPtr scopeChanger = make_shared<IScopeChangerMock>();
    IocSetScopeAbsoluteCommand cmd(rootScope, scopeChanger, targetScopeName);

    EXPECT_CALL(*scopeChanger, Change(static_pointer_cast<IScope>(rootScope)));

    EXPECT_NO_THROW(cmd.Execute());
}

TEST(IocSetScopeAbsoluteCommand, ChangeScopeToSubscope)
{
    IScopeMockPtr rootScope = make_shared<IScopeMock>();
    IScopeMockPtr scope1 = make_shared<IScopeMock>();
    IScopeMockPtr scope1_2 = make_shared<IScopeMock>();
    string targetScopeName = "/scope1/scope1_2";
    IScopeChangerMockPtr scopeChanger = make_shared<IScopeChangerMock>();
    IocSetScopeAbsoluteCommand cmd(rootScope, scopeChanger, targetScopeName);

    EXPECT_CALL(*rootScope, FindChild("scope1"))
        .WillOnce(
            Return(static_pointer_cast<IScope>(scope1))
        );

    EXPECT_CALL(*scope1, FindChild("scope1_2"))
        .WillOnce(
            Return(static_pointer_cast<IScope>(scope1_2))
        );

    EXPECT_CALL(*scopeChanger, Change(static_pointer_cast<IScope>(scope1_2)));

    EXPECT_NO_THROW(cmd.Execute());
}

TEST(IocSetScopeAbsoluteCommand, WrongScopeName)
{
    IScopeMockPtr rootScope = make_shared<IScopeMock>();
    IScopeMockPtr scope1 = make_shared<IScopeMock>();
    string targetScopeName = "/scope1/scope1_3";
    IScopeChangerMockPtr scopeChanger = make_shared<IScopeChangerMock>();
    IocSetScopeAbsoluteCommand cmd(rootScope, scopeChanger, targetScopeName);

    EXPECT_CALL(*rootScope, FindChild("scope1"))
        .WillOnce(
            Return(static_pointer_cast<IScope>(scope1))
        );

    EXPECT_CALL(*scope1, FindChild("scope1_3"))
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