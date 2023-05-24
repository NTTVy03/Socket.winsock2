const int BUFFER_SIZE = 1024;
#include <WinSock2.h>
#include <fstream>

using namespace std;

class scrShot {
public:
    static void go();
    static void SaveScreenShotToFile(SOCKET& m_socket, char* filename);
};
