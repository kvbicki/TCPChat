#include "Server.h"
#include "ClientHandler.h"
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

Server::Server(int p) : port(p), listenSocket(INVALID_SOCKET) {}

Server::~Server() {
    if (listenSocket != INVALID_SOCKET) {
        closesocket(listenSocket);
    }
    WSACleanup();
}

bool Server::Initialize() {
    WSADATA data;
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

bool Server::Setup() {
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, "0.0.0.0", &serverAddr.sin_addr) != 1) {
        std::cerr << "Setting address failed" << std::endl;
        return false;
    }

    if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed" << std::endl;
        closesocket(listenSocket);
        return false;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed" << std::endl;
        return false;
    }

    std::cout << "Server listening on port: " << port << std::endl;
    return true;
}

void Server::Run() {
    while (true) {
        SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }

        std::cout << "Client connected!" << std::endl;

        std::thread t([clientSocket]() {
            ClientHandler handler(clientSocket);
            handler.HandleClient();
        });
        t.detach();
    }
}