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
    L"1> Thông tin khách hàng đã mua",
    L"2> Thêm khách hàng mới"};
int menuKhachHang = sizeof(menuKhachHang) / sizeof(menuKhachHang[0]);
inline void thanh_sang(int x, int y, int w, int h, int b_color, wstring menuItems[], int currentItem, bool highlight)
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);

    // Nếu là highlight (thanh sáng), dùng màu nổi bật
    if (highlight)
        setcolor(0, b_color); // Chữ trắng, nền nổi bật
    else
        setcolor(0, 7); // Chữ trắng, nền xám

    // Vẽ nền
    for (int iy = y + 1; iy <= y + h - 1; iy++)
    {
        for (int ix = x + 1; ix <= x + w - 1; ix++)
        {
            gotoXY(ix, iy);
            wcout << L" ";
        }
    }

    // Hiển thị nội dung
    gotoXY(x + 2, y + 1);
    wcout << menuItems[currentItem];
}

inline int MENU(wstring menuItems[], int menuSize, int x, int y, int w, int h, int boxX, int boxY, int boxW, int i)
{
    SetConsoleOutputCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U16TEXT);
    Showcur(0);

    int b_color_sang = 12; // Nền nổi bật (đỏ nhạt)
    int currentItem = 0;
    // Vẽ khung menu
    menuTable(boxX, boxY - 3, boxW, 2);
    gotoXY(boxX + 14, boxY - 2);
    if (i == 1)
        wcout << "MENU ADMIN";
    else
        wcout << "MENU USER";
    menuTable(boxX, boxY, boxW, menuSize * 3 + 4);

    // Hiển thị toàn bộ mục menu với màu mặc định
    for (int i = 0; i < menuSize; i++)
    {
        gotoXY(x + 2, y + i * 3 + 1);
        thanh_sang(x, y + i * 3, w, h, 7, menuItems, i, false); // Chữ trắng, nền xám
    }

    int xp = x, yp = y, xcu = xp, ycu = yp;
    bool kt = true;

    while (true)
    {
        if (kt)
        {
            // Reset màu của mục trước đó
            thanh_sang(xcu, ycu, w, h, 7, menuItems, (ycu - y) / 3, false);

            // Cập nhật vị trí mới
            xcu = xp;
            ycu = yp;

            // Tô sáng mục hiện tại
            thanh_sang(xcu, ycu, w, h, b_color_sang, menuItems, (yp - y) / 3, true);
            kt = false;
        }

        if (_kbhit())
        {
            char c = _getch();
            if (c == -32)
            { // Phím mũi tên
                kt = true;
                c = _getch();
                if (c == 72)
                { // Mũi tên lên
                    if (yp != y)
                        yp -= 3;
                    else
                        yp = y + 3 * (menuSize - 1); // Quay lại mục cuối
                }
                else if (c == 80)
                { // Mũi tên xuống
                    if (yp != y + 3 * (menuSize - 1))
                        yp += 3;
                    else
                        yp = y; // Quay lại mục đầu
                }
            }
            else if (c == 13)
            {                        // Phím Enter
                setcolor(7, 0);      // Reset màu mặc định
                return (yp - y) / 3; // Trả về chỉ mục menu
            }
            else if (c == 27)
            {                   // Phím ESC
                setcolor(7, 0); // Reset màu mặc định
                return -1;      // Thoát menu
            }
        }
    }

    // Reset màu mặc định
    setcolor(7, 0);
    gotoXY(0, 30);
    return -1;
}

inline void Thong_Tin()
{
    int x = 55, y = 5;
    while (true)
    {
        menuTable(x + 29, y + 2, 65, 19);
        writeString(x + 57, y + 3, L"PBL2", 0x70);
        writeString(x + 37, y + 5, L"CHƯƠNG TRÌNH QUẢN LÍ CỬA HÀNG CHUYÊN VỀ SÁCH", 0x70);
        writeString(x + 33, y + 9, L"Sinh viên thực hiện: Trần Quốc Đạt  Lớp: 23T_NHAT2", 0x70);
        writeString(x + 33, y + 11, L"Sinh viên thực hiện: Cao Minh Đức   Lớp: 23T_NHAT2", 0x70);
        writeString(x + 33, y + 13, L"Giáo viên hướng dẫn: Thầy Võ Đức Hoàng", 0x70);
        writeString(x + 33, y + 15, L"Cảm ơn: Các thầy, cô giáo trong bộ môn đã giúp đỡ chúng em", 0x70);
        if (setKeyBoard() == 5)
        {
            break;
        }
    }
}
