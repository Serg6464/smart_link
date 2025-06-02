#include <IocSetScopeAbsoluteCommand.h>
#include <RuntimeError.h>
#include <sstream>
#include <string>


using namespace std;

IocSetScopeAbsoluteCommand::IocSetScopeAbsoluteCommand(IScopePtr root, IScopeChangerPtr changer, string targetScope)
    : m_pRoot(root), m_pChanger(changer), m_sTargetScope(targetScope)
{
}

void IocSetScopeAbsoluteCommand::Execute()
{
    istringstream stream(m_sTargetScope);
    string token;
    const char delimiter = '/';

    if (!getline(stream, token, delimiter))
        throw new RuntimeError("IocSetScopeAbsoluteCommand::Execute(): wrong path");

    if (token != "")
        throw new RuntimeError("IocSetScopeAbsoluteCommand::Execute(): wrong path");

    IScopePtr scope = m_pRoot;

    while (getline(stream, token, delimiter)) {
        if (token == "")
            throw new RuntimeError("IocSetScopeAbsoluteCommand::Execute(): wrong path");
        IScopePtr next = scope->FindChild(token);
        if (next == nullptr)
            throw new RuntimeError("IocSetScopeAbsoluteCommand::Execute(): wrong path");
        scope = next;
    }

    m_pChanger->Change(scope);
}
