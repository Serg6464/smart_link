#include <ScopeContainer.h>

ScopeContainer::ScopeContainer(IScopePtr scope)
    : m_pScope(scope)
{

}

void ScopeContainer::setScope(IScopePtr scope)
{
    m_pScope = scope;
}

IScopePtr ScopeContainer::getScope()
{
    return m_pScope;
}
