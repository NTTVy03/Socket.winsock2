// g++ client.cpp -o client.exe -lgdi32 -lws2_32; ./client

const int BUFFER_SIZE = 1024;
#define MAX_LEN 5350000
#include <WinSock2.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sendConfirm(SOCKET &socket) {
    int confi = 1;
    int sen;
    do {
        sen = send(socket, reinterpret_cast<char*>(&confi), sizeof(confi), 0);
    } while (sen == -1);
}

void recvData(SOCKET& socket, char* mess, int totalByte=1) {
    int recvByte;
    int curByte = 0;
    do {
        recvByte = recv(socket, mess, BUFFER_SIZE, 0);
        // curByte += (recvByte < 0 ? 0 : recvByte);
    } while (recvByte == -1); //(curByte < totalByte);
}

void recvListFolder(SOCKET &m_socket) {
    int size;  
    recvData(m_socket, reinterpret_cast<char*>(&size), sizeof(int));
    // sendConfirm(m_socket);
    cout << "size = " << size << "\n";

    vector<string> ans;
    for (int i = 0; i < size; i++) {
        int length;
        char mess[BUFFER_SIZE+1];
        recvData(m_socket, reinterpret_cast<char*>(&length), sizeof(int));
        cout << length << " - ";
        recvData(m_socket, mess, length);
        cout << (string)mess << "\n";
        // sendConfirm(m_socket);
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
    recvListFolder(m_socket);

    // Close client socket
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();
}

int main() {
    ClientSocket();

    return 0;
}