#pragma once
#include <WinSock2.h>
#include<ws2tcpip.h>
#include <thread>

class Server {
private:
    SOCKET listenSocket;
    int port;

public:
    Server(int port);
    ~Server();

    bool Initialize();
    bool Setup();
    void Run();
};
