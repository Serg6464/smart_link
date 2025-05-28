#include "ruleshandler.h"
#include "IException.h"

RulesHandler::RulesHandler(std::string location, ICommandPtr rules_check_command)
    :_location(location), _rules_check_command(rules_check_command), _next(nullptr)
{

}

RulesHandlerPtr RulesHandler::Create(std::string location, ICommandPtr rules_check_command)
{
    return std::make_shared<RulesHandler>(location, rules_check_command);
}

std::string RulesHandler::get_location()
{
    try
    {
      //выполняем анализ условий и если нет исключений возвращаем location
      _rules_check_command->Execute();
    } catch (IException *e)
    {
        delete e;
        if( _next != nullptr) return _next->get_location();
        return "";
    }
    return _location;
}
