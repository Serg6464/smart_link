#ifndef IOCSETSCOPEABSOLUTECOMMAND_H
#define IOCSETSCOPEABSOLUTECOMMAND_H

#include <ICommand.h>
#include <IScope.h>
#include <IScopeChanger.h>
#include <memory>
#include <string>

class IocSetScopeAbsoluteCommand: public ICommand
{
    IScopePtr m_pRoot;
    IScopeChangerPtr m_pChanger;
    std::string m_sTargetScope;

public:
    IocSetScopeAbsoluteCommand(IScopePtr root, IScopeChangerPtr changer, std::string targetScope);

    void Execute() override;
};

using IocSetScopeAbsoluteCommandPtr = std::shared_ptr<IocSetScopeAbsoluteCommand>;

#endif
