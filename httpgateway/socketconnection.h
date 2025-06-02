#ifndef SOCKETCONNECTION_H
#define SOCKETCONNECTION_H

#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>

//namespace http = boost::beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class SocketConnection
{
    std::shared_ptr<tcp::socket> _socket;
public:
    SocketConnection(std::shared_ptr<tcp::socket> socket):
        _socket(std::move(socket))
    { }
    tcp::socket & socket()
    {
        return *_socket;
    }
    ~SocketConnection()
    {
        // Закрываем соединение
        if (_socket != nullptr)
        {
            boost::beast::error_code ec;
            _socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        }
    }
};

#endif // SOCKETCONNECTION_H
