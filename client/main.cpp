#include <iostream>
#include <winsock2.h>
#include<ws2tcpip.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

bool Initialize(){
    WSADATA data;
    return WSAStartup(MAKEWORD(2,2), &data) == 0;
}

int main(){
    //initialization
    if(!Initialize()){
        cout << "initialize winsock failed" << endl;
        return 1;
    }
    //socket creation
    SOCKET s;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s == INVALID_SOCKET){
        cout << "invalid socket" << endl;
        return 1;
    }

    //create address structure
    int port = 12345;
    string serveraddress = "127.0.0.1";
    sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    inet_pton(AF_INET,serveraddress.c_str(),&(serveraddr.sin_addr));

    //connect
    if(connect(s, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR){
        cout << "not able to connect to server" << endl;
        closesocket(s);
        WSACleanup();
        return 1;
    }
    cout << "succesfully connected to server" << endl;

    //send/recv
    cout << "client program started" << endl;
    string message = "hello there!";

    int bytesent;
    bytesent = send(s,message.c_str(), message.length(),0);
    if(bytesent == SOCKET_ERROR){
        cout << "send failed" << endl;
    }

    //closing
    closesocket(s);
    WSACleanup();
    return 0;
}