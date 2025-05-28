#include "checkconditioncommand.h"
#include "icondition.h"
#include "RuntimeError.h"
#include "IoC.h"

CheckConditionCommand::CheckConditionCommand(std::string condition, std::string parameter, JsonPtr request)
    :m_condition(condition), m_parameter(parameter), m_request(request)
{}


void CheckConditionCommand::Execute()
{
    auto conditionObject = IoC::Resolve<IConditionPtr>("Condition.Get", m_condition, m_parameter);

    if (!conditionObject->Check(m_request))
    {
        throw new RuntimeError("CheckConditionCommand::Execute(): checking failed");
    }
}
