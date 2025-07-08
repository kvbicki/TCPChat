#include "clientHandler.h"
#include <iostream>

ClientHandler::ClientHandler(SOCKET socket) : clientSocket(socket) {}

void ClientHandler::HandleClient() {
    char buffer[4096];
    int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecvd > 0) {
        std::string message(buffer, bytesRecvd);
        std::cout << "Message from client: " << message << std::endl;
    }
    else {
        std::cout << "recv failed or connection closed" << std::endl;
    }

    closesocket(clientSocket);
}
