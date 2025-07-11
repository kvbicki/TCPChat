#include "ClientHandler.h"
#include "Clients.h"

ClientHandler::ClientHandler(SOCKET socket, Clients& clientsRef) : clientSocket(socket), clients(clientsRef){}

void ClientHandler::HandleClient() {
    char buffer[4096];
    int bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRecvd <= 0) {
        std::cout << "Failed to receive nickname." << std::endl;
        closesocket(clientSocket);
        return;
    }

    nickname = std::string(buffer, bytesRecvd);
    clients.addClient(clientSocket,nickname);
    std::string m = "Client connected with nickname " + nickname;
    std::cout << m << std::endl;
    clients.broadcast(m);

    while (true) {
        ZeroMemory(buffer, sizeof(buffer));
        bytesRecvd = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRecvd > 0) {
            
            std::string message(buffer, bytesRecvd);
            if (message == "quit") {
                m = nickname + " disconnected.";
                clients.broadcast(m);
                std::cout << nickname << " disconnected." << std::endl;
                
                break;
            }
            clients.broadcast(clients.findBySocket(clientSocket),message);
            std::cout << "[" << nickname << "]: " << message << std::endl;

        } else {
            std::cout << "recv failed or connection closed by " << nickname << std::endl;
            break;
        }
    }

    shutdown(clientSocket, SD_BOTH);
    closesocket(clientSocket);
}
