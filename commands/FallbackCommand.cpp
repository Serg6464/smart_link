#include <FallbackCommand.h>
#include <IException.h>
#include <RuntimeError.h>

FallbackCommand::FallbackCommand(const std::vector<ICommandPtr> &commands)
    :m_Commands(commands)
{
}


void FallbackCommand::Execute()
{
    auto command = m_Commands.begin();
    while (command != m_Commands.end())
    {
        try
        {
            (*command)->Execute();
            return;
        }
        catch (IException *exception)
        {
            delete exception;
        }
        command++;
    }

    throw new RuntimeError("FallbackCommand::Execute(): all commands fails");
}
