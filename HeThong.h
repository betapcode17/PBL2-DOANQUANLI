#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <strsafe.h>
#include <chrono>
#include <io.h>
#include <fcntl.h>
using namespace std;
#include <windows.h>
#include <iostream>

inline void SetConsoleBackgroundToGray()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (hConsole == INVALID_HANDLE_VALUE)
    {
        std::cerr << "Error: Unable to get console handle." << std::endl;
        return;
    }

    // Lấy thông tin buffer console
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        std::cerr << "Error: Unable to get console buffer info." << std::endl;
        return;
    }

    // Tính tổng số ô cần thay đổi trong console
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD charsWritten;

    // Màu nền xám (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE)
    WORD grayBackground = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

    // Thay đổi màu nền toàn bộ console
    FillConsoleOutputAttribute(hConsole, grayBackground, consoleSize, {0, 0}, &charsWritten);

    // Thay đổi nội dung thành khoảng trắng
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, {0, 0}, &charsWritten);

    // Đặt lại con trỏ về góc trên bên trái
    SetConsoleCursorPosition(hConsole, {0, 0});
}

inline void gotoXY(int x, int y)
{
    COORD coord = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
inline void setTextColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
inline void drawBox(int x, int y, int width, int height)
{
    gotoXY(x, y);
    cout << char(218);
    gotoXY(x + width - 1, y);
    cout << char(191);
    gotoXY(x, y + height - 1);
    cout << char(192);
    gotoXY(x + width - 1, y + height - 1);
    cout << char(217);

    for (int i = 1; i < width - 1; ++i)
    {
        gotoXY(x + i, y);
        cout << char(196);
        gotoXY(x + i, y + height - 1);
        cout << char(196);
    }

    for (int i = 1; i < height - 1; ++i)
    {
        gotoXY(x, y + i);
        cout << char(179);
        gotoXY(x + width - 1, y + i);
        cout << char(179);
    }
}

inline void Showcur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    // Lấy thông tin con trỏ hiện tại
    GetConsoleCursorInfo(handle, &ConCurInf);

    // Thiết lập trạng thái hiển thị con trỏ
    ConCurInf.bVisible = CursorVisibility;

    // Thiết lập lại kích thước con trỏ (không cần thay đổi kích thước nếu bạn chỉ muốn hiển thị/ẩn con trỏ)
    ConCurInf.dwSize = 10; // Giá trị hợp lệ nằm trong khoảng từ 1 đến 100

    // Cập nhật thông tin con trỏ
    SetConsoleCursorInfo(handle, &ConCurInf);
}
inline void setcolor(int text_color, int background_color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (background_color << 4) | text_color);
}

