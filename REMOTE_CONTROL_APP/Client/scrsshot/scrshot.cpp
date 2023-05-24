#include "scrshot.h"

void scrShot::SaveScreenShotToFile(SOCKET& m_socket, char* filename) {
    // Nhan kich thuoc file
    streampos file_size;
    int bytes_received;
    do {
        bytes_received = recv(m_socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);
    } while (bytes_received == -1);
    
    // Tao file anh
    ofstream out(filename, ios::binary);
    char* buffer = new char[BUFFER_SIZE];
    int bytes_read = 0;

    // Nhan file anh
    while (bytes_read < file_size) {
        do {
            bytes_received = recv(m_socket, buffer, BUFFER_SIZE, 0);
        } while(bytes_received == -1);

        out.write(buffer, bytes_received);
        bytes_read += bytes_received;
        if (bytes_read == file_size) {
            break;
        }
    }

    out.close();
    delete[] buffer;
}
