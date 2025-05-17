#ifndef IocNewScopeCommand_H
#define IocNewScopeCommand_H

#include <ICommand.h>
#include <IScope.h>
#include <memory>
#include <string>

class IocNewScopeCommand: public ICommand
{
    IScopePtr m_pCurrentScope;
    std::string m_sName;
public:
    IocNewScopeCommand(IScopePtr pCurrentScope, std::string name);

    void Execute() override;
};

using IocNewScopeCommandPtr = std::shared_ptr<IocNewScopeCommand>;

#endif
