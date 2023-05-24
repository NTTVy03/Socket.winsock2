#pragma once

#include "../menu/menu.h"

class Client {
private:
    // ...
    SOCKET m_socket;
public:
    Client(); // init socket & ... here
    ~Client();

    void connect();
    
    void send(const char* mess, int size);
    char* recv(int &size);
};