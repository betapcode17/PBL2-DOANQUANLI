
#include "Book.h"
#include "Users.h"
#include "HeThong.h"
#include "menu_table.h"
#include "menu.h"
#include "Order.h"
LinkedList L;
Users users;
Order order;
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
        choice = MENU(menu, menuSize, 41, 9, 28, 2, 40, 7, 30);
        switch (choice)
        {
        case 0:
        {
            bool crudMenuExit = false;
            while (!crudMenuExit)
            {
                system("cls");
                int i = MENU(menuCRUD, menuCRUDSize, 41, 9, 30, 2, 40, 7, 40);
                switch (i)
                {
                case 0:
                { // "Xem thong tin cua sach"
                    bool readMenuExit = false;
                    while (!readMenuExit)
                    {
                        system("cls");
                        int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45);

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
                                int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40);

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
                                int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40);

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
                                        int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40);

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
            admin.ShowAllCus();
            break;
        }
        case 2:
        {
            // thống kê
            system("cls");
            admin.statistical();
            break;
        }
        case 3:
        {
            // thoát
            Thong_Tin();
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
        choice = MENU(menuUser, menuUserSize, 41, 9, 28, 2, 40, 7, 30);

        switch (choice)
        {
        case 0:
        { // "Xem thong tin cua sach"
            bool readMenuExit = false;
            while (!readMenuExit)
            {
                system("cls");
                int b = MENU(menuRead, menuReadSize, 41, 9, 30, 2, 40, 7, 45);

                switch (b)
                {
                case 0:
                {
                    user.ShowAllBook();
                    break;
                }
                case 1:
                { // tìm kiếm sách
                    bool searchMenuExit = false;
                    while (!searchMenuExit)
                    {
                        system("cls");
                        int s = MENU(menuSearch, menuSearchSize, 41, 9, 30, 2, 40, 7, 40);

                        switch (s)
                        {
                        case 0:
                            // tìm kiếm sách theo tên
                            system("cls");
                            user.search_book(1);
                            break;
                        case 1:
                            // tìm kiếm sách theo thể loại
                            system("cls");
                            user.search_book(2);
                            break;
                        case 2:
                            // tìm kiếm sách theo tác giả
                            system("cls");
                            user.search_book(3);
                            break;
                        case 3:
                            // tìm kiếm sách theo năm xuất bản
                            system("cls");
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
                        int s = MENU(menuSort, menuSortSize, 41, 9, 30, 2, 40, 7, 40);

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
                                int t = MENU(menuSortUpandDown, menuUpandDownSize, 41, 9, 30, 2, 40, 7, 40);

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
            user.ShowAllCus();
            break;
        }
        case 2:
        {
            system("cls");
            // user.Order();
            order.ProcessOrder();
            break;
        }
        case 3:
        {
            // thoát
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
int main()
{
    Process();
}
