#include "scrshot.h"

void scrShot::SaveScreenShotToFile(char* filename) {
    // Lấy handle của màn hình chính
    HDC hScreen = GetDC(NULL);

    // Lấy chiều rộng và chiều cao của màn hình
    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    // Tạo một bitmap với kích thước bằng với màn hình
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, width, height);

    // Tạo một DC (device context) mới để vẽ lên bitmap
    HDC hDC = CreateCompatibleDC(hScreen);
    SelectObject(hDC, hBitmap);

    // Sử dụng hàm BitBlt để chụp màn hình vào bitmap
    BitBlt(hDC, 0, 0, width, height, hScreen, 0, 0, SRCCOPY);

    // Lưu bitmap vào file
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hDC, hBitmap);
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    BITMAPFILEHEADER bmfHeader = {0};
    bmfHeader.bfType = 0x4D42;
    bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmp.bmWidthBytes * bmp.bmHeight;
    bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    BITMAPINFOHEADER bi = {0};
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmp.bmWidth;
    bi.biHeight = bmp.bmHeight;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;
    char* pBuffer = new char[bmp.bmWidthBytes * bmp.bmHeight];
    GetDIBits(hDC, hBitmap, 0, bmp.bmHeight, pBuffer, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
    
    FILE* pFile = fopen(filename, "wb");
    fwrite(&bmfHeader, sizeof(BITMAPFILEHEADER), 1, pFile);
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, pFile);
    fwrite(pBuffer, bmp.bmWidthBytes * bmp.bmHeight, 1, pFile);
    fclose(pFile);
    delete[] pBuffer;

    // Giải phóng bộ nhớ
    SelectObject(hDC, hOldBitmap);
    DeleteDC(hDC);
    DeleteObject(hBitmap);
    ReleaseDC(NULL, hScreen);
}

void scrShot::ScreenShotAndSendToClient(SOCKET &ac_socket, char* filename) {
    SaveScreenShotToFile(filename);
    
    ifstream in(filename, ios::binary | ios::ate);
    streampos file_size = in.tellg();
    in.seekg(0, ios::beg);

    char* buffer = new char[BUFFER_SIZE];
    int bytes_sent = 0;

    // Gui kich thuoc file den server
    send(ac_socket, reinterpret_cast<char*>(&file_size), sizeof(streampos), 0);

    // Gui file anh den server
    while (!in.eof()) {
        in.read(buffer, BUFFER_SIZE);
        bytes_sent = send(ac_socket, buffer, BUFFER_SIZE, 0);
    }

    in.close();
    delete[] buffer;
}
