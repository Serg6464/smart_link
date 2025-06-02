#include "httprequest.h"
#include <boost/beast/core.hpp>

HttpRequest::HttpRequest(const std::string& raw_request)
{
    // Создаем буфер для парсинга
    boost::beast::multi_buffer buffer;
    boost::beast::error_code ec;
    buffer.commit(raw_request.size());
    boost::beast::ostream(buffer) << raw_request.data();

    // Парсим запрос
    http::request_parser<http::string_body> parser;
    parser.eager( true );
    parser.put(buffer.data(), ec);
    //request_ = parser.release();
}



