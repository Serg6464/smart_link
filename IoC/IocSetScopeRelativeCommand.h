#ifndef IOCSETSCOPERELATIVECOMMAND_H
#define IOCSETSCOPERELATIVECOMMAND_H

#include <ICommand.h>
#include <IScope.h>
#include <IScopeChanger.h>
#include <memory>
#include <string>

class IocSetScopeRelativeCommand: public ICommand
{
    IScopePtr m_pCurrent;
    IScopeChangerPtr m_pChanger;
    std::string m_sTargetScope;

public:
    IocSetScopeRelativeCommand(IScopePtr current, IScopeChangerPtr changer, std::string targetScope);

    void Execute() override;
};

using IocSetScopeRelativeCommandPtr = std::shared_ptr<IocSetScopeRelativeCommand>;

#endif // IOCSETSCOPERELATIVECOMMAND_H
