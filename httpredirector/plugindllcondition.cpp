#include "plugindllcondition.h"
#include <dlfcn.h> // Для работы с динамическими библиотеками (DLL)
#include <RuntimeError.h>


PluginDllCondition::PluginDllCondition(void *dllhandle, IConditionPtr condition)
{
    if(dllhandle == nullptr){
        throw RuntimeError("Try to create PluginDllCondition with nullptr dll handle");
    }
    _dllhandle = dllhandle;
    _condition = condition;
}

PluginDllCondition::~PluginDllCondition()
{
    if(_condition != nullptr){
        _condition.reset();
    }
    if(_dllhandle != nullptr){
        // Закрываем DLL
        dlclose(_dllhandle);
    }
}

IConditionPtr PluginDllCondition::PluginDllConditionCreate(std::string dllPath, std::string parameter)
{
    // Открываем DLL
    void* handle = dlopen(dllPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::string err = "Ошибка загрузки DLL: " + std::string(dllPath) + std::string( dlerror() );
        throw new RuntimeError(err);
    }

    // Получаем указатель на функцию
    typedef ICondition *(*CreateType)(const std::string &param);
    CreateType dll_CreateNewConditionObj = (CreateType)dlsym(handle, "CreateNewConditionObj");
    // Проверяем, существует ли функция
    if (dll_CreateNewConditionObj) {
        std::shared_ptr<ICondition> pNewConditionObj = std::shared_ptr<ICondition>(dll_CreateNewConditionObj(parameter));
std::cout << "condition :" << dllPath << "new addr: " << pNewConditionObj;

        return std::make_shared<PluginDllCondition>( handle, pNewConditionObj);
    } else {
        std::string err;
        err = "Функция CreateNewConditionObj не найдена в " + dllPath;;
        // Закрываем DLL
        dlclose(handle);
        //std::string err = "Ошибка загрузки DLL: " + std::string(dllPath) + std::string( ":not a valid plugin" );
        throw new RuntimeError(err);
    }
}
