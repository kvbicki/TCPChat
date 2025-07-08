#include "ClientHandler.h"
#include <iostream>

ClientHandler::ClientHandler(SOCKET socket) : clientSocket(socket) {}

void ClientHandler::HandleClient() {

    char buffer[4096];
    int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecvd <= 0) {
        std::cout << "Failed to receive nickname." << std::endl;
        closesocket(clientSocket);
        return;
    }
    nickname = std::string(buffer, bytesRecvd);
    std::cout << "Client connected with nickname: " << nickname << std::endl;

    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRecvd > 0) {
            std::string message(buffer, bytesRecvd);
            if (message == "quit") {
                std::cout << nickname << " disconnected." << std::endl;
                break;
            }
            std::cout << "[" << nickname << "]: " << message << std::endl;
        } else {
            std::cout << "recv failed or connection closed by " << nickname << std::endl;
            break;
        }
    }

    shutdown(clientSocket, SD_BOTH);
    closesocket(clientSocket);
}