// Ghi lỗi và thoát ra ( dùng trong bắt sự kiện chuột)
inline VOID WriteError(LPSTR lpszMessage)
{
    printf("%s\n", lpszMessage);
    ExitProcess(0);
}
// Viết kí tự tại vị trí có tọa độ (x, y)
inline void writeChar(int x, int y, const wchar_t *z)
{
    // Save the current mode
    int oldMode = _setmode(_fileno(stdout), _O_U16TEXT);
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Thiết lập màu chữ trắng trên nền xám (0x70: nền xám, chữ trắng)
    SetConsoleTextAttribute(consoleHandle, 0x70);
    // Move the cursor to the specified position and print the wide character string
    gotoXY(x, y);
    wcout << z;

    // Restore the previous mode
    _setmode(_fileno(stdout), oldMode);
}
inline int setClick(int &a, int &b)
{
    DWORD cNumRead;
    DWORD fdwMode;
    INPUT_RECORD irInBuf[128];
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    if (hStdin == INVALID_HANDLE_VALUE)
    {
        WriteError(const_cast<LPSTR>("GetStdHandle failed"));
        return 1;
    }

    // Set extended flags mode
    fdwMode = ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError(const_cast<LPSTR>("SetConsoleMode failed (EXTENDED_FLAGS)"));
        return 1;
    }

    // Enable window and mouse input
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError(const_cast<LPSTR>("SetConsoleMode failed (WINDOW_INPUT | MOUSE_INPUT)"));
        return 1;
    }

    bool clicked = false;

    while (!clicked)
    {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))
        {
            WriteError(const_cast<LPSTR>("ReadConsoleInput failed"));
            return 1;
        }

        for (DWORD i = 0; i < cNumRead; i++)
        {
            if (irInBuf[i].EventType == MOUSE_EVENT)
            {
                MOUSE_EVENT_RECORD mer = irInBuf[i].Event.MouseEvent;

                // Check if it's a left button click event and not mouse movement
                if ((mer.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) && (mer.dwEventFlags == 0))
                {
                    a = mer.dwMousePosition.X;
                    b = mer.dwMousePosition.Y;
                    clicked = true;
                    break;
                }
            }
        }
    }

    // Always return a value at the end
    return 0;
}
inline void menuTable(int x, int y, int m, int n)
{
    int i, j;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Thiết lập màu nền xám và màu chữ mặc định
    SetConsoleTextAttribute(consoleHandle, 0x70);

    for (j = y; j <= y + n; j++) // Duyệt từng dòng
    {
        for (i = x; i <= x + m; i++) // Duyệt từng cột
        {
            // Góc trên trái
            if (i == x && j == y)
                writeChar(i, j, L"╔");

            // Góc trên phải
            else if (i == x + m && j == y)
                writeChar(i, j, L"╗");

            // Góc dưới trái
            else if (i == x && j == y + n)
                writeChar(i, j, L"╚");

            // Góc dưới phải
            else if (i == x + m && j == y + n)
                writeChar(i, j, L"╝");

            // Đường viền ngang
            else if (j == y || j == y + n)
                writeChar(i, j, L"═");

            // Đường viền dọc
            else if (i == x || i == x + m)
                writeChar(i, j, L"║");

            // Bên trong khung: đảm bảo màu nền
            else
            {
                SetConsoleCursorPosition(consoleHandle, {(SHORT)i, (SHORT)j});
                std::wcout << L" ";
            }
        }
    }
}
// sự kiện bàn phím
inline int setKeyBoard()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            return 2; // lên
        }
        else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            return 1; // xuống
        }
        else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            return 3; // TRÁI
        }
        else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            return 4; // PHẢI
        }
        else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            return 5; // ESC
        }
        else if (GetAsyncKeyState(VK_TAB) & 0x8000) // Kiểm tra phím Tab
        {
            return 9; // Tab
        }
    }
    return 0;
}

