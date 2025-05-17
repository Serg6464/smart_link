#ifndef __IOC_H_INCLUDED__
#define __IOC_H_INCLUDED__

#include <IResolverCollection.h>
#include <ResolverContainer.h>
#include <RuntimeError.h>
#include <string>
#include <stdexcept>
#include <memory>
#include <functional>

class IoC
{
    static IResolverCollectionPtr Resolvers;

    IoC() {}

public:

    template<typename ResultType, typename... Args>
    static ResultType Resolve(std::string dependecy, Args... args)
    {
        using ResolverContainerType = ResolverContainer<std::function<ResultType(Args...)>>;

        std::shared_ptr<ResolverContainerType> container =
            std::dynamic_pointer_cast<ResolverContainerType>(IoC::Resolvers->findContainer(dependecy));

        if (container == nullptr)
            throw new RuntimeError(
                std::string("IoC::Resolve(): resolver <") +
                dependecy +
                std::string("> not found"));

        return container->getResolver()(args...);
    }

    template<typename ResultType>
    static ResultType Resolve(std::string dependecy)
    {
        using ResolverContainerType = ResolverContainer<std::function<ResultType()>>;

        std::shared_ptr<ResolverContainerType> container =
            std::dynamic_pointer_cast<ResolverContainerType>(IoC::Resolvers->findContainer(dependecy));

        if (container == nullptr)
            throw new RuntimeError(
                std::string("IoC::Resolve(): resolver <") +
                dependecy +
                std::string("> not found"));

        return container->getResolver()();
    }
};

#endif
