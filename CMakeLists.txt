cmake_minimum_required(VERSION 3.14)
project(SimpleWebServer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

add_executable(web_server
    src/main.cpp
    src/Server.cpp
    src/Session.cpp
)

target_include_directories(web_server PRIVATE src)
target_link_libraries(web_server PRIVATE Boost::system)

# Enable some warnings
if(MSVC)
    target_compile_options(web_server PRIVATE /W4 /WX)
else()
    target_compile_options(web_server PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
