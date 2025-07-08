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

    std::string msgs;
    std::string msgr;

    while (true) {
        if (!client.ReceiveMessage(msgr)) {
            std::cerr << "Failed to receive message or connection closed.\n";
            break;
        }

        std::cout << "Server: " << msgr << std::endl;

        std::getline(std::cin, msgs);
        if (msgs == "quit") break;

        if (!client.SendMessage(msgs)) {
            std::cerr << "Failed to send message\n";
            break;
        }
    }

    std::cout << "Bye!" << std::endl;
    client.Close();

    return 0;
}
