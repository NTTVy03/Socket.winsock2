// g++ server.cpp -o server.exe -lgdi32 -lws2_32
// ./server

const int BUFFER_SIZE = 1024;
# define MAX_LEN 5350000
#include <cstdio>
#include <winsock2.h>
#include <iostream>
#include <fstream>

using namespace std;

void SaveScreenShotToFile(char* filename) {
    // Lấy handle của màn hình chính
    HDC hScreen = GetDC(NULL);

    // Lấy chiều rộng và chiều cao của màn hình
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Tạo một bitmap với kích thước bằng với màn hình
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);

    // Tạo một DC (device context) mới để vẽ lên bitmap
    HDC hDC = CreateCompatibleDC(hScreen);
    SelectObject(hDC, hBitmap);

    // Sử dụng hàm BitBlt để chụp màn hình vào bitmap
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    // Lưu bitmap vào file
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    BITMAPFILEHEADER bmfHeader = {0};
    bmfHeader.bfType = 0x4D42;
    bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
    bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmp.bmWidth;
    bi.biHeight = bmp.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
    char* pBuffer = new char[bmp.bmWidthBytes * bmp.bmHeight];
    GetDIBits(hDC, hBitmap, 0, bmp.bmHeight, pBuffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    FILE* pFile = fopen(filename, "wb");
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);
    fwrite(pBuffer, bmp.bmWidthBytes * bmp.bmHeight, 1, pFile);
    fclose(pFile);
    delete[] pBuffer;

    // Giải phóng bộ nhớ
    SelectObject(hDC, hOldBitmap);
    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
}

void ScreenShotAndSendToClient(SOCKET &ac_socket, char* filename) {
    SaveScreenShotToFile(filename);
    
    ifstream in(filename, ios::binary | ios::ate);
    streampos file_size = in.tellg();
    in.seekg(0, ios::beg);

    char* buffer = new char[BUFFER_SIZE];
    int bytes_sent = 0;

    // Gui kich thuoc file den server
    send(ac_socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);

    // Gui file anh den server
    while (!in.eof()) {
        in.read(buffer, BUFFER_SIZE);
        bytes_sent = send(ac_socket, buffer, BUFFER_SIZE, 0);
    }

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
    char filename[] = "screenshot.bmp";
    
    ScreenShotAndSendToClient(ac_socket, filename);
   
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