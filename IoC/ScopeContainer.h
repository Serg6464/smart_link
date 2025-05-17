#ifndef __SCOPECONTAINER_H_INCLUDED__
#define __SCOPECONTAINER_H_INCLUDED__

#include <IScope.h>
#include <memory>
#include <string>

class ScopeContainer//: public IScope
{
    IScopePtr m_pScope;

public:
    ScopeContainer(IScopePtr scope);

    void setScope(IScopePtr scope);
    IScopePtr getScope();
};

using ScopeContainerPtr = std::shared_ptr<ScopeContainer>;

#endif
