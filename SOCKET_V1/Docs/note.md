# Winsock2.h - SOCKET - WINDOWS

## Code mẫu cơ bản đầy đủ

### Server: [Accept](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept)
### Client: [Connect](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect)

***

## Các bước dùng Socket (**Server**):

### [Tạo socket](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket)

- Mục đích: tạo socket
- Cú pháp

        SOCKET WSAAPI socket(
            [in] int af, // af = 2 = AF_INET (IPv4)
            [in] int type, // type = 1 = SOCK_STREAM
            [in] int protocol // protocol = 6 = IPPROTO_TCP
        );

### [Bind](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-bind)

- Mục đích: liên kết địa chỉ cục bộ với socket
- Cú pháp:

        int WSAAPI bind(
            [in] SOCKET         s,
            [in] const sockaddr *name,
            [in] int            namelen
        );

### [Listen](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen)

- Mục đích: đặt socket ở chế độ lắng nghe (chờ) một kết nối đến
- Cú pháp:

        int WSAAPI listen(
            [in] SOCKET s,
            [in] int    backlog // số thằng tối đa trong queue
        );

### [Accept](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept)

- Mục đích: cho phép kết nối của một yêu cầu được gửi đến
- Cú pháp:

        SOCKET WSAAPI accept(
            [in]      SOCKET   s,
            [out]     sockaddr *addr,
            [in, out] int      *addrlen
        );


### [Closesocket](https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-closesocket)

- Mục đích: đóng socket đang có
- Cú pháp:

        int closesocket(
            [in] SOCKET s
        );

### [Shutdown](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-shutdown)

- Mục đích: vô hiệu hóa gửi/nhận trên socket
- Cú pháp:

        int WSAAPI shutdown(
            [in] SOCKET s,
            [in] int    how // 0(SD_RECEIVE); 1(SD_SEND); 2(SD_BOTH)
        );
    
***

## Các bước dùng Socket (**Client**):

### [Tạo socket](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket)

### [Connect](https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect)

- Mục đích: kết nối với server
- Cú pháp:

        int WSAAPI connect(
            [in] SOCKET         s,
            [in] const sockaddr *name,
            [in] int            namelen
        );

## Cách chạy file .cpp trong VS:

    g++ server.cpp -o server.exe -lws2_32 ; .\server
    $(CC) -o server server.cpp  -lws2_32
    
## Cách chạy file với makefile:

    cd ..... (đưa đến folder)
    make; .\server