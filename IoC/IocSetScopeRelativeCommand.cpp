#include <IocSetScopeRelativeCommand.h>
#include <RuntimeError.h>

IocSetScopeRelativeCommand::IocSetScopeRelativeCommand(IScopePtr current, IScopeChangerPtr changer, string targetScope)
    : m_pCurrent(current), m_pChanger(changer), m_sTargetScope(targetScope)
{
}

void IocSetScopeRelativeCommand::Execute()
{
    if (m_pCurrent == nullptr)
        throw RuntimeError("IocSetScopeRelativeCommand::Execute(): current scope is nullptr");

    auto scope = m_pCurrent->FindChild(m_sTargetScope);

    if (scope != nullptr)
    {
        if (m_pChanger == nullptr)
            throw RuntimeError("IocSetScopeRelativeCommand::Execute(): scope changer is nullptr");

        m_pChanger->Change(scope);
    }
    else
        throw new RuntimeError("IocSetScopeRelativeCommand::Execute(): wrong scope name");
}
