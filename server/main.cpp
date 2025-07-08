#include "Server.h"
#include <iostream>

int main() {
    Server server(12345);

    if (!server.Initialize()) {
        std::cerr << "Winsock initialization failed" << std::endl;
        return 1;
    }

    if (!server.Setup()) {
        std::cerr << "Server setup failed" << std::endl;
        return 1;
    }

    server.Run();

    return 0;
}
