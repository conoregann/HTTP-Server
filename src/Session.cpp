#include "Session.hpp"
#include <iostream>
#include <sstream>

Session::Session(tcp::socket socket)
    : socket_(std::move(socket)) {
}

void Session::start() {
    do_read();
}

void Session::do_read() {
    auto self(shared_from_this());
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        [this, self](boost::system::error_code ec, std::size_t length) {
            if (!ec) {
                // Simple check to see if we have a full request or just print what we got
                // In a real server, we'd parse until we find \r\n\r\n
                // For this demo, we assume the request fits in one read and we just reply.
                
                // Print request for debugging
                std::cout << "Received Request:\n";
                std::cout.write(data_, length);
                std::cout << "\n----------------\n";

                do_write(length);
            }
        });
}

void Session::do_write(std::size_t /*length*/) {
    auto self(shared_from_this());
    
    std::string response = make_response();

    boost::asio::async_write(socket_, boost::asio::buffer(response),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                // Initiate graceful shutdown
                boost::system::error_code ignored_ec;
                socket_.shutdown(tcp::socket::shutdown_both, ignored_ec);
            }
        });
}

std::string Session::make_response() {
    std::string body = "<html><body><h1>Hello from C++ Boost.Asio Server!</h1></body></html>";
    std::ostringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n";
    response_stream << "Content-Length: " << body.size() << "\r\n";
    response_stream << "Content-Type: text/html\r\n";
    response_stream << "Connection: close\r\n";
    response_stream << "\r\n";
    response_stream << body;
    return response_stream.str();
}