inline int batphim()
{
    int c = getch();
    if (c == 8) // phim Backspace
        return 1;
    else if (c == 9) // phim Tab
        return 2;
    else if (c == 13) // phim Enter
        return 3;
    else if (c == 27) // phim Esc
        return 4;
    else if (c == 224)
    {
        c = getch();
        if (c == 72) // Keyup
            return 5;
        else if (c == 80) // KeyDown
            return 6;
        else if (c == 75) // KeyLeft
            return 7;
        else if (c == 77) // KeyRight
            return 8;
        else if (c == 83) // Delete
            return 9;
    }
    else if (c == 0)
    {
        c = getch();
        if (c == 60) // F2
            return 12;
        if (c == 62) // F4
            return 13;
    }
}
inline void writeString(int x, int y, const std::wstring &s, int color)
{
    // Set console mode to handle Unicode characters (UTF-16)
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleOutputCP(CP_UTF8);
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Set the text attribute to the specified color
    SetConsoleTextAttribute(consoleHandle, color);

    // Move the cursor to the specified position
    gotoXY(x, y);

    // Output the string with wcout
    std::wcout << s;

    // Reset the console mode back to text mode
    _setmode(_fileno(stdout), _O_TEXT);
}
inline void display_forgetPassword()
{
    // Xóa toàn bộ màn hình và thiết lập nền xám
    system("cls");
    SetConsoleBackgroundToGray();

    // Vẽ khung chính
    menuTable(40, 5, 40, 25);
    writeString(50, 7, L"[FORGET PASSWORD]", 0x71);
    // Vẽ label và textbox "New Username"
    writeString(45, 9, L"Username", 0x71);
    menuTable(45, 10, 30, 2); // Khung textbox New Username

    // Vẽ label và textbox "New Password"
    writeString(45, 14, L"New Password", 0x71);
    menuTable(45, 15, 30, 2); // Khung textbox New Password

    // Vẽ label và textbox "Confirm Password"
    writeString(45, 19, L"Confirm Password", 0x71);
    menuTable(45, 20, 30, 2); // Khung textbox Confirm Password

    // Vẽ nút "Register"
    menuTable(45, 24, 30, 2);
    writeString(55, 25, L"Submit Now", 0x71);
    menuTable(90, 5, 40, 15);
    writeString(98, 6, L"[ Mật khẩu hợp lệ ]", 0x71);
    writeString(92, 8, L"1. Chứa ít nhất 4 ký tự", 0x74);
    writeString(92, 10, L"2. Chứa ít nhất 1 chữ cái viết hoa", 0x74);
    writeString(92, 12, L"3. Chứa ít nhất 1 chữ cái viết thường", 0x74);
    writeString(92, 14, L"4. Chứa ít nhất 1 chữ số", 0x74);
}
inline void display_register()
{
    // Xóa toàn bộ màn hình và thiết lập nền xám
    system("cls");
    SetConsoleBackgroundToGray();

    // Vẽ khung chính
    menuTable(40, 5, 40, 25);

    // Vẽ label và textbox "New Username"
    writeString(45, 8, L"New Username", 0x71);
    menuTable(45, 10, 30, 2); // Khung textbox New Username

    // Vẽ label và textbox "New Password"
    writeString(45, 14, L"New Password", 0x71);
    menuTable(45, 15, 30, 2); // Khung textbox New Password

    // Vẽ label và textbox "Confirm Password"
    writeString(45, 19, L"Confirm Password", 0x71);
    menuTable(45, 20, 30, 2); // Khung textbox Confirm Password

    // Vẽ nút "Register"
    menuTable(45, 24, 30, 2);
    writeString(55, 25, L"Register Now", 0x71);
    menuTable(90, 5, 40, 15);
    writeString(98, 6, L"[ Mật khẩu hợp lệ ]", 0x71);
    writeString(92, 8, L"1. Chứa ít nhất 4 ký tự", 0x74);
    writeString(92, 10, L"2. Chứa ít nhất 1 chữ cái viết hoa", 0x74);
    writeString(92, 12, L"3. Chứa ít nhất 1 chữ cái viết thường", 0x74);
    writeString(92, 14, L"4. Chứa ít nhất 1 chữ số", 0x74);
}
inline void display_login()
{
    // Xóa toàn bộ màn hình và thiết lập nền xám
    system("cls");
    SetConsoleBackgroundToGray();

    // Đặt màu chữ
    setTextColor(11);

    // Vẽ khung tiêu đề
    menuTable(30, 1, 60, 3);
    writeString(34, 2, L"CHÀO MỪNG BẠN ĐẾN VỚI ỨNG DỤNG QUẢN LÍ NHÀ SÁCH", 0x74);

    // Vẽ khung chính
    menuTable(40, 5, 40, 20);

    // Vẽ label và textbox "Username"
    writeString(45, 8, L"Username", 0x71);
    menuTable(45, 10, 30, 2); // Khung textbox Username

    // Vẽ label và textbox "Password"
    writeString(45, 14, L"Password", 0x71);
    menuTable(45, 15, 30, 2); // Khung textbox Password

    // Vẽ gợi ý "Press Tab to show/hide password"
    writeString(45, 18, L"Press Tab to show/hide password.", 0x71);

    // Vẽ nút "Login"
    menuTable(45, 20, 30, 2);
    writeString(57, 21, L"Login", 0x71);

    // Vẽ "SIGN UP" và "Forgot password"
    setTextColor(11); // Đặt lại màu chữ để tạo hiệu ứng gạch chân
    writeString(48, 23, L"\033[4mSIGN UP\033[0m", 0x71);
    writeString(60, 23, L"\033[4mForgot password\033[0m", 0x71);
}

