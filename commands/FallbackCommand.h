#ifndef FALLBACKCOMMAND_H
#define FALLBACKCOMMAND_H

#include <ICommand.h>
#include <memory>
#include <vector>

class FallbackCommand : public ICommand
{
    std::vector<ICommandPtr> m_Commands;

public:
    FallbackCommand(const std::vector<ICommandPtr> &commands);

    virtual void Execute() override;
};

using FallbackCommandPtr = std::shared_ptr<FallbackCommand>;

#endif
