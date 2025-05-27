#ifndef CONDITIONTARGET_H
#define CONDITIONTARGET_H

#include "icondition.h"
#include <string>

class ConditionTarget;
using ConditionTargetPtr = std::shared_ptr<ConditionTarget>;

class ConditionTarget : public ICondition
{
    std::string _reference_value;
public:
    ConditionTarget(std::string reference_value)
        :_reference_value(reference_value)
    { };

    static inline ConditionTargetPtr Create(std::string reference_value)
    {
        return std::make_shared<ConditionTarget>(reference_value);
    }
    // ICondition interface
public:
    bool Check(JsonPtr json)
    {
        auto target = json->at("target").as_string();
        std::cout << "check target:" << target << " is? " << _reference_value << std::endl;
        return target == _reference_value;
    }
};

#endif // CONDITIONTARGET_H
