// g++ client.cpp -o client.exe -lgdi32 -lws2_32; ./client

const int BUFFER_SIZE = 1024;
#define MAX_LEN 5350000
#include <WinSock2.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void recvData(SOCKET& socket, char* mess) {
    int recvByte;
    int totalByte;
    do {
        recvByte = recv(socket, reinterpret_cast<char*>(&totalByte), sizeof(int), 0);
    } while (recvByte == -1);

    cout << "total: " << totalByte << " - ";
    int curByte = 0;
    while (curByte < totalByte)
    {
        do {
            recvByte = recv(socket, mess+curByte, totalByte-curByte, 0);
        } while (recvByte == -1);
        curByte += recvByte;
        cout << mess << "\n";
    }
    
    
    cout << mess << "\n";
}

void recvKeyDown(SOCKET &socket) {
    // while (true)
    {
        char* mess;
        recvData(socket, mess);
        // cout << mess << "\n";
    } 
}

void ClientSocket() {
    // Set up WSA
    WORD verRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    int wsaErr = WSAStartup(verRequested, &wsaData);
    if (wsaErr != 0) {
        printf("WSAStartup fail - error: %d", wsaErr);
        exit(-1);
    }
    else
        printf("WSAStartup success - status: %s\n", wsaData.szSystemStatus);

    // Create client socket
    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("socket fail - error: ", WSAGetLastError());
        WSACleanup();
        exit(-2);
    }
    else
        printf("socket success\n");
    
    // Connect Server
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.1.1");
    service.sin_port = htons(12345); // [1024;49151]

    int connectErr = connect(m_socket, (SOCKADDR *)&service, sizeof(service));
    if (connectErr != 0) {
        printf("connect fail - error: ", WSAGetLastError());
        WSACleanup();
        exit(-3);
    }
    else
        printf("connect success\n");

    // Do someting with Server  
    recvKeyDown(m_socket);

    // Close client socket
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();
}

int main() {
    ClientSocket();

    return 0;
}

