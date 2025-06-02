#ifndef IOCREGISTERCOMMAND_H
#define IOCREGISTERCOMMAND_H

#include <ICommand.h>
#include <IScope.h>
#include <IResolverContainer.h>
#include <memory>
#include <string>

class IocRegisterCommand: public ICommand
{
    IScopePtr m_pScope;
    std::string m_sDependecy;
    IResolverContainerPtr m_pResolver;

public:
    IocRegisterCommand( IScopePtr scope, std::string dependecy, IResolverContainerPtr resolver);

    void Execute() override;
};

using IocRegisterCommandPtr = std::shared_ptr<IocRegisterCommand>;

#endif // IOCREGISTERCOMMAND_H
