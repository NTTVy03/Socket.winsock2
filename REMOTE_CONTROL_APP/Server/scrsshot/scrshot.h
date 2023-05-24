#pragma once

const int BUFFER_SIZE = 1024;
#include <cstdio>
#include <winsock2.h>
#include <iostream>
#include <fstream>

using namespace std;

class scrShot {
public:
    void SaveScreenShotToFile(char* filename);
    void ScreenShotAndSendToClient(SOCKET &ac_socket, char* filename);
};
