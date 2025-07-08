cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# client
add_executable(client
    client/main.cpp
)

# server
add_executable(server
    server/main.cpp
    server/server.cpp
    server/clientHandler.cpp
)
