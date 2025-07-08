#include <iostream>
#include "Client.h"

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

    if (!client.SendMessage("hello there!")) {
        std::cerr << "Failed to send message\n";
    }

    client.Close();

    return 0;
}
