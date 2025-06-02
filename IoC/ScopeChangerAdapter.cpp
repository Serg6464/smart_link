#include "ScopeChangerAdapter.h"

ScopeChangerAdapter::ScopeChangerAdapter(ScopeContainerPtr injectedScope)
    : m_pInjectedScope(injectedScope)
{}

void ScopeChangerAdapter::Change(IScopePtr scope)
{
    m_pInjectedScope->setScope(scope);
}
