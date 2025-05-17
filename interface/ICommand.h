#ifndef __ICOMMAND_H_INCLUDED__
#define __ICOMMAND_H_INCLUDED__

#include <memory>

class ICommand
{
public:
    virtual ~ICommand() = default;

    virtual void Execute() = 0;
};

typedef std::shared_ptr<ICommand> ICommandPtr;

#endif