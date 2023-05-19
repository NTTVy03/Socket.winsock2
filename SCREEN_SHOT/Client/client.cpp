// g++ client.cpp -o client.exe -lgdi32 -lws2_32
// ./client

const int BUFFER_SIZE = 1024;
#define MAX_LEN 5350000
#include <WinSock2.h>
#include <fstream>

using namespace std;

void SaveScreenShotToFile(SOCKET m_socket, char* filename) {
    // Nhan kich thuoc file
    streampos file_size;
    int bytes_received;
    do {
        bytes_received = recv(m_socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);
    } while (bytes_received == -1);
    
    // Tao file anh
    ofstream out(filename, ios::binary);
    char* buffer = new char[BUFFER_SIZE];
    int bytes_read = 0;

    // Nhan file anh
    while (bytes_read < file_size) {
        do {
            bytes_received = recv(m_socket, buffer, BUFFER_SIZE, 0);
        } while(bytes_received == -1);

        out.write(buffer, bytes_received);
        bytes_read += bytes_received;
        if (bytes_read == file_size) {
            break;
        }
    }

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
    char filename[] = "ScreenShot.bmp";
    SaveScreenShotToFile(m_socket, filename);
        
    // Close client socket
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();
}

int main() {
    ClientSocket();

    return 0;
}