#ifndef __ISCOPE_H_INCLUDED__
#define __ISCOPE_H_INCLUDED__

#include <IResolverContainer.h>
#include <memory>
#include <string>

using namespace std;

class IScope
{
public:
    virtual ~IScope() = default;

    virtual string getName() = 0;

    virtual void AddChild(shared_ptr<IScope> newChild) = 0;
    virtual shared_ptr<IScope> FindChild(string name) = 0;
    
    virtual IResolverContainerPtr getResolver(string dependecy) = 0;
    virtual void setResolver(string dependecy, IResolverContainerPtr resolver) = 0;
};

using IScopePtr = std::shared_ptr<IScope>;

#endif
