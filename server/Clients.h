#include <iostream>
#include <string>
#include <winsock2.h>
#include <vector>
#pragma once

struct Client{
    SOCKET socket;
    std::string nickname;
};


class Clients{
private:
    std::vector<Client> clients;
public:
    Clients(){};
    void addClient(SOCKET socket, const std::string& nickname);
    void remClient(SOCKET socket);
    Client* findBySocket(SOCKET socket);
    void broadcast(Client *client,const std::string& message);
    void broadcast(const std::string& message);
};