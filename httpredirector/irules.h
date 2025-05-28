#ifndef IRULES_H
#define IRULES_H

#include <memory>
#include <string>

class IRules;
using IRulesPtr = std::shared_ptr<IRules>;
class IRules
{
public:
    ~IRules() = default;
    virtual std::string get_location() = 0;
};

#endif // IRULES_H
