#define MAX_LEN 512
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

int main() {
    WORD verRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    int wsaErr = WSAStartup(verRequested, &wsaData);
    if (wsaErr != 0) {
        printf("WSAStartup fail - error: %d", wsaErr);
        return 0;
    }
    else
        printf("WSAStartup success - status: %s\n", wsaData.szSystemStatus);

    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("socket fail - error: ", WSAGetLastError());
        WSACleanup();
        return 0;
    }
    else
        printf("socket success\n");

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.1.1");
    service.sin_port = htons(12345); // [1024;49151]

    int connectErr = connect(m_socket, (SOCKADDR *)&service, sizeof(service));
    if (connectErr != 0) {
        printf("connect fail - error: ", WSAGetLastError());
        WSACleanup();
        return 0;
    }
    else
        printf("connect success\n");

    while (true) {
        // send msg
        char Smsg[MAX_LEN] = "";
        int sendBytes;

        // printf("Enter your message: ");
        printf("Client: ");
        scanf("%[^\n]s", Smsg);
        fflush(stdin);

        sendBytes = send(m_socket, Smsg, strlen(Smsg), 0);
        
        // printf("msg = .%s.\n", Smsg);
        // printf("Send %d/%d bytes\n", sendBytes, strlen(Smsg));
        
        if (strcmp(Smsg, "x") == 0)
            break;

        // receive msg
        char Rmsg[MAX_LEN] = "";
        int recvBytes;

        do {
            recvBytes = recv(m_socket, Rmsg, MAX_LEN, 0);
        } while (recvBytes == SOCKET_ERROR);
        
        if (recvBytes == 0) {
            printf("Connection closed\n");
            break;
        } 
        else {
            // printf("Recv msg = %s - Length: %d\n", Rmsg, recvBytes);
            printf("Server: %s\n", Rmsg);

            if (strcmp(Rmsg, "x") == 0)
                break;
        }

    }

    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();

    return 0;
}