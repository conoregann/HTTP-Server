#include <boost/asio.hpp>
#include <iostream>
#include <vector>
#include <thread>
#include "Server.hpp"

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Usage: web_server <port>\n";
            return 1;
        }

        boost::asio::io_context io_context;

        Server s(io_context, std::atoi(argv[1]));

        // Run the I/O context on multiple threads
        std::vector<std::thread> threads;
        // Use hardware concurrency to determine thread count, or default to 4
        auto count = std::thread::hardware_concurrency();
        if (count == 0) count = 4;
        
        std::cout << "Starting server on port " << argv[1] << " with " << count << " threads...\n";

        for (unsigned int i = 0; i < count; ++i) {
            threads.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        for (auto& t : threads) {
            t.join();
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
