#ifndef __MACROCOMMAND_H_INCLUDED__
#define __MACROCOMMAND_H_INCLUDED__

#include <ICommand.h>
#include <memory>
#include <vector>

class MacroCommand;
using MacroCommandPtr = std::shared_ptr<MacroCommand>;

class MacroCommand: public ICommand
{
    std::vector<ICommandPtr> m_Commands;

public:
    MacroCommand(const std::vector<ICommandPtr> &commands);

    static MacroCommandPtr Create(const std::vector<ICommandPtr> &commands)
    {
        return std::make_shared<MacroCommand>(commands);
    }

    void Execute() override;
};


#endif
