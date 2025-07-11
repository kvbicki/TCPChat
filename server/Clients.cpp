#include "Clients.h"


bool Clients::addClient(SOCKET socket, const std::string& nickname) {
    std::lock_guard<std::mutex> lock(clientMutex);

    
    if (std::any_of(clients.begin(), clients.end(), 
        [&nickname](const Client& c) { return c.nickname == nickname; })) {
        return false;
    }
    
    clients.push_back(Client{socket, nickname});
    return true;
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
    std::lock_guard<std::mutex> lock(clientMutex);
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
bool Clients::clientList(SOCKET socket) {
    std::lock_guard<std::mutex> lock(clientMutex);
    
    if (clients.empty()) {
        const std::string msg = "Obecnie nie ma zadnych zalogowanych uzytkownikzw.\n";
        return send(socket, msg.c_str(), msg.size(), 0) != SOCKET_ERROR;
    }

    std::string message = "Zalogowani uzytkownicy (" + std::to_string(clients.size()) + "):\n";
    
    for (auto it = clients.begin(); it != clients.end(); ++it) {
        message += "- " + it->nickname;
        if (std::next(it) != clients.end()) {
            message += "\n"; 
        }
    }

    const int result = send(socket, message.c_str(), static_cast<int>(message.size()), 0);
    if (result == SOCKET_ERROR) {
        std::cerr << "Blad wysylania listy uzytkowników do socketa " << std::endl;
        return false;
    }

    return true;
}