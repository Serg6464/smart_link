#include <IoC.h>
#include <ICommand.h>
#include <IException.h>
#include <ResolverContainer.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <thread>

using namespace std;
using ::testing::Throw;
using ::testing::Return;
using ::testing::AnyNumber;
using ::testing::_;
using ::testing::InSequence;

TEST(IoC, RegisterDependecy)
{
    IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "/")->Execute();
    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ScopeName",
        make_container(std::function<string()>( [](){ return string("root"); } ))
        )->Execute();

    EXPECT_EQ(
        string("root"),
        IoC::Resolve<string>("ScopeName")
    );
}

TEST(IoC, CreateScope)
{
    try {
        IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "/")->Execute();
        IoC::Resolve<ICommandPtr>("IoC.Scope.New", "subscope_01")->Execute();
        IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "subscope_01")->Execute();

        IoC::Resolve<ICommandPtr>(
            "IoC.Register",
            "ScopeName",
            make_container(std::function<string()>( [](){ return string("subscope_01"); } ))
            )->Execute();
        
        EXPECT_EQ(
            string("subscope_01"),
            IoC::Resolve<string>("ScopeName")
        );
    }
    catch(IException *exception)
    {
        string what = exception->WhatHappened();
        delete exception;
        FAIL() << what;
    }
}

TEST(IoC, InheritedDependies)
{
    IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "/")->Execute();
    IoC::Resolve<ICommandPtr>("IoC.Scope.New", "subscope_02")->Execute();
    IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "subscope_02")->Execute();

    EXPECT_EQ(
        string("root"),
        IoC::Resolve<string>("ScopeName")
    );
}

TEST(IoC, MultithreadedTest)
{
    IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "/")->Execute();
    IoC::Resolve<ICommandPtr>("IoC.Scope.New", "subscope_03")->Execute();
    IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "subscope_03")->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ScopeName",
        make_container(std::function<string()>( [](){ return string("subscope_03"); } ))
    )->Execute();

    std::thread t( []() {
        IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "/")->Execute();
        IoC::Resolve<ICommandPtr>("IoC.Scope.New", "subscope_03_thread")->Execute();
        IoC::Resolve<ICommandPtr>("IoC.Scope.Current.Set", "subscope_03_thread")->Execute();
    
        IoC::Resolve<ICommandPtr>(
            "IoC.Register",
            "ScopeName",
            make_container(std::function<string()>( [](){ return string("subscope_03_thread"); } ))
        )->Execute();
    
    } );
    t.join();

    EXPECT_EQ(
        string("subscope_03"),
        IoC::Resolve<string>("ScopeName")
    );    
}