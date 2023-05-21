// g++ client.cpp -o client.exe -lgdi32 -lws2_32; ./client

const int BUFFER_SIZE = 1024;
#define MAX_LEN 5350000
#include <WinSock2.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// void recvData(SOCKET& socket, char* mess, int totalByte=1) {
//     int recvByte;
//     int curByte = 0;
//     do {
//         recvByte = recv(socket, mess, BUFFER_SIZE, 0);
//         // curByte += (recvByte < 0 ? 0 : recvByte);
//     } while (recvByte == -1); //(curByte < totalByte);
// }

void recvListFolder(SOCKET &m_socket) {
    const char* filename = "recv.txt";
    // Nhan kich thuoc file
    streampos file_size;
    int bytes_received;
    do {
        bytes_received = recv(m_socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);
    } while (bytes_received == -1);
    
    cout << "size: " << file_size << "\n";

    // Tao file anh
    ofstream out(filename, ios::binary);
    char* buffer = new char[BUFFER_SIZE];
    int bytes_read = 0;

    // Nhan file anh
    while (bytes_read < file_size) {
        int RECV_BUFF = BUFFER_SIZE;
        if (RECV_BUFF > (int)file_size - bytes_read)
            RECV_BUFF = (int)file_size - bytes_read;
        do {
            bytes_received = recv(m_socket, buffer, RECV_BUFF, 0);
        } while(bytes_received == -1);

        out.write(buffer, bytes_received);
        bytes_read += bytes_received;
        if (bytes_read == file_size) {
            break;
        }
    }

    cout << "Recv: " << bytes_read << "\n";
    out.close();
    delete[] buffer;
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