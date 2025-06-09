#ifndef MONITORREQUESTHANDLERDECORATOR_H
#define MONITORREQUESTHANDLERDECORATOR_H

#include "irequesthandler.h"
#include <memory>

class MonitorRequestHandlerDecorator : public IRequestHandler
{
    std::shared_ptr<IRequestHandler> handler_; // Реализуемый оригинальный обработчик
    std::string server_addr_;
    int port_;

    void sendUDP(const std::string& serverName, unsigned short port, const std::string& message);
public:
    MonitorRequestHandlerDecorator(std::shared_ptr<IRequestHandler> handler, std::string server_addr, int port);

    // IRequestHandler interface
public:
    bool handle(std::shared_ptr<IHttpRequest> request, std::shared_ptr<IHttpResponse> response);
private:
    std::string convert_http_response_to_string(http::response<http::string_body> &res);
    std::string convert_http_request_to_string(http::request<http::string_body> &req);
};

#endif // MONITORREQUESTHANDLERDECORATOR_H
