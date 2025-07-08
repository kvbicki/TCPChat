#include <iostream>
#include "Client.h"
#include <string>

int main() {
    Client client("127.0.0.1", 12345);

    if (!client.Initialize()) {
        std::cerr << "Failed to initialize Winsock\n";
        return 1;
    }

    if (!client.Connect()) {
        std::cerr << "Failed to connect to server\n";
        return 1;
    }

    std::cout << "Client program started\n";

    while(true){
        std::string msg;
        std::getline(std::cin, msg);
        if (!client.SendMessage(msg)) {
            std::cerr << "Failed to send message\n";
        }
    }
    client.Close();

    return 0;
}
