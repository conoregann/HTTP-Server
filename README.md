# Simple C++ Web Server

A high-performance, multi-threaded HTTP server implemented in C++ using Boost.Asio.

## Features
- **Asynchronous I/O**: Uses `boost::asio` for non-blocking network operations.
- **Multithreading**: Runs the `io_context` on a thread pool to handle multiple requests concurrently.
- **Clean Architecture**: Separates `Server` (acceptor) and `Session` (connection handling) logic.
- **Memory Management**: Uses `std::shared_ptr` and `std::enable_shared_from_this` for safe object lifetime management.

## Prerequisites
- C++17 compliant compiler (GCC, Clang, MSVC)
- CMake 3.14+
- Boost Libraries (specifically `boost::system` and `boost::asio`)

### Installing Dependencies (macOS)
```bash
brew install cmake boost
```

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

## Running the Server
```bash
./web_server 8080
```

## Testing
Open a browser and visit `http://localhost:8080` or use curl:
```bash
curl -v http://localhost:8080
```
