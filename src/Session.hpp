#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <string>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    explicit Session(tcp::socket socket);
    void start();

private:
    void do_read();
    void do_write(std::size_t length);
    std::string make_response();

    tcp::socket socket_;
    enum { max_length = 1024 };
    char data_[max_length];
};
