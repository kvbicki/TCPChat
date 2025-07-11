#pragma once
#include <WinSock2.h>
#include<ws2tcpip.h>
#include <thread>
#include <string>
#include <iostream>
#include "Clients.h"
#include "clientHandler.h"

class Server {
private:
    SOCKET listenSocket;
    int port;
    Clients clients;
public:
    Server(int port);
    ~Server();

    bool Initialize();
    bool Setup();
    bool SendMessage(const std::string& message, SOCKET clientSocket);
    void Run();
    
};
