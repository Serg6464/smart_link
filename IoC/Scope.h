#ifndef SCOPE_H
#define SCOPE_H

#include <IScope.h>
#include <IResolverContainer.h>
#include <memory>
#include <string>
#include <map>
#include <list>

using namespace std;

class Scope : public IScope
{
    string m_sName;

    IScopePtr m_pParent;
    list<shared_ptr<IScope>> m_listChildren;
    
    map<string, IResolverContainerPtr> m_mapDependies;

public:
    Scope(string name, IScopePtr parent);

    string getName() override;

    void AddChild(shared_ptr<IScope> newChild) override;
    IScopePtr FindChild(string name) override;
    
    IResolverContainerPtr getResolver(string dependecy) override;
    void setResolver(string dependecy, IResolverContainerPtr resolver) override;
};

using ScopePtr = std::shared_ptr<Scope>;

#endif
