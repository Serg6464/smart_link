#include "HttpRequest.h"

HttpRequest::HttpRequest(std::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor)
    :m_acceptor(acceptor)
{
    m_socket = std::make_shared<boost::asio::ip::tcp::socket>(m_acceptor->get_executor());
}

HttpRequest::~HttpRequest()
{
    // Закрываем соединение
    if (m_socket != nullptr)
    {
        boost::beast::error_code ec;
        m_socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
    }
}

