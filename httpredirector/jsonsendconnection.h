#ifndef JSONSENDCONNECTION_H
#define JSONSENDCONNECTION_H

#include <isendableconnection.h>
#include <ijsonobject.h>

/*
#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>
*/


class JsonSendConnection;
using JsonSendConnectionPtr = std::shared_ptr<JsonSendConnection>;
class JsonSendConnection : public ISendableConnection
{
    std::shared_ptr<SocketConnection> _connection;
    IJsonObjectPtr _object;
public:
    JsonSendConnection( std::shared_ptr<SocketConnection> connection, IJsonObjectPtr object):
        _connection(connection), _object(object)
    {};

    static inline JsonSendConnectionPtr Create(std::shared_ptr<SocketConnection> connection, IJsonObjectPtr object)
    {
        return std::make_shared<JsonSendConnection>(connection, object);
    }

    // ISendableConnection interface
public:
    void send()
    {
        // Преобразуем JSON в строку
          std::string jsonString = boost::json::serialize(*(_object->getJson()));

          // Добавляем символ новой строки для удобства приема
          jsonString += "\r\n";

          // Отправляем данные
          boost::asio::write(_connection->socket(), boost::asio::buffer(jsonString));
    }
};

#endif // JSONSENDCONNECTION_H
