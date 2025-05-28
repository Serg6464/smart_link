#ifndef CHECKCONDITIONCOMMAND_H
#define CHECKCONDITIONCOMMAND_H

#include "ICommand.h"
#include "ijsonobject.h"
#include <memory>
#include <string>

class CheckConditionCommand;
using CheckConditionCommandPtr = std::shared_ptr<CheckConditionCommand>;

class CheckConditionCommand : public ICommand
{
    std::string m_condition;
    std::string m_parameter;
    JsonPtr m_request;

public:
    CheckConditionCommand(std::string condition, std::string parameter, JsonPtr request);

    static CheckConditionCommandPtr Create(std::string condition, std::string parameter, JsonPtr request)
    {
        return std::make_shared<CheckConditionCommand>(condition, parameter, request);
    }

    void Execute() override;
};

#endif // CHECKCONDITIONCOMMAND_H
