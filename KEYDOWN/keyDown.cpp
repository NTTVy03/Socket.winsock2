// g++ keydown.cpp -o keydown.exe; ./keydown

#include <iostream>
#include <windows.h>
// Nhận xét chung:
// 1.1 Bị sót chữ nếu gõ nhanh (vì sleep 100ms)
// 1.2 Bị lặp chữ nến nhấn giữ lâu > 100ms (vì sleep 100ms)
// 2. Kí tự có dấu -> mất chữ
// 3. Bàn phím số (bên phải)
// chữ hoa - thường
// ,./;''
// kí hiệu (Shift + phím) 
// -> không chính xác

// Hàm kiểm tra xem Caps Lock có được bật hay không
bool isCapsLock()
{
    // Kiểm tra xem Caps Lock có được bật hay không
    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0) // Nếu bit thấp nhất là 1, phím được bật
        return true;
    else
        return false;
}

// Hàm kiểm tra xem Shift có được nhấn hay không
bool isShift()
{
    // Kiểm tra xem Shift có được nhấn hay không
    if ((GetKeyState(VK_SHIFT) & 0x8000) != 0) // Nếu bit cao nhất là 1, phím được nhấn
        return true;
    else
        return false;
}

// Kiểm tra chữ cái - phân biệt hoa thường
void checkAlphabet()
{
    // Kiem tra chu cai
    for (int vk = 0x41; vk <= 0x5a; vk++)
    {
        if (GetAsyncKeyState(vk) & 0x8000)
        {
            char c = vk;
            // Kiểm tra xem phím có nên viết thường hay không
            if (!(isShift() ^ isCapsLock())) // Nếu Shift và Caps Lock cùng bật hoặc cùng tắt
            {
                c += 32; // Chuyển sang chữ thường
            }
            std::cout << "You pressed " << c << "\n";
        }
    }
}

// Kiểm tra số -> không dùng được phím số bên phải
void checkNumber()
{
    // Kiem tra chu cai
    for (int vk = 0x30; vk <= 0x39; vk++)
    {
        if (GetAsyncKeyState(vk) & 0x8000)
        {
            char c = vk;
            std::cout << "You pressed " << c << "\n";
        }
    }
}

// Bắt phím ESC
void isESC()
{
    // Kiểm tra xem phím ESC có được nhấn hay không
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        std::cout << "You pressed ESC\n";
    }
}

// Bắt số + chữ cái hoa thường
void catchKeydown()
{
    // bat phim nhan
    while (true)
    {
        checkAlphabet();
        checkNumber();
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            std::cout << "You pressed ESC\n";
            break; // Thoát khỏi vòng lặp
        }
        // Đợi 100 ms trước khi kiểm tra lại
        Sleep(100);
    }
}

// Chuyển mã phím ảo thành mã unicode
void toUni(int code)
{
    // Khởi tạo mảng trạng thái bàn phím
    BYTE keyState[256] = {0};

    // Khởi tạo bộ đệm ký tự Unicode
    WCHAR unicodeBuff[10] = {0};

    // Mã phím ảo của phím A
    // UINT vk = 'A';
    UINT vk = code;

    // Mã quét phím của phím A
    UINT sc = MapVirtualKey(vk, MAPVK_VK_TO_VSC);

    // Gọi hàm ToUnicode để chuyển đổi mã phím ảo thành ký tự Unicode
    int result = ToUnicode(vk, sc, keyState, unicodeBuff, 10, 0);

    // Kiểm tra kết quả trả về
    if (result > 0) // Nếu có ít nhất một ký tự được ghi vào bộ đệm
    {
        std::wcout << "The Unicode character is: " << unicodeBuff << "\n";
    }
    else if (result < 0) // Nếu mã phím ảo là một ký tự chết
    {
        std::wcout << "The virtual key is a dead key character.\n";
    }
    else // Nếu không có ký tự nào được ghi vào bộ đệm
    {
        std::wcout << "The virtual key has no translation.\n";
    }
}

// VirtualKeyCode --> String
std::string VirtualKeyCodeToString(UCHAR virtualKey)
{
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

// Tất cả phím, chuyển sang unicode
void catchAlltoUnicode()
{
    while (true)
    {
        // Duyệt qua tất cả các mã phím ảo từ 0x01 đến 0xFE
        for (int vk = 0x01; vk <= 0xFE; vk++)
        {
            // Kiểm tra xem phím có được nhấn hay không
            // if (GetAsyncKeyState(vk) & 0x8000)
            if (GetAsyncKeyState(vk) & 0x8000)
            {
                // std::cout << "You pressed key code " << vk << " - " << codeToKey(vk) << "\n";
                // std::cout << "You pressed key code " << (char)vk << "\n";
                toUni(vk);
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            std::cout << "You pressed ESC\n";
            break; // Thoát khỏi vòng lặp
        }
        // Đợi 100 ms trước khi kiểm tra lại
        Sleep(100);
    }
}

// Bắt phím và xuất Virtual Key Code
void catchCodeAll()
{
    while (true)
    {
        // Duyệt qua tất cả các mã phím ảo từ 0x01 đến 0xFE
        for (int vk = 0x01; vk <= 0xFE; vk++)
        {
            // Kiểm tra xem phím có được nhấn hay không
            // if (GetAsyncKeyState(vk) & 0x8000)
            if (GetAsyncKeyState(vk) & 0x8000)
            {
                std::cout << "You pressed key code " << vk << "\n";
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            std::cout << "You pressed ESC\n";
            break; // Thoát khỏi vòng lặp
        }
        // Đợi 100 ms trước khi kiểm tra lại
        Sleep(100);
    }
}

// Bắt phím và xuất string (Desc)
void catchCodeAlltoString() {
    while (true)
    {
        // Duyệt qua tất cả các mã phím ảo từ 0x01 đến 0xFE
        // for (int vk = 0x01; vk <= 0xFE; vk++)
        for (int vk = 0x08; vk <= 0xFE; vk++) // bỏ qua click chuột
        {
            // Kiểm tra xem phím có được nhấn hay không
            if (GetAsyncKeyState(vk) & 0x8000)
            {
                // std::cout << "You pressed key code " << vk << "\n";
                std::cout << "You pressed key code: " << vk << " --> " << VirtualKeyCodeToString(vk) << "\n";
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            std::cout << "You pressed ESC\n";
            break; // Thoát khỏi vòng lặp
        }
        
        // Đợi 100 ms trước khi kiểm tra lại
        Sleep(100);
    }
}

int main()
{
    // catchKeydown();
    // catchAll();
    // catchCodeAll();
    catchCodeAlltoString();
    return 0;
}

