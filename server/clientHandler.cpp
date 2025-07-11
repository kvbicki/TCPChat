#include "ClientHandler.h"
#include "Clients.h"

ClientHandler::ClientHandler(SOCKET socket, Clients& clientsRef) 
    : clientSocket(socket), clients(clientsRef) {}


void ClientHandler::Quit(){
    
}

void ClientHandler::HandleClient() {
    char buffer[4096];
    

    int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer) - 1, 0); 
    if (bytesRecvd <= 0) {
        std::cerr << "Failed to receive nickname. Error: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        return;
    }
    buffer[bytesRecvd] = '\0';
    nickname = std::string(buffer);


    if (!clients.addClient(clientSocket, nickname)) {
        std::cerr << "Failed to add client to list" << std::endl;
        closesocket(clientSocket);
        return;
    }

    std::string welcomeMsg = nickname + " has joined the chat.";
    std::cout << welcomeMsg << std::endl;
    clients.broadcast(welcomeMsg);

    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        bytesRecvd = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

        if (bytesRecvd > 0) {
            buffer[bytesRecvd] = '\0';
            std::string message(buffer);

            if (message == "/quit") {
                std::string leaveMsg = nickname + " has left the chat.";
                clients.broadcast(leaveMsg);
                std::cout << leaveMsg << std::endl;
                break;
            }
            else if (message == "/list"){
                clients.clientList(clientSocket);
            }

            else if (Client* sender = clients.findBySocket(clientSocket)) {
                clients.broadcast(sender, message);
                std::cout << "[" << nickname << "]: " << message << std::endl;
            }
        } 
        else if (bytesRecvd == 0) {
            std::cout << "Connection closed by " << nickname << std::endl;
            break;
        } 
        else {
            std::cerr << "recv failed for " << nickname << ". Error: " << WSAGetLastError() << std::endl;
            break;
        }
    }


    clients.remClient(clientSocket);
    shutdown(clientSocket, SD_BOTH);
    closesocket(clientSocket);
}