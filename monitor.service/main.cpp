#include <iostream>
#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::udp;

class UdpReceiver {
public:
    UdpReceiver(uint16_t port) : io_context_{}, socket_{io_context_, udp::endpoint(udp::v4(), port)} {
        start_receive();
    }

    void run() {
        io_context_.run();
    }

private:
    boost::asio::io_context io_context_;
    udp::socket socket_;
    char buffer_[1024];

    void start_receive() {
        socket_.async_receive_from(
            boost::asio::buffer(buffer_), remote_endpoint_,
            [this](const boost::system::error_code& ec, std::size_t length) {
                if (!ec && length > 0) {
                    print_packet(length);
                    start_receive(); // Продолжаем ожидать следующий пакет
                } else {
                    std::cerr << "Receive error: " << ec.message() << "\n";
                }
            });
    }

    void print_packet(size_t len) {
        std::cout << ": " << std::string(buffer_, len) << std::endl;
    }

    udp::endpoint remote_endpoint_;
};

int main() {
    std::cout << "Monitor started\n" << std::endl;

    try {
        std::cout << "Monitor started\n" << std::endl;
        UdpReceiver receiver(8092); // Привязываемся к порту 8092
        receiver.run();              // Начинаем бесконечный цикл приёма пакетов
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
