#include <IoC.h>
#include <ResolverCollection.h>

IResolverCollectionPtr IoC::Resolvers = std::make_shared<ResolverCollection>();
