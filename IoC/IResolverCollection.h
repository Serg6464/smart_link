#ifndef IRESOLVERCOLLECTION_H
#define IRESOLVERCOLLECTION_H

#include <IResolverContainer.h>
#include <memory>
#include <string>

class IResolverCollection
{
public:
    virtual ~IResolverCollection() = default;
    
    virtual IResolverContainerPtr findContainer(std::string dependecy) = 0;
};

using IResolverCollectionPtr = std::shared_ptr<IResolverCollection>;

#endif
