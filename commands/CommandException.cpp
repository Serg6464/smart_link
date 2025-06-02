#include <CommandException.h>

CommandException::CommandException(ICommandPtr pCommand, IExceptionPtr pException)
    : m_pCommand(pCommand), m_pException(pException)
{
}

std::string CommandException::WhatHappened()
{
    return std::string("Command failed with exception: ") + m_pException->WhatHappened();
}