#pragma once
#include <iostream>
#include "book.h"
#include "customer.h"
using namespace std;
class BookNode
{
public:
    Book data;
    BookNode *next;
    BookNode(const Book &book) : data(book), next(nullptr) {}
    BookNode() : next(NULL) {}
};
class CustomerNode
{
public:
    Customer data;
    CustomerNode *next;
    CustomerNode(const Customer &cus) : data(cus), next(nullptr) {}
    CustomerNode() : next(NULL) {}
};
class LinkedList
{
protected:
    BookNode *bookHead;
    CustomerNode *customerHead;

public:
    LinkedList();
    ~LinkedList();
    bool isEmpty();
    int length_Of_List();
    bool delete_Node_Book(Book);
    int find_Node_Book(Book);
    int find_Node_Book(const string &);
    bool Insert_NodeLast(Book);
    bool Insert_NodeMiddle(Book, int);
    int find_NodeCustomer(Customer);
    bool Add_Customer(Customer);
    Book *getNodeBook(int);
    Customer *getNodeCustomer(int);
    int find_NodeCustomer(const string &);
    void readCustomer(const string &fileName);
};