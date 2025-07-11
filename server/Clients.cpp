#include "Clients.h"


void Clients::addClient(SOCKET socket, const std::string& nickname){
    clients.push_back(Client{socket,nickname});
}

Client* Clients::findBySocket(SOCKET socket){
    for(auto& client: clients){
        if(client.socket == socket){
            return &client;
        }
    }
}