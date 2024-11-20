#pragma once
#include "linkedlist.h"
class Menu : public LinkedList
{
public:
    Menu();
    ~Menu();
    void Start();
    void ShowAllCus();
    void ShowAllBook();
    void ShowSortedBooks(int, BookNode *);
    void Sort_BookUporDown(int i, int t);
    BookNode *filterBooks(string, int);
    void search_book(int);
    bool UpdateBook();
    bool DeleteBook();
    bool CreateBook();
    void statistical();
};