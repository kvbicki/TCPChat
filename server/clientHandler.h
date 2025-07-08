#pragma once
#include <WinSock2.h>

class ClientHandler {
private:
    SOCKET clientSocket;

public:
    ClientHandler(SOCKET socket);
    void HandleClient();
};
