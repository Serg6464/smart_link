#include <string>
#include <icondition.h>

#define PluginConditionName "target_contains"

extern "C"{
void getConditionName(std::string *destination);
ICondition *CreateNewConditionObj(const std::string &param);
}

class PluginCondition: public ICondition
{
    std::string _reference_value;
public:
    PluginCondition(std::string reference_value)
        :_reference_value(reference_value)
    { };

    // ICondition interface
public:
    bool Check(JsonPtr json)
    {
        auto target = json->at("target").as_string();
        return target.find(_reference_value) != std::string::npos;
    }};

void getConditionName(std::string *destination) {
    *destination = PluginConditionName;
}
ICondition *CreateNewConditionObj(const std::string &param)
{
    return new PluginCondition(std::string(param));
}
