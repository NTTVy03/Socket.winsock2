#pragma once

#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdlib.h>

#pragma comment(lib, "advapi32.lib")

using namespace std;

class App {
private:
public:
    static vector<string> listAllAppDemo();
    static bool TerminateProcessByName(const char* processName);
    static string ConvertExePath(const string& path);
    static bool runApp(string exePath);
}