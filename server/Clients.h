#include <iostream>
#include <string>
#include <winsock2.h>
#include <vector>

struct Client{
    SOCKET socket;
    std::string nickname;
};


class Clients{
private:
    std::vector<Client> clients;
public:
    void addClient(SOCKET socket, const std::string& nickname);
    void remClient(SOCKET socket);
    void findBySocket(SOCKET socket);
    void broadcast();
};