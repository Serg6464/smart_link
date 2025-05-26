#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <memory>

class HttpRequest;
using HttpRequestPtr = std::shared_ptr<HttpRequest>;

class HttpRequest
{
    std::shared_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;

    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
    boost::beast::flat_buffer m_buffer;
    boost::beast::http::request<boost::beast::http::string_body> m_request;
    boost::beast::error_code m_error;

public:
    HttpRequest(std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor);
    ~HttpRequest();

    std::shared_ptr<boost::asio::ip::tcp::socket> socketptr() { return m_socket; }

    boost::asio::ip::tcp::acceptor& acceptor() { return *m_acceptor; }
    boost::asio::ip::tcp::socket& socket() { return *m_socket; }
    boost::beast::flat_buffer& buffer() { return m_buffer; }
    boost::beast::http::request<boost::beast::http::string_body>& request() { return m_request; }
    boost::beast::error_code& error() { return m_error; }
};

#endif // HTTPREQUEST_H
