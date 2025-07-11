#include "Clients.h"


void Clients::addClient(SOCKET socket, const std::string& nickname){
    std::lock_guard<std::mutex> lock(clientMutex);
    clients.push_back(Client{socket,nickname});
}

Client* Clients::findBySocket(SOCKET socket){
    for(auto& client: clients){
        if(client.socket == socket){
            return &client;
        }
    }
    return nullptr;
}

void Clients::remClient(SOCKET socket){
    std::lock_guard<std::mutex> lock(clientMutex);
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

void Clients::broadcast(const std::string& message) {
    std::lock_guard<std::mutex> lock(clientMutex);
    for (auto it = clients.begin(); it != clients.end(); ) {
        int bytesSent = send(it->socket, message.c_str(), message.size(), 0);
        if (bytesSent == SOCKET_ERROR) {
            it = clients.erase(it); 
        } else {
            ++it;
        }
    }
}