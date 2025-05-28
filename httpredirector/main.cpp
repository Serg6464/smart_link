#include <iostream>
#include <memory>
#include <string>
#include <IoC.h>
#include <ICommand.h>

#include "endpoint.h"

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
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
    return 0;
}

void IoC_Init()
{
/*    std::string json_str = R"(
    {
        "version": "1.0",
        "rules":
        [
            {
                "name": "Правило для мобильных устройств",
                "conditions":
                [
                    {
                        "type": "target",
                        "value": "/welcome"
                    },
                    {
                      "type": "user_agent_contain",
                      "value": "Mobile"
                    }
                ],
                "redirect_url": "https://mobile.example.com"
            },
            {
                "name": "Правило для Chrome до начала рабочего времени",
                "conditions": [
                {
                  "type": "user_agent_contain",
                  "value": "Chrome"
                },
                {
                  "type": "time_of_day_before",
                  "value": "08:00:00"
                }
                ],
                "redirect_url": "https://early.example.com"
            }
        ]
    }
    )";
*/

    std::string json_str = R"(
    {
        "version": "1.0",
        "rules":
        [
            {
                "name": "Тестовое правило",
                "conditions":
                [
                    {
                        "type": "target",
                        "value": "/welcome"
                    }
                ],
                "redirect_url": "https://welcome.example.com"
            }
        ]
    }
    )";
    JsonPtr jsonRules = std::make_shared<Json>(boost::json::parse(json_str));

    IoC::Resolve<ICommandPtr>(
        "IoC.Register",
        "Connection.GetNew",
        make_container(std::function<std::shared_ptr<SocketConnection>()>( []() {
                boost::asio::io_context io_context;
                tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8091));
    std::cout << "start waiting request\n";
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
                for (const auto& ruleNode : jsonRules->as_object().at("rules").as_array()) {
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

    IoC::Resolve<ICommandPtr>(
            "IoC.Register",
            "Condition.Get",
            make_container(std::function<IConditionPtr(std::string condition, std::string)>( [](std::string condition, std::string parameter) {

                // TODO: загрузка плагинов
                std::cout<<"resolve condition "<<condition << std::endl;
                if (condition == "target")
                {
                    return (IConditionPtr)ConditionTarget::Create(parameter);
                }
                return (IConditionPtr)nullptr;
            })))->Execute();

 }
