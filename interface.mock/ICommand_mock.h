#ifndef __ICOMMAND_MOCK_H_INCLUDED__
#define __ICOMMAND_MOCK_H_INCLUDED__

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ICommand.h>

class ICommandMock: public ICommand
{
public:
    MOCK_METHOD(void, Execute, ());
};

#endif