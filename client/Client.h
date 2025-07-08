#pragma once
#include <winsock2.h>
#include <string>

class Client {
public:
    Client(const std::string& serverAddress, int port);
    ~Client();

    bool Initialize();
    bool Connect();
    bool SendMessage(const std::string& message);
    bool ReceiveMessage(std::string& message);
    void Close();

private:
    std::string serverAddress;
    int port;
    SOCKET sock;
    bool initialized;
};
