#ifndef HTTPSENDCONNECTION_H
#define HTTPSENDCONNECTION_H

#include "isendableconnection.h"
#include "ihttpresponse.h"

class HttpSendConnection: public ISendableConnection
{
    std::shared_ptr<SocketConnection> _connection;
    std::shared_ptr<IHttpResponse> _response;
public:
    HttpSendConnection( std::shared_ptr<SocketConnection> connection, std::shared_ptr<IHttpResponse> response):
        _connection(connection), _response(response)
    {};

    // IHttpSendConnection interface
public:
    void send()
    {
        http::write(_connection->socket(), _response->getResponse());
    }
};


#endif // HTTPSENDCONNECTION_H
