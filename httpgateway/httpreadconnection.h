#ifndef HTTPREADCONNECTION_H
#define HTTPREADCONNECTION_H

#include "ireadableconnection.h"
#include "ihttprequest.h"

class HttpReadConnection: public IReadableConnection
{
    std::shared_ptr<SocketConnection> _connection;
    std::shared_ptr<IHttpRequest> _request;
public:
    HttpReadConnection( std::shared_ptr<SocketConnection> connection, std::shared_ptr<IHttpRequest> request):
        _connection(connection), _request(request)
    {};

    // IHttpReadConnection interface
public:
     void read()
    {
        boost::beast::flat_buffer buffer;
        boost::beast::error_code er;
        http::read(_connection->socket(), buffer, *_request->getRequest(), er);
    }
};


#endif // HTTPREADCONNECTION_H
