#ifndef PLUGINDLLCONDITION_H
#define PLUGINDLLCONDITION_H

#include "icondition.h"
#include <memory>
#include <string>

class PluginDllCondition : public ICondition
{
    void* _dllhandle;
    IConditionPtr _condition;
public:
    PluginDllCondition(void *dllhandle, IConditionPtr condition);
    ~PluginDllCondition();
    static IConditionPtr PluginDllConditionCreate( std::string dllPath, std::string parameter);


    // ICondition interface
public:
    bool Check(JsonPtr json)
    {
        if( _condition != nullptr ){
            return _condition->Check(json);
        }
        return false;
    }
};

#endif // PLUGINDLLCONDITION_H
