#ifndef HTTPREADSOCKETCONNECTION_H
#define HTTPREADSOCKETCONNECTION_H

#include "ireadableconnection.h"
#include "ihttprequest.h"

class HttpReadSocketConnection: public IReadableConnection
{
    std::shared_ptr<HttpConnection> _connection;
    std::shared_ptr<IHttpRequest> _request;
public:
    HttpReadSocketConnection( std::shared_ptr<HttpConnection> connection, std::shared_ptr<IHttpRequest> request):
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


#endif // HTTPREADSOCKETCONNECTION_H
