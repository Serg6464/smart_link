#ifndef __IRESOLVERCONTAINER_H_INCLUDED__
#define __IRESOLVERCONTAINER_H_INCLUDED__

#include <memory>

class IResolverContainer
{
public:
    virtual ~IResolverContainer() = default;
};

using IResolverContainerPtr = std::shared_ptr<IResolverContainer>;

#endif
