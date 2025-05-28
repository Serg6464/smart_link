#ifndef JSONREADCONNECTION_H
#define JSONREADCONNECTION_H

#include <ireadableconnection.h>
#include <ijsonobject.h>

/*#include <boost/json.hpp>
#include <boost/json/src.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

using Json = boost::json::value;
using JsonPtr = std::shared_ptr<Json>;
*/

class JsonReadConnection;
using JsonReadConnectionPtr = std::shared_ptr<JsonReadConnection>;

class JsonReadConnection : public IReadableConnection
{
    std::shared_ptr<SocketConnection> _connection;
    IJsonObjectPtr _object;
public:
    JsonReadConnection( std::shared_ptr<SocketConnection> connection, IJsonObjectPtr object):
        _connection(connection), _object(object)
    {};

    static inline JsonReadConnectionPtr Create(std::shared_ptr<SocketConnection> connection, IJsonObjectPtr object)
    {
        return std::make_shared<JsonReadConnection>(connection, object);
    }


    // IReadableConnection interface
public:
    void read()
    {
        boost::asio::streambuf request;
        boost::asio::read_until(_connection->socket(), request, "\r\n");

        std::string jsonString;
        std::istream response_stream(&request);
        std::getline(response_stream, jsonString);

        // Создаем объект JSON
        *(_object->getJson()) = boost::json::parse(jsonString);
        std::cout << *(_object->getJson()); //<< std::cin;request;
    }
};

#endif // JSONREADCONNECTION_H
