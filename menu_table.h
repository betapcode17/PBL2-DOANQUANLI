#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fcntl.h>
#include "HeThong.h"
using namespace std;

// --- Variables ---
wstring menu[] = {
    L"1> Quản lý sản phẩm",
    L"2> Quản lý khách hàng",
    L"3> Thống kê",
    L"4> Thông tin",
    L"5> Thoát"};
int menuSize = sizeof(menu) / sizeof(menu[0]);

wstring menuUser[] = {
    L"1> Xem thông tin sản phẩm",
    L"2> Xem thông tin khách hàng",
    L"3> Order",
    L"4> Thông tin",
    L"5> Thoát"};
int menuUserSize = sizeof(menuUser) / sizeof(menuUser[0]);

wstring menuCRUD[] = {
    L"1> Xem thông tin của sách",
    L"2> Thêm sách mới",
    L"3> Xóa sách",
    L"4> Cập nhật sách",
    L"5> Thoát"};
int menuCRUDSize = sizeof(menuCRUD) / sizeof(menuCRUD[0]);

wstring menuRead[] = {
    L"1> Thông tin toàn bộ sách trong cửa hàng",
    L"2> Tìm kiếm thông tin sách",
    L"3> Sắp xếp thông tin sách",
    L"4> Thoát"};
int menuReadSize = sizeof(menuRead) / sizeof(menuRead[0]);

wstring menuSearch[] = {
    L"1> Tìm kiếm sách theo tên sách",
    L"2> Tìm kiếm sách theo thể loại",
    L"3> Tìm kiếm sách theo tác giả",
    L"4> Tìm kiếm sách theo năm xuất bản",
    L"5> Thoát"};
int menuSearchSize = sizeof(menuSearch) / sizeof(menuSearch[0]);

wstring menuSort[] = {
    L"1> Sắp xếp sách theo số lượng",
    L"2> Sắp xếp sách theo số tiền",
    L"3> Sắp xếp sách theo năm xuất bản",
    L"4> Thoát"};
int menuSortSize = sizeof(menuSort) / sizeof(menuSort[0]);

wstring menuSortUpandDown[] = {
    L"1> Sắp xếp tăng dần",
    L"2> Sắp xếp giảm dần",
    L"3> Thoát"};
int menuUpandDownSize = sizeof(menuSortUpandDown) / sizeof(menuSortUpandDown[0]);

wstring menuKhachHang[] = {
    L"1> Nhập thông tin khách hàng",
    L"2> Quản lý khách hàng",
    L"3> Thoát"};

// --- Functions ---
inline void thanh_sang(int x, int y, int w, int h, int b_color, wstring menuItems[], int currentItem)
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
    setcolor(15, b_color); // Màu chữ trắng (15), màu nền tùy chọn
    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        for (int ix = x + 1; ix <= x + w - 1; ix++)
        {
            gotoXY(ix, iy);
            wcout << L" ";
        }
    }
    gotoXY(x + 2, y + 1);
    wcout << menuItems[currentItem]; // Hiển thị mục menu tương ứng

    // Reset màu trở lại màu mặc định sau khi in thanh sáng
    // Màu mặc định: chữ trắng, nền đen
}

inline int MENU(wstring menuItems[], int menuSize, int x, int y, int w, int h, int boxX, int boxY, int boxW)
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
    Showcur(0);
    int t_color = 11;
    int b_color = 0;
    int b_color_sang = 12;
    int currentItem = 0;

    // Draw box for menu
    menuTable(boxX, boxY, boxW, menuSize * 3 + 4);

    // Print all menu items with default color
    for (int i = 0; i < menuSize; i++)
    {
        gotoXY(x + 2, y + i * 3 + 1);
        setcolor(7, 0); // Default color
        wcout << menuItems[i];
    }

    int xp = x, yp = y, xcu = xp, ycu = yp;
    bool kt = true;

    while (true)
    {
        if (kt == true)
        {
            // Reset previous item to default color
            thanh_sang(xcu, ycu, w, h, b_color, menuItems, (ycu - y) / 3);

            // Update current coordinates
            xcu = xp;
            ycu = yp;

            // Highlight new item
            thanh_sang(xcu, ycu, w, h, b_color_sang, menuItems, (yp - y) / 3);
            kt = false;
        }

        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            { // Arrow keys
                kt = true;
                c = _getch();
                if (c == 72)
                { // Up arrow key
                    if (yp != y)
                        yp -= 3;
                    else
                        yp = y + 3 * (menuSize - 1); // Loop back to last item
                }
                else if (c == 80)
                { // Down arrow key
                    if (yp != y + 3 * (menuSize - 1))
                        yp += 3;
                    else
                        yp = y; // Loop back to first item
                }
            }
            else if (c == 13)
            {                        // Enter key
                setcolor(7, 0);      // Reset color to default before executing action
                return (yp - y) / 3; // Return the selected menu index
            }
            else if (c == 27)
            {                   // ESC key
                setcolor(7, 0); // Reset color to default on ESC
                return -1;      // Exit on ESC key press
            }
        }
    }

    // Reset color to default at the end
    setcolor(7, 0);
    gotoXY(0, 30);
    return -1;
}

inline void Thong_Tin()
{
    int x = 50, y = 5;
    while (true)
    {
        menuTable(x + 29, y + 2, 65, 19);
        writeString(x + 57, y + 3, L"PBL2");
        writeString(x + 37, y + 5, L"CHƯƠNG TRÌNH QUẢN LÍ CỬA HÀNG CHUYÊN VỀ SÁCH");
        writeString(x + 33, y + 9, L"Sinh viên thực hiện: Trần Quốc Đạt  Lớp: 23T_NHAT2");
        writeString(x + 33, y + 11, L"Sinh viên thực hiện: Cao Minh Đức   Lớp: 23T_NHAT2");
        writeString(x + 33, y + 13, L"Giáo viên hướng dẫn: Thầy Võ Đức Hoàng");
        writeString(x + 33, y + 15, L"Cảm ơn: Các thầy, cô giáo trong bộ môn đã giúp đỡ chúng em");
        if (setKeyBoard() == 5)
        {
            break;
        }
    }
}
