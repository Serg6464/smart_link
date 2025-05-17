#ifndef SCOPECHANGERADAPTER_H
#define SCOPECHANGERADAPTER_H

#include <IScopeChanger.h>
#include <ScopeContainer.h>

class ScopeChangerAdapter : public IScopeChanger
{
    ScopeContainerPtr m_pInjectedScope;
public:
    ScopeChangerAdapter(ScopeContainerPtr injectedScope);

    void Change(IScopePtr scope) override;
};

#endif // SCOPECHANGERADAPTER_H
