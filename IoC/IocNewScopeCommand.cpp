#include <IocNewScopeCommand.h>
#include <Scope.h>
#include <InvalidArgument.h>
#include <RuntimeError.h>

IocNewScopeCommand::IocNewScopeCommand(IScopePtr pCurrentScope, string name)
    : m_pCurrentScope(pCurrentScope), m_sName(name)
{
}

void IocNewScopeCommand::Execute()
{
    if (m_pCurrentScope == nullptr)
        throw new InvalidArgument("IocNewScopeCommand: m_pCurrentScope is nullptr");

    if (m_pCurrentScope->FindChild(m_sName) != nullptr)
        throw new RuntimeError(std::string("IocNewScopeCommand: scope \"") + m_sName + std::string("\" already exist"));

    m_pCurrentScope->AddChild( std::make_shared<Scope>(m_sName, m_pCurrentScope) );
}
