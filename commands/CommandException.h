#ifndef __COMMANDEXCEPTION_H_INCLUDED__
#define __COMMANDEXCEPTION_H_INCLUDED__

#include <memory>
#include <IException.h>
#include <ICommand.h>

class CommandException: public IException
{
    ICommandPtr m_pCommand;
    IExceptionPtr m_pException;

public:
    CommandException(ICommandPtr pCommand, IExceptionPtr pException);

    std::string WhatHappened() override;
};

typedef std::shared_ptr<CommandException> CommandExceptionPtr;

#endif