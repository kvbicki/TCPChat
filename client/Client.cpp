#include "Client.h"
#include <iostream>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

Client::Client(const std::string& serverAddress, int port)
    : serverAddress(serverAddress), port(port), sock(INVALID_SOCKET), initialized(false)
{}

Client::~Client() {
    Close();
}

bool Client::Initialize() {
    WSADATA data;
    initialized = (WSAStartup(MAKEWORD(2, 2), &data) == 0);
    return initialized;
}

bool Client::Connect() {
    if (!initialized) {
        std::cerr << "Winsock not initialized\n";
        return false;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed\n";
        return false;
    }

    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    if (inet_pton(AF_INET, serverAddress.c_str(), &serveraddr.sin_addr) != 1) {
        std::cerr << "Invalid address\n";
        closesocket(sock);
        return false;
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed\n";
        closesocket(sock);
        return false;
    }

    std::cout << "Successfully connected to server\n";
    return true;
}

bool Client::SendMessage(const std::string& message) {
    int bytesSent = send(sock, message.c_str(), static_cast<int>(message.size()), 0);
    if (bytesSent == SOCKET_ERROR) {
        std::cerr << "Send failed\n";
        return false;
    }
    return true;
}
bool Client::ReceiveMessage(std::string& message) {
    char buffer[1024];
    int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // zakończ string
        message = buffer;
        return true;
    } else if (bytesReceived == 0) {
        std::cerr << "Connection closed by server\n";
    }
    return false;
}


void Client::Close() {
    if (sock != INVALID_SOCKET) {
        closesocket(sock);
        sock = INVALID_SOCKET;
    }
    if (initialized) {
        WSACleanup();
        initialized = false;
    }
}
