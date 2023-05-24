// g++ *.cpp -o server.exe -lgdi32 -lws2_32 -lftdc++fs; ./server

// vector<string> --> string --> const char*

const int BUFFER_SIZE = 1024;
# define MAX_LEN 5350000
#include <cstdio>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "FolderTask.h"

using namespace std;

void recvConfirm(SOCKET &socket) {
    int conf;
    int rec;
    do {
        rec = recv(socket, reinterpret_cast<char*>(&conf), BUFFER_SIZE, 0);
    } while (rec == -1);
}

// Hàm gửi dữ liệu bằng socket
bool send_data(SOCKET &socket, const char* data, int size) {
    int total_sent = 0;
    while (total_sent < size) {
        int sent = send(socket, data + total_sent, size - total_sent, 0);
        if (sent == -1) {
            std::cerr << "Error sending data\n";
            return false;
        }
        total_sent += sent;
    }
    cout << "Total send: " << total_sent << "/" << size << "\n";
    return true;
}

void sendListFolder(SOCKET &socket) {
    const char* filename = "DirectoryManager.txt";
    // lay danh sach file/folder
    FolderTask* f = new FolderTask;
    string ans;
    // string ans = f->tab_recursive_list_files("D:/DELETE_THIS_FOLDER", 0);
    
    // ghi ket qua vao file
    std::ofstream out(filename);
    out << ans;
    out.close();

    // truyen file qua socket
    ifstream in(filename, ios::binary | ios::ate);
    streampos file_size = in.tellg();
    cout << "size: " << file_size << "\n";
    in.seekg(0, ios::beg);

    char* buffer = new char[BUFFER_SIZE];
    int bytes_sent = 0;

    // Gui kich thuoc file den server
    send(socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);

    // Gui file anh den server
    while (!in.eof()) {
        int SEND_BUFF = BUFFER_SIZE;
        if (SEND_BUFF > (int)file_size - bytes_sent)
            SEND_BUFF = (int)file_size - bytes_sent;
        in.read(buffer, SEND_BUFF);
        bytes_sent = send(socket, buffer, SEND_BUFF, 0);
    }

    cout << "Send: " << bytes_sent << "\n";

    in.close();
    delete[] buffer;
}

void ServerSocket() {
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

    // Create server socket
    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("socket fail - error: ", WSAGetLastError());
        WSACleanup();
        exit(-2);
    }
    else
        printf("socket success\n");

    // Bind server socket
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.1.1");
    service.sin_port = htons(12345); // [1024;49151]

    int bindErr = bind(m_socket, (SOCKADDR *)&service, sizeof(service));
    if (bindErr != 0) {
        printf("bind fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        exit(-3);
    }
    else
        printf("bind success\n");

    // Listen to Client request
    int listenErr = listen(m_socket, 1);
    if (bindErr != 0) {
        printf("listen fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        exit(-4);
    }
    else
        printf("listen success\n");

    printf("Server is waiting for Client...\n");

    // Connect Client
    SOCKET ac_socket;

    // --------- CONNECT CLIENT: START -------------
    // Connect accept socket (with 1 Client)
    ac_socket = accept(m_socket, NULL, NULL);
    if (ac_socket == INVALID_SOCKET) {
        printf("conect fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        exit(-5);
    }
    else
        printf("connect success\n");

    // Do something with Client
    sendListFolder(ac_socket);
   
    // Close accept socket (with 1 Client)
    closesocket(ac_socket);
    printf("Close ac_socket\n");
    // --------- CONNECT CLIENT: FINISH -------------

    // Close server socket
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();
}

void test() {
    FolderTask *f = new FolderTask();
    string ans = f->tab_recursive_list_files("D:/DELETE_THIS_FOLDER", 0);
    cout << ans;

    // cout << f->isFolder("D:/HK2_NAM2/BUCHA/quanLyCongViec.xlsx") << "\n";
    // cout << f->isFolder("D:/HK2_NAM2/BUCHA/") << "\n";
    delete f;
}

int main() {
    // ServerSocket();
    
    test();
    return 0;
}