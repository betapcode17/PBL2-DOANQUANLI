
#include "Book.h"
#include "Users.h"
#include "HeThong.h"
#include "menu_table.h"
#include "menu.h"
#include "Order.h"
Order order;
LinkedList L;
Users users;
Menu admin;
Menu user;
using namespace std;
void ShowMenuAdmin()
{
    int choice;
    bool exitFlag = false;

    while (!exitFlag)
    {
        system("cls");
        SetConsoleBackgroundToGray();
        choice = MENU(menu, menuSize, 41, 9, 30, 2, 40, 7, 40, 1);
        switch (choice)
        {
        case 0:
        {
            bool crudMenuExit = false;
            while (!crudMenuExit)
            {
                system("cls");
                SetConsoleBackgroundToGray();
                int i = MENU(menuCRUD, menuCRUDSize, 41, 9, 30, 2, 40, 7, 40, 1);
                switch (i)
                {
                case 0:
                { // "Xem thong tin cua sach"
                    bool readMenuExit = false;
                    while (!readMenuExit)
                    {
                        system("cls");
                        SetConsoleBackgroundToGray();
                        int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45, 1);

                        switch (b)
                        {
                        case 0:
                        {

                            admin.ShowAllBook();
                            break;
                        }
                        case 1:
                        { // tìm kiếm sách
                            bool searchMenuExit = false;
                            while (!searchMenuExit)
                            {
                                system("cls");
                                SetConsoleBackgroundToGray();
                                int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40, 1);

                                switch (s)
                                {
                                case 0:
                                    // tìm kiếm sách theo tên
                                    system("cls");
                                    admin.search_book(1);
                                    break;
                                case 1:
                                    // tìm kiếm sách theo thể loại
                                    system("cls");
                                    admin.search_book(2);
                                    break;
                                case 2:
                                    // tìm kiếm sách theo tác giả
                                    system("cls");
                                    admin.search_book(3);
                                    break;
                                case 3:
                                    // tìm kiếm sách theo năm xuất bản
                                    system("cls");
                                    admin.search_book(4);
                                    break;
                                case 4:
                                    searchMenuExit = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 2:
                        { // Sap xep sach
                            bool sortMenuExit = false;
                            while (!sortMenuExit)
                            {
                                system("cls");
                                SetConsoleBackgroundToGray();
                                int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40, 1);

                                switch (s)
                                {
                                case 0:
                                case 1:
                                case 2:
                                {
                                    bool sortUpandDown = false;
                                    while (!sortUpandDown)
                                    {
                                        system("cls");
                                        SetConsoleBackgroundToGray();
                                        int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40, 1);

                                        switch (t)
                                        {
                                        case 0:
                                            admin.Sort_BookUporDown(s + 1, 0);
                                            system("cls");
                                            break;
                                        case 1:
                                            admin.Sort_BookUporDown(s + 1, 1); // Sort descending
                                            system("cls");
                                            break;
                                        case 2:
                                            system("cls");
                                            sortUpandDown = true;
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 3:
                                    sortMenuExit = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            readMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 1:
                {
                    system("cls");
                    admin.CreateBook();
                    break;
                }
                case 2:
                {
                    system("cls");
                    admin.DeleteBook();
                    break;
                }
                case 3:
                {
                    system("cls");
                    admin.UpdateBook();
                    break;
                }
                case 4:
                    crudMenuExit = true;
                    system("cls");
                    break;
                }
            }
            break;
        }
        case 1:
        {
            SetConsoleBackgroundToGray();
            admin.ShowAllCus();
            break;
        }
        case 2:
        {
            // thống kê
            system("cls");
            SetConsoleBackgroundToGray();
            admin.statistical();
            break;
        }
        case 3:
        {
            // thoát
            SetConsoleBackgroundToGray();
            admin.ShowAllAccount();
            break;
        }
        case 4:
        {
            exitFlag = true;
            break;
        }
        }
    }
}
void ShowMenuUser()
{
    int choice;
    bool exitFlag = false;
    while (!exitFlag)
    {
        system("cls");
        SetConsoleBackgroundToGray();
        choice = MENU(menuUser, menuUserSize, 41, 9, 30, 2, 40, 7, 40, 0);

        switch (choice)
        {
        case 0:
        { // "Xem thong tin cua sach"
            bool readMenuExit = false;
            while (!readMenuExit)
            {
                system("cls");
                SetConsoleBackgroundToGray();
                int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45, 0);

                switch (b)
                {
                case 0:
                {
                    SetConsoleBackgroundToGray();
                    user.ShowAllBook();
                    break;
                }
                case 1:
                { // tìm kiếm sách
                    bool searchMenuExit = false;
                    while (!searchMenuExit)
                    {
                        system("cls");
                        SetConsoleBackgroundToGray();
                        int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40, 0);

                        switch (s)
                        {
                        case 0:
                            // tìm kiếm sách theo tên
                            system("cls");
                            SetConsoleBackgroundToGray();
                            user.search_book(1);
                            break;
                        case 1:
                            // tìm kiếm sách theo thể loại
                            system("cls");
                            SetConsoleBackgroundToGray();
                            user.search_book(2);
                            break;
                        case 2:
                            // tìm kiếm sách theo tác giả
                            system("cls");
                            SetConsoleBackgroundToGray();
                            user.search_book(3);
                            break;
                        case 3:
                            // tìm kiếm sách theo năm xuất bản
                            system("cls");
                            SetConsoleBackgroundToGray();
                            user.search_book(4);
                            break;
                        case 4:
                            searchMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 2:
                { // Sap xep sach
                    bool sortMenuExit = false;
                    while (!sortMenuExit)
                    {
                        system("cls");
                        SetConsoleBackgroundToGray();
                        int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40, 0);

                        switch (s)
                        {
                        case 0:
                        case 1:
                        case 2:
                        {
                            bool sortUpandDown = false;
                            while (!sortUpandDown)
                            {
                                system("cls");
                                SetConsoleBackgroundToGray();
                                int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40, 0);

                                switch (t)
                                {
                                case 0:
                                    user.Sort_BookUporDown(s + 1, 0); // Sort ascending
                                    system("cls");
                                    break;
                                case 1:
                                    user.Sort_BookUporDown(s + 1, 1); // Sort descending
                                    system("cls");
                                    break;
                                case 2:
                                    system("cls");
                                    sortUpandDown = true;
                                    break;
                                }
                            }
                            break;
                        }
                        case 3:
                            sortMenuExit = true;
                            break;
                        }
                    }
                    break;
                }
                case 3:
                    readMenuExit = true;
                    break;
                }
            }
            break;
        }
        case 1:
        {
            SetConsoleBackgroundToGray();
            user.ShowAllCus();
            break;
        }
        case 2:
        {
            system("cls");
            // user.Order();
            SetConsoleBackgroundToGray();
            order.ProcessOrder();
            break;
        }
        case 3:
        {
            // thoát
            SetConsoleBackgroundToGray();
            Thong_Tin();
            break;
        }
        case 4:
        {
            exitFlag = true;
            system("cls");
            //            Process();
            break;
        }
        }
    }
}
void Process()
{
    while (true)
    {
        int login = users.login();
        system("cls");
        if (login)
        {
            system("cls");
            admin.Start();
            ShowMenuAdmin();
        }
        else
        {
            system("cls");
            user.Start();
            ShowMenuUser();
        }
    }
}
int main()
{
    system("chcp 65001");
   Process();
//    Account_Table(2, 4, 23, 1, 8);

//change_role(30,30);
}
