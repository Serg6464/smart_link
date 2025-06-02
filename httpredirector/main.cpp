#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <IoC.h>
#include <ICommand.h>

#include "endpoint.h"
#include <boost/json.hpp>
#include <boost/json/error.hpp>
#include <fstream>

#include <socketconnection.h>
#include "jsonreadconnection.h"
#include "jsonsendconnection.h"
#include "boostjsonobject.h"
#include "resolveredirectioncommand.h"
#include <MacroCommand.h>
#include "sendnewlocationcommand.h"

#include "httpredirectorresolver.h"
#include "ruleshandler.h"
#include "checkconditioncommand.h"
#include "icondition.h"
#include <MacroCommand.h>
#include "conditiontarget.h"
#include <boost/range/adaptor/reversed.hpp>
#include "plugindllcondition.h"
#include <dlfcn.h> // Для работы с динамическими библиотеками (DLL)
#include <dirent.h> // Для перечисления файлов в каталоге


//All logic dependency initialization. 
void IoC_Init();

int main(void)
{
    try
    {
        IoC_Init();

        EndPoint mainLoop;
        mainLoop.Run();
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}

/*Добавляем условия плагины
 * плагины храним в dll в папке. каждая dll содержит функцию создания условия IConditionPtr CreateCondition(string parameter)
 * и функцию получения имени условия. getConditionName для регистрации условия
 */
std::map<std::string, std::string> conditions_plugin;
// загрузка плагинов
std::string loadAndCheckDLL(const std::string& dllPath);
std::vector<std::string> getDLLFiles(const std::string& directory);

void LoadPluginsInfo(std::map<std::string, std::string > *pconditions_plugin)
{
     std::string currentDirectory = "./plugins"; //

     // Получаем список файлов DLL в текущей директории
     std::vector<std::string> dllFiles = getDLLFiles(currentDirectory);

     std::string condition_name;
     // Проверяем каждую DLL
     for (const auto& dllFile : dllFiles) {
         condition_name = loadAndCheckDLL(dllFile);
         if ( condition_name != "") {
             // функции найдены в DLL
             pconditions_plugin->emplace(condition_name,dllFile);
         }
     }
     std::cout << "Plugins registered:\n" << pconditions_plugin->size() << "\n";

}

// Функция для загрузки и поиска функции в DLL
std::string loadAndCheckDLL(const std::string& dllPath)
{
    std::string conditionName;
    // Открываем DLL
    void* handle = dlopen(dllPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Ошибка загрузки DLL: " << dllPath << " - " << dlerror() << std::endl;
        return "";
    }

    // Получаем указатель на функцию
    std::string getConditionNameSymbol = "getConditionName";
    typedef void (*GetConditionNameType)(std::string *);
    GetConditionNameType dll_getConditionName = (GetConditionNameType)dlsym(handle, getConditionNameSymbol.c_str());
    typedef ICondition (*CreateType)(const std::string &param);
    CreateType dll_CreateNewConditionObj = (CreateType)dlsym(handle, "CreateNewConditionObj");
    // Проверяем, существует ли функция
    if (dll_getConditionName && dll_CreateNewConditionObj) {
        dll_getConditionName(&conditionName);
        // Закрываем DLL
        dlclose(handle);
        return conditionName;
    } else {
        std::cerr << "Функция " << getConditionNameSymbol << " не найдена в " << dllPath << std::endl;
        // Закрываем DLL
        dlclose(handle);
        return "";
    }
}

// Функция для перечисления файлов в каталоге
std::vector<std::string> getDLLFiles(const std::string& directory)
{
    std::vector<std::string> dllFiles;
    DIR* dir = opendir(directory.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG && std::string(entry->d_name).rfind(".so") != std::string::npos) {
                // Заменяем "/" на "//" для совместимости с разными платформами
                dllFiles.push_back(directory + "/" + entry->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Ошибка при открытии каталога: " << directory << std::endl;
    }
    return dllFiles;
}


boost::json::value load_json_from_file(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());

        try {
            return boost::json::parse(content);
        } catch (const std::exception& e) {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()));
        }
    } catch (const std::exception& e) {
        throw std::runtime_error("Error loading JSON: " + std::string(e.what()));
    }
}

// Проходим по всем правилам
int json_config_verify( JsonPtr jsonRules)
{
    for (const auto& ruleNode : boost::adaptors::reverse(jsonRules->as_object().at("rules").as_array())) {
        // Проверяем условия
        for (const auto& conditionNode : ruleNode.as_object().at("conditions").as_array()) {

            auto conditionObject = IoC::Resolve<IConditionPtr>("Condition.Get",
                                                               std::string(conditionNode.as_object().at("type").as_string().c_str()),
                                                               std::string(conditionNode.as_object().at("value").as_string().c_str()));

            if (conditionObject == nullptr){
                //not valid rule
                throw std::runtime_error( conditionNode.as_object().at("type").as_string().c_str());
            }

        }
    }
    return 1;
}


