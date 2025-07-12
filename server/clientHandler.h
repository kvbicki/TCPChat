#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>
#include "Clients.h"
#include <sstream>

class ClientHandler {
private:
    SOCKET clientSocket;
    std::string nickname;
    Clients& clients;

public:
    ClientHandler(SOCKET socket,Clients& clientsRef);
    void HandleClient();
    void Quit();
};
