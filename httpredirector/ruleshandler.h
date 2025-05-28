#ifndef RULESHANDLER_H
#define RULESHANDLER_H

#include "irules.h"
#include "ICommand.h"
#include <memory>
#include <string>

class RulesHandler;
using RulesHandlerPtr = std::shared_ptr<RulesHandler>;

class RulesHandler : public IRules
{
    std::string _location;
    ICommandPtr _rules_check_command;
    RulesHandlerPtr _next;
public:
    RulesHandler(std::string location, ICommandPtr rules_check_command);

    static RulesHandlerPtr Create(std::string location, ICommandPtr rules_check_command);

    virtual RulesHandlerPtr setNext(RulesHandlerPtr next)
    {
        _next = next;
        return next;
    };

    // IRules interface
public:
    std::string get_location();
};



#endif // RULESHANDLER_H
