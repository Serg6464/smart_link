#ifndef SCOPEHOLDER_H
#define SCOPEHOLDER_H

#include <IResolverCollection.h>
#include <IScope.h>
#include <ScopeContainer.h>


class ResolverCollection: public IResolverCollection
{
    IScopePtr m_pRootScope;
    thread_local static ScopeContainerPtr s_pCurrentScopeContainer;
    
    void Register(string dependecy, IResolverContainerPtr resolver);
    ScopeContainerPtr getCurrentScopeContainer();

public:
    ResolverCollection();
    
    IResolverContainerPtr findContainer(string dependecy) override;
};

#endif
