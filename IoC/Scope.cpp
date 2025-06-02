#include <Scope.h>
#include <RuntimeError.h>
#include <algorithm>

Scope::Scope(string name, IScopePtr parent)
    :m_sName(name), m_pParent(parent)
{
}

string Scope::getName()
{
    return m_sName;
}

void Scope::AddChild(shared_ptr<IScope> newChild)
{
    m_listChildren.push_back(newChild);
}

IScopePtr Scope::FindChild(string name)
{
    auto result = find_if(m_listChildren.begin(), m_listChildren.end(),
                           [name](const IScopePtr &scope){ return scope->getName() == name; });

    if (result == m_listChildren.end())
        return nullptr;

    return *result;
}

IResolverContainerPtr Scope::getResolver(std::string dependecy)
{
    IResolverContainerPtr resolver = m_mapDependies[dependecy];

    if (resolver != nullptr)
        return resolver;

    if (m_pParent != nullptr)
        return m_pParent->getResolver(dependecy);

    return nullptr;
}

void Scope::setResolver(std::string dependecy, IResolverContainerPtr resolver)
{
    if (m_mapDependies[dependecy] != nullptr)
        throw new RuntimeError(
            std::string("Scope::setResolver(): dependecy \"") + 
            dependecy + std::string("\" already exist"));

    m_mapDependies[dependecy] = resolver;
}
