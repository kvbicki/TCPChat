#pragma once
#include <WinSock2.h>
#include <iostream>
#include <string>

class ClientHandler {
private:
    SOCKET clientSocket;
    std::string nickname;

public:
    ClientHandler(SOCKET socket);
    void HandleClient();
};