void IoC_Init()
{

    std::string json_str = R"(
    {
        "version": "1.0",
        "rules":
        [
            {
                "name": "Page - notime to enter when time no valid",
                "conditions":
                [
                    {
                        "type": "target",
                        "value": "/welcome"
                    },
                    {
                        "type": "date_before",
                        "value": "30-05-2025"
                    }
                ],
                "redirect_url": "https://notime.to.enter"
            },
            {
                "name": "Welcome page",
                "conditions":
                [
                    {
                        "type": "target",
                        "value": "/welcome"
                    }
                ],
                "redirect_url": "https://welcome.example.com"
            },
            {
                "name": "Переход на гугл",
                "conditions":
                [
                    {
                        "type": "target_contains",
                        "value": "/search"
                    }
                ],
                "redirect_url": "https://www.google.com"
            }

        ]
    }
    )";
//    JsonPtr jsonRules = std::make_shared<Json>(boost::json::parse(json_str));
    JsonPtr jsonRules = std::make_shared<Json>(load_json_from_file("./config/redirection_rules.json"));



    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Connection.GetNew",
        make_container(std::function<std::shared_ptr<SocketConnection>()>( []() {
                boost::asio::io_context io_context;
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8091));
    std::cout << "start waiting request to link resolve\n";
                std::shared_ptr<tcp::socket> socket = std::make_shared<tcp::socket>(io_context);
                std::shared_ptr<SocketConnection> conn = std::make_shared<SocketConnection>(socket);
                acceptor.accept( conn->socket() );
                return conn;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Request.GetNew",
                make_container(std::function<IJsonObjectPtr(std::shared_ptr<SocketConnection>)>( [](std::shared_ptr<SocketConnection> conn) {
                        auto req = BoostJsonObject::Create();
                        std::shared_ptr<IReadableConnection> readconn = std::make_shared<JsonReadConnection>(conn,req);
                        readconn->read();
                        return (IJsonObjectPtr)req;
                    } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.Get",
        make_container(std::function<ICommandPtr(std::shared_ptr<SocketConnection>,IJsonObjectPtr)>( [](std::shared_ptr<SocketConnection> conn, IJsonObjectPtr req) {
                std::vector<ICommandPtr> commands;
                IJsonObjectPtr resp = BoostJsonObject::Create();
                commands.push_back( ResolveRedirectionCommand::Create(req, resp));
                //create send cmd
                JsonSendConnectionPtr sendconn = JsonSendConnection::Create(conn, resp);
                commands.push_back(SendNewLocationCommand::Create(sendconn));

                return MacroCommand::Create(commands);
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "ProcessPacketCmd.GetRedirector",
        make_container(std::function<IRedirectorPtr(IJsonObjectPtr)>( [](IJsonObjectPtr json_request) {
                IRedirectorPtr res = std::make_shared<HttpRedirectorResolver>(json_request);
                return res;
            } )))->Execute();

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Redirector.GetLocationRule",
        make_container(std::function<IRulesPtr(IJsonObjectPtr)>( [jsonRules](IJsonObjectPtr httpjsonobject) {
                //Создаю цепочку обработчиков правил, внутри каждого все условия для конкретного правила
                //в данной реализации правила из json
                RulesHandlerPtr rules_chain = nullptr;
                // Проходим по всем правилам
                for (const auto& ruleNode : boost::adaptors::reverse(jsonRules->as_object().at("rules").as_array())) {
                    std::vector<ICommandPtr> commands;
                    // Собираем условия
                    for (const auto& conditionNode : ruleNode.as_object().at("conditions").as_array()) {
                            commands.push_back(CheckConditionCommand::Create(
                                    conditionNode.as_object().at("type").as_string().c_str(),
                                    conditionNode.as_object().at("value").as_string().c_str(),
                                    httpjsonobject->getJson()
                                    ));

                    }

                     // Получаем действия
                    std::string redirect_url = ruleNode.as_object().at("redirect_url").as_string().c_str();
                    auto newRule = RulesHandler::Create(redirect_url, MacroCommand::Create(commands));
                    newRule->setNext(rules_chain);
                    rules_chain = newRule;
                }
                return rules_chain;
            } )))->Execute();

    /*Добавляем условия плагины
     * плагины храним в dll в папке. каждая dll содержит функцию создания условия IConditionPtr CreateCondition(string parameter)
     * и функцию получения имени условия. getConditionName для регистрации условия
     */
    std::map<std::string, std::string> conditions_plugin;
    // загрузка плагинов
    LoadPluginsInfo(&conditions_plugin);

    IoC::Resolve<ICommandPtr>(
            "IoC.Register",
            "Condition.Get",
            make_container(std::function<IConditionPtr(std::string condition, std::string)>( [conditions_plugin](std::string condition, std::string parameter) {


                //std::cout<<"resolve condition "<< condition << std::endl;
                auto it = conditions_plugin.find(condition);
                if( it != conditions_plugin.end() ){
                    return PluginDllCondition::PluginDllConditionCreate( it->second, parameter);
                } else {
                    if (condition == "target")
                    {
                        return (IConditionPtr)ConditionTarget::Create(parameter);
                    }
                }
                return (IConditionPtr)nullptr;
            })))->Execute();
    try
    {
        json_config_verify(jsonRules);
    } catch ( std::exception &e )
    {
        std::cout << "json rules not valid: "<< e.what() << "\n";
        throw std::exception(e);
    }

 }
