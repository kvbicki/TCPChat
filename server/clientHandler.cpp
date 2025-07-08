#include "ClientHandler.h"
#include <iostream>

ClientHandler::ClientHandler(SOCKET socket) : clientSocket(socket) {}

void ClientHandler::HandleClient() {
    char buffer[4096];
    int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecvd > 0) {
        std::string message(buffer, bytesRecvd);
        std::cout << "Message from client: " << message << std::endl;
        if(message == "quit"){
            closesocket(clientSocket);
        }
    }
    else {
        std::cout << "recv failed or connection closed" << std::endl;
    }

}
