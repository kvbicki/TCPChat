#include <iostream>
#include "Client.h"
#include <string>
#include <thread>
#include <atomic>

std::atomic<bool> running{true};

void receiveThreadFunc(Client& client) {
    std::string msgr;
    while (running) {
        if (!client.ReceiveMessage(msgr)) {
            std::cerr << "Failed to receive message or connection closed.\n";
            running = false;
            break;
        }
        std::cout << "Server: " << msgr << std::endl;
    }
}

void sendThreadFunc(Client& client) {
    std::string msgs;
    while (running) {
        std::getline(std::cin, msgs);
        if (msgs == "quit") {
            client.Close();
            running = false;
            break;
        }
        if (!client.SendMessage(msgs)) {
            std::cerr << "Failed to send message\n";
            running = false;
            break;
        }
    }
}

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

    std::thread receiver(receiveThreadFunc, std::ref(client));
    std::thread sender(sendThreadFunc, std::ref(client));

    sender.join();
    running = false;
    receiver.join();

    return 0;
}