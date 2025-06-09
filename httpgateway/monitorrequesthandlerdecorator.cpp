#include "monitorrequesthandlerdecorator.h"

#include <iostream>
#include <memory>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <boost/beast/http.hpp>
#include <boost/beast/core.hpp>
#include <boost/asio.hpp>

namespace http = boost::beast::http;

void MonitorRequestHandlerDecorator::sendUDP(const std::string& serverName, unsigned short port, const std::string& message) {
 try {
 // Создаем контекст ввода-вывода
 boost::asio::io_context io_context;

 // Создаем UDP-сокет
 boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::v4());

 // Преобразуем хост и порт в конечную точку
 boost::asio::ip::udp::resolver resolver(io_context);
 boost::asio::ip::udp::resolver::results_type endpoints = resolver.resolve(serverName, std::to_string(port));

 // Отправляем сообщение
 socket.send_to(boost::asio::buffer(message), *endpoints.begin());

 std::cout << "Message sent to " << serverName << ":" << port << std::endl;
 } catch (const std::exception& e) {
 std::cerr << "Error: " << e.what() << std::endl;
 }
}

MonitorRequestHandlerDecorator::MonitorRequestHandlerDecorator(std::shared_ptr<IRequestHandler> handler, std::string server_addr, int port)
    :handler_(handler), server_addr_(server_addr), port_(port)
{

}

std::string MonitorRequestHandlerDecorator::convert_http_response_to_string(http::response<http::string_body>& res) {
    std::ostringstream oss;
    res.prepare_payload(); // Подготовка ответа перед выводом

    // Записываем статус-код и версию протокола
    oss << res.version() << ' '
        << static_cast<unsigned>(res.result_int()) << ' '
        << res.reason() << "\r\n"; // Строка статуса

    // Добавляем поля заголовков
    for(auto&& field : res.base()) {
        oss << field.name_string() << ": "
           << field.value()
           << "\r\n";
    }

    // Завершаем разделителем между заголовком и телом
    oss << "\r\n";

    // Добавляем тело ответа, если оно есть
    if(!res.body().empty()) {
        oss << res.body();
    }

    return oss.str();
}

std::string MonitorRequestHandlerDecorator::convert_http_request_to_string(http::request<http::string_body>& req) {
    std::ostringstream oss;
    req.prepare_payload(); // Убедимся, что тело запроса подготовлено

    // Записываем заголовок запроса
    oss << req.base();

    // Если имеется тело запроса, добавляем его
    if (!req.body().empty())
        oss << '\r' << '\n' << req.body();

    return oss.str();
}


bool MonitorRequestHandlerDecorator::handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response)
{

    // Выполняем основную обработку запроса
    bool result = handler_->handle(request, response);
    std::string serialized_request = convert_http_request_to_string(*(request->getRequest()));
    std::string serialized_response = convert_http_response_to_string( response->getResponse());
    // Формируем сообщение мониторинга (сериализуя request и response)
    std::string monitorMessage = "Request: " + serialized_request +
                                 "\nResponse: " + serialized_response;
    std::cout <<monitorMessage << std::endl;

    // Отправляем сформированное сообщение на UDP-порт
    sendUDP(server_addr_, port_, monitorMessage);

    return result;
}
