#ifndef ICONDITION_H
#define ICONDITION_H

#include <ijsonobject.h>
#include <memory>

class ICondition
{
public:
    virtual ~ICondition() = default;
    virtual bool Check(JsonPtr json) = 0;
};

using IConditionPtr = std::shared_ptr<ICondition>;

#endif // ICONDITION_H
