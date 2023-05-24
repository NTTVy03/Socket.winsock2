#include "app.h"

// list app
vector<string> App::listAllAppDemo()
{
    std::vector<std::string> installed_programs;

    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths", 0, KEY_READ | KEY_WOW64_32KEY, &hKey) != ERROR_SUCCESS) {
        std::cerr << "Failed to open registry key" << std::endl;
        return installed_programs;
    }

    char szDisplayName[1024];
    char szKeyName[1024];
    DWORD dwSize = sizeof(szDisplayName);

    for (DWORD i = 0, retValue = ERROR_SUCCESS; retValue == ERROR_SUCCESS; ++i) {
        retValue = RegEnumKeyEx(hKey, i, szKeyName, &dwSize, NULL, NULL, NULL, NULL);
        dwSize = sizeof(szKeyName);

        if (retValue == ERROR_SUCCESS) {
            HKEY hSubKey;
            if (RegOpenKeyEx(hKey, szKeyName, 0, KEY_READ | KEY_WOW64_32KEY, &hSubKey) == ERROR_SUCCESS) {
                dwSize = sizeof(szDisplayName);
                if (RegQueryValueEx(hSubKey, NULL, NULL, NULL, (LPBYTE)szDisplayName, &dwSize) == ERROR_SUCCESS) {
                    installed_programs.push_back(szDisplayName);
                }
                RegCloseKey(hSubKey);
            }
        }
    }

    RegCloseKey(hKey);

    installed_programs.erase(unique(installed_programs.begin(), installed_programs.end()), installed_programs.end());

    int cnt = 0;
    for (;cnt < installed_programs.size();)
    {
        installed_programs[cnt].erase(remove(installed_programs[cnt].begin(), installed_programs[cnt].end(), '\"'), installed_programs[cnt].end());
        string program = installed_programs[cnt];
        std::cout << ++cnt << ". " << program << std::endl;
    }

    return installed_programs;
}

// chạy app bằng đường dẫn
bool App::runApp(string exePath)
{
    std::string convertedPath = ConvertExePath(exePath);
    // cout<<convertedPath<<endl;

    bool isSuccess = ShellExecute(NULL, "open", convertedPath.c_str(), NULL, NULL, SW_SHOWNORMAL);
    return isSuccess;
}

// đóng app bằng tên
bool App::TerminateProcessByName(const char* processName) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return false;
    }

    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &pe)) {
        CloseHandle(hSnapshot);
        return false;
    }

    bool found = false;
    do {
        if (_stricmp(pe.szExeFile, processName) == 0) {
            found = true;
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0, pe.th32ProcessID);
            if (hProcess != NULL) {
                TerminateProcess(hProcess, 0);
                CloseHandle(hProcess);
            }
        }
    } while (Process32Next(hSnapshot, &pe));

    CloseHandle(hSnapshot);
    return found;
}

// chuẩn hóa đường dẫn file exe
string App::ConvertExePath(const string& path)
{
    string convertedPath;
    char expandedPath[MAX_PATH];
    ExpandEnvironmentStrings(path.c_str(), expandedPath, MAX_PATH);
    string newPath = string(expandedPath);
    for (char c : newPath)
        if (c == '\\')
            convertedPath += "\\\\";
        else
            convertedPath += c;

    return convertedPath;
}