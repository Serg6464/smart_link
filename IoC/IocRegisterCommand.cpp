#include <IocRegisterCommand.h>
#include <InvalidArgument.h>
#include <RuntimeError.h>

IocRegisterCommand::IocRegisterCommand(IScopePtr scope, std::string dependecy, IResolverContainerPtr resolver)
    :m_pScope(scope), m_sDependecy(dependecy), m_pResolver(resolver)
{

}

void IocRegisterCommand::Execute()
{
    if (m_pScope == nullptr)
        throw new InvalidArgument("IocRegisterCommand::Execute(): m_pScope is nullptr");

    m_pScope->setResolver(m_sDependecy, m_pResolver);
}
