#include <ResolverCollection.h>
#include <ICommand.h>
#include <Scope.h>
#include <IocRegisterCommand.h>
#include <IocNewScopeCommand.h>
#include <IocSetScopeRelativeCommand.h>
#include <IocSetScopeAbsoluteCommand.h>
#include <FallbackCommand.h>
#include <ScopeChangerAdapter.h>
#include <ResolverContainer.h>
#include <functional>
#include <iostream>

thread_local ScopeContainerPtr ResolverCollection::s_pCurrentScopeContainer = nullptr;

void ResolverCollection::Register(string dependecy, IResolverContainerPtr resolver)
{
    getCurrentScopeContainer()->getScope()->setResolver(dependecy, resolver);
}

ScopeContainerPtr ResolverCollection::getCurrentScopeContainer()
{
    if (s_pCurrentScopeContainer == nullptr)
    {
        s_pCurrentScopeContainer = std::make_shared<ScopeContainer>(m_pRootScope);
    }

    return s_pCurrentScopeContainer;
}

ResolverCollection::ResolverCollection()
{
    m_pRootScope = std::make_shared<Scope>("root", nullptr);

    Register("IoC.Register",
             make_container(
                 std::function<ICommandPtr(const char *,IResolverContainerPtr)>(
                     [&](const char *dep, IResolverContainerPtr resolver)
                     {
                         return std::static_pointer_cast<ICommand>(
                             std::make_shared<IocRegisterCommand>(
                                 getCurrentScopeContainer()->getScope(),
                                 dep,
                                 resolver));
                     }
                     )
                 )
             );

    Register("IoC.Scope.New",
             make_container(
                 std::function<ICommandPtr(const char *)>(
                     [&](const char *scopeName)
                     {
                         return std::static_pointer_cast<ICommand>(
                             std::make_shared<IocNewScopeCommand>(
                                 getCurrentScopeContainer()->getScope(),
                                 scopeName)
                             );
                     }
                     )
                 )
             );

    Register("IoC.Scope.Current.Set",
             make_container(
                 std::function<ICommandPtr(const char *)>(
                     [&](const char *scopeName)
                     {
                         std::vector<ICommandPtr> commands = {
                             std::make_shared<IocSetScopeRelativeCommand>(
                                 getCurrentScopeContainer()->getScope(),
                                 std::make_shared<ScopeChangerAdapter>(getCurrentScopeContainer()),
                                 scopeName),
                             std::make_shared<IocSetScopeAbsoluteCommand>(
                                 m_pRootScope,
                                 std::make_shared<ScopeChangerAdapter>(getCurrentScopeContainer()),
                                 scopeName)
                         };
                         return std::static_pointer_cast<ICommand>(
                             std::make_shared<FallbackCommand>(commands));
                     }
                     )
                 )
             );
}

IResolverContainerPtr ResolverCollection::findContainer(string dependecy)
{
    return getCurrentScopeContainer()->getScope()->getResolver(dependecy);
}
