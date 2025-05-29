#include "httpredirectorresolverservice.h"
#include <IoC.h>
#include <boost/asio.hpp>
#include <iostream>
#include <boostjsonobject.h>

using boost::asio::ip::tcp;

std::string HttpRedirectorResolverService::GetLocation()
{
    //1connection conn;
    //2отправить запрос
    //3получить ответ
    std::string newLocation;
    // Создаем io_service
     boost::asio::io_service io_service;

     // Создаем сокет
     tcp::socket socket(io_service);

     try
     {
         // Подключаемся к серверу
         tcp::resolver resolver(io_service);
         auto endpoint_iterator = resolver.resolve({_serverAddress, std::to_string(_serverPort)});
         boost::asio::connect(socket, endpoint_iterator);

    // Отправляем запрос - TODO: заменить на jsonsendconnection
         // Преобразуем JSON в строку
           std::string jsonString = boost::json::serialize(*(_jsonobject->getJson()));
           // Добавляем символ новой строки для удобства приема
           jsonString += "\r\n";
           // Отправляем данные
           boost::asio::write(socket, boost::asio::buffer(jsonString));

    //TODO: заменить на вызов jsonreadconnection
         boost::asio::streambuf request;
         boost::asio::read_until(socket, request, "\r\n");

         std::istream response_stream(&request);
         std::getline(response_stream, jsonString);

        BoostJsonObjectPtr response = BoostJsonObject::Create();
         // Создаем объект JSON
         *(response->getJson()) = boost::json::parse(jsonString);
         //std::cout << *(response->getJson()); //<< std::cin;request;

        newLocation = response->getJson()->as_object().at("location").as_string().c_str();
     } catch ( const std::exception& e)
     {
        std::cerr << "Redirection error: " << e.what() << std::endl;
     }
     // Закрываем соединение
     socket.close();

     return newLocation;
}
