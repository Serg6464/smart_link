#include <MacroCommand.h>
#include <CommandException.h>

MacroCommand::MacroCommand(const std::vector<ICommandPtr> &commands)
    : m_Commands(commands)
{
}

void MacroCommand::Execute()
{
    auto command = m_Commands.begin();
    while (command != m_Commands.end())
    {
        try
        {
            (*command)->Execute();
        }
        catch (IException *exception)
        {
            throw new CommandException(*command, IExceptionPtr(exception));
        }
        command++;
    }
}