inline void hideCursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // Lấy handle của console
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(consoleHandle, &cursorInfo); // Lấy thông tin hiện tại của con trỏ chuột
    cursorInfo.bVisible = FALSE;                      // Đặt trạng thái hiển thị của con trỏ thành FALSE để ẩn con trỏ
    SetConsoleCursorInfo(consoleHandle, &cursorInfo); // Cập nhật thông tin mới của con trỏ chuột
}
inline void menuDisplay(int x, int y, int sl, int number = 1, int sum = 1)
{
    int i, j;
    int c = 150;
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
                i == x + 120 || i == x + 130 || i == x + c)
            {

                // Drawing corners and intersections for clean table look
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }
    writeString(x + 8, y + 1, L"Mã Sách", 0x71);
    writeString(x + 30, y + 1, L"Tên Sách", 0x71);
    writeString(x + 60, y + 1, L"Thể Loại", 0x71);
    writeString(x + 85, y + 1, L"Tên Tác Giả", 0x71);
    writeString(x + 104, y + 1, L"Năm xuất bản", 0x71);
    writeString(x + 125, y + 1, L"SL", 0x71);
    writeString(x + 136, y + 1, L"Giá Bán", 0x71);
    // writeString(x + 40, y - 1, L"Nhấn ESC để quay trở lại ");
    if (sum > 1)
    {
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(consoleHandle, 0x74); // 0x74 = nền xám + chữ đỏ
        writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!", 0x74);
        writeString(x + 135, y - 2, L"Trang: ", 0x74);
        wcout << number << L"/" << sum;
    }
}
inline void bangsanpham(int x, int y, int sl)
{
    int i, j;
    int c = 150;
    sl = sl + 3;
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
                i == x + 120 || i == x + 130 || i == x + c)
            {

                // Drawing corners and intersections for clean table look
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }
    writeString(x + 5, y + 1, L"Mã Sách", 0x71);
    writeString(x + 30, y + 1, L"Tên Sách", 0x71);
    writeString(x + 60, y + 1, L"Thể Loại", 0x71);
    writeString(x + 85, y + 1, L"Tên Tác Giả", 0x71);
    writeString(x + 104, y + 1, L"Năm xuất bản", 0x71);
    writeString(x + 125, y + 1, L"SL", 0x71);
    writeString(x + 136, y + 1, L"Giá Bán", 0x71);
}
inline void bangkhanhhang(int x, int y, int sl)
{
    int i, j;
    int c = 150;
    sl = sl + 3;
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
                i == x + c)
            {

                // Drawing corners and intersections for clean table look
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }
    writeString(x + 10, y + 1, L"Mã KH", 0x71);
    writeString(x + 30, y + 1, L"Họ và tên", 0x71);
    writeString(x + 60, y + 1, L"Địa chỉ", 0x71);
    writeString(x + 85, y + 1, L"SĐT", 0x71);
    writeString(x + 104, y + 1, L"số tiền đã mua", 0x71);
}
inline void menuDisplay2(int x, int y, int sl, int number = 1, int sum = 1)
{
    int i, j;
    int c = 120;
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 20 || i == x + 50 || i == x + 80 || i == x + 100 ||
                i == x + c)
            {

                // Drawing corners and intersections for clean table look
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }
    writeString(x + 10, y + 1, L"Mã KH", 0x71);
    writeString(x + 30, y + 1, L"Họ và tên", 0x71);
    writeString(x + 60, y + 1, L"Địa chỉ", 0x71);
    writeString(x + 85, y + 1, L"SĐT", 0x71);
    writeString(x + 104, y + 1, L"số tiền đã mua", 0x71);
    writeString(x + 40, y - 1, L"Nhấn ESC để quay trở lại ", 0x74);
    if (sum > 1)
    {
        writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!", 0x74);
        writeString(x + 135, y - 2, L"Trang: ", 0x74);
        wcout << number << L"/" << sum;
    }
}
inline void Ordertable(int x, int y, int sl)
{
    int i, j;
    int c = 100;
    sl = sl + 3;
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 10 || i == x + 40 || i == x + 60 || i == x + 80 || i == x + 100 || i == x + c)
            {

                // Drawing corners and intersections for clean table look
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }
    writeString(x + 2, y + 1, L"STT", 0x71);
    writeString(x + 15, y + 1, L"Tên sách", 0x71);
    writeString(x + 45, y + 1, L"Số lượng", 0x71);
    writeString(x + 65, y + 1, L"Đơn giá", 0x71);
    writeString(x + 85, y + 1, L"Thành tiền", 0x71);
}
inline void Bill_Table(int x, int y, int sl, int number = 1, int sum = 1)
{
    int i, j;
    int c = 100; // Reduced total width of the table
    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 15 || i == x + 35 || i == x + 60 || i == x + 80 || i == x + c)
            {
                // Adjusted positions for cleaner layout
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }

    // Adjusted column text positions for narrower layout
    writeString(x + 8, y + 1, L"Mã HĐ", 0x70);
    writeString(x + 23, y + 1, L"Mã KH", 0x70);
    writeString(x + 40, y + 1, L"Ngày lập hóa đơn", 0x70);
    writeString(x + 65, y + 1, L"Số lượng", 0x70);
    writeString(x + 85, y + 1, L"Tổng tiền", 0x70);

    // Adjusted position for ESC instruction
    writeString(x + 20, y - 1, L"Nhấn ESC để quay trở lại ", 0x74);
    if (sum > 1)
    {
        writeString(x + 3, y + 24, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!", 0x74);
        writeString(x + 85, y - 2, L"Trang: ", 0x74);
        wcout << number << L"/" << sum;
    }
}
inline void Account_Table(int x, int y, int sl, int number = 1, int sum = 1)
{
    int i, j;
    int c = 60; // Giảm chiều rộng bảng vì bỏ cột Mật khẩu
    // Lấy kích thước màn hình (giả sử bạn đã có hàm lấy chiều rộng và chiều cao màn hình)
    int screenWidth = 120; // Thay giá trị này bằng chiều rộng màn hình
    int screenHeight = 30; // Thay giá trị này bằng chiều cao màn hình

    // Tính toán vị trí trung tâm
    x = (screenWidth - c) / 2;       // Căn giữa theo chiều ngang
    y = (screenHeight - sl - 3) / 2; // Căn giữa theo chiều dọc (trừ thêm khoảng header và footer)

    for (i = x; i <= x + c; i++)
    {
        for (j = y; j <= y + sl; j++)
        {
            if (i == x || i == x + 10 || i == x + 30 || i == x + c)
            {
                // Điều chỉnh các đường kẻ cột
                if (j == y && i != x && i != x + c)
                    writeChar(i, j, L"┬");
                else if (j == y && i == x)
                    writeChar(i, j, L"┌");
                else if (j == y && i == x + c)
                    writeChar(i, j, L"┐");
                else if (j == y + 2 && i != x && i != x + c)
                    writeChar(i, j, L"┼");
                else if (j == y + 2 && i == x)
                    writeChar(i, j, L"├");
                else if (j == y + 2 && i == x + c)
                    writeChar(i, j, L"┤");
                else if (j == y + sl && i != x && i != x + c)
                    writeChar(i, j, L"┴");
                else if (j == y + sl && i == x)
                    writeChar(i, j, L"└");
                else if (j == y + sl && i == x + c)
                    writeChar(i, j, L"┘");
                else
                    writeChar(i, j, L"│");
            }
            else if (j == y || j == y + 2 || j == y + sl)
            {
                writeChar(i, j, L"─");
            }
        }
    }

    // Các tiêu đề cột
    writeString(x + 3, y + 1, L"STT", 0x70);
    writeString(x + 15, y + 1, L"Username", 0x70);
    writeString(x + 37, y + 1, L"Role", 0x70);

    // Hướng dẫn ESC và phân trang
    writeString(x + 10, y - 1, L"Nhấn ESC để quay lại || Nhấn Tab để hiện menu", 0x74);
    if (sum > 1)
    {
        writeString(x + 3, 25, L"[->] Tới trang tiếp, [<-] Quay về trang trước", 0x74);
        writeString(x + 65, y - 2, L"Trang: ", 0x74);
        wcout << number << L"/" << sum;
    }
}