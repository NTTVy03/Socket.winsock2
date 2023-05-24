#pragma once

#define MAX_CLIENTS 5
#define SERVER_IP "192.168.0.0.1"
#define SERVER_PORT "12345"

#include "../menu/menu.h"

class Server {
private:
    SOCKET m_socket;
    SOCKET ac_socket[MAX_CLIENTS];
    WSADATA wsaData;
public:
    // init - create - bind - listen
    Server();

    // connect - classify message
    void manage_AcSocket(int id_AcSocket);
    // process after recv Client request
    bool callFuncAndSendResponse(int id_AcSocket, const char* type, char* para[]);
    
    // manage all connection & request - response
    void manage_All();

    // send message
    bool sendSize(int id_AcSocket, int size);
    bool sendData(int id_AcSocket, const char* message);
    bool sendDatafromFile(int id_AcSocket, const char* filename);

    // recv message
    bool recvSize(int id_AcSocket, int &size);
    bool recvData(int id_AcSocket, char* &message);
    bool recvDataAndSaveToFile(int id_AcSocket, const char* filename);

};