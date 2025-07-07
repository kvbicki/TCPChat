cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# Dodaj client
add_executable(client
    client/main.cpp
)

# Dodaj server
add_executable(server
    server/main.cpp
)
