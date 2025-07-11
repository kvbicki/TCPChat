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

void Clients::remClient(SOCKET socket){
    for (auto it = clients.begin(); it != clients.end(); ) {
        if (it->socket == socket) {
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}
void Clients::broadcast(Client *client,const std::string& message){

    std::string fullMessage = "[" + client->nickname + "]: " + message;
    for (auto& c: clients){
        int bytesSent = send(c.socket, fullMessage.c_str(), static_cast<int>(fullMessage.size()), 0);
    }
}

void Clients::broadcast(const std::string& message){
    for (auto& c: clients){
        int bytesSent = send(c.socket, message.c_str(), static_cast<int>(message.size()), 0);
    }
}