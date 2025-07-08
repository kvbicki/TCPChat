#include "ClientHandler.h"
#include <iostream>

ClientHandler::ClientHandler(SOCKET socket) : clientSocket(socket) {}

void ClientHandler::HandleClient() {
    while(true){
        char buffer[4096];
        int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRecvd > 0) {
            std::string message(buffer, bytesRecvd);
            std::cout << "Message from client: " << message << std::endl;
            if(message == "quit"){
                std::cout << "Client disconnected!" << std::endl;
                break;
            }
        }
        else {
            std::cout << "recv failed or connection closed" << std::endl;
        }
    }
    shutdown(clientSocket,SD_BOTH);
    closesocket(clientSocket);
}
