const int BUFFER_SIZE = 1024;
#include <WinSock2.h>
#include <fstream>

using namespace std;

class keyDown {
public:
    static void sendRequest();
    static void RecvKeyDesc(SOCKET& m_socket, char* filename);
};
