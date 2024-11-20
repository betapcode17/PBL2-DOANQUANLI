#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <windows.h>
#include "HeThong.h"
#include "linkedlist.h"
#include "Book.h"
#include "customer.h"
#include "condition.h"
#include <windows.h>
#include "customer.h"
using namespace std;
static int count = 0;
bool LinkedList::isEmpty()
{
    if (this->bookHead == NULL)
        return true;
    return false;
}
LinkedList ::LinkedList()
{
    bookHead = NULL;
    customerHead = NULL;
}
LinkedList ::~LinkedList()
{
    // Clean up Book list
    BookNode *bookCurrent = bookHead;
    while (bookCurrent != NULL)
    {
        BookNode *bookNext = bookCurrent->next;
        delete bookCurrent;
        bookCurrent = bookNext;
    }

    // Clean up Customer list
    CustomerNode *customerCurrent = customerHead;
    while (customerCurrent != NULL)
    {
        CustomerNode *customerNext = customerCurrent->next;
        delete customerCurrent;
        customerCurrent = customerNext;
    }
}
int LinkedList::length_Of_List()
{
    int lenght = 0;
    BookNode *temp = this->bookHead;
    for (temp; temp != NULL; temp = temp->next)
    {
        ++lenght;
    }
    return lenght;
}
void LinkedList::readCustomer(const string &fileName)
{
    ifstream infile(fileName);
    if (!infile.is_open())
    {
        cout << "Could not open the file " << fileName << endl;
        return;
    }

    int n; // Số lượng khách hàng
    infile >> n;
    infile.ignore(); // Bỏ qua ký tự xuống dòng sau số lượng khách hàng
    CustomerNode *temp = nullptr;
    for (int i = 0; i < n; ++i)
    {
        CustomerNode *newNode = new CustomerNode();

        // Đọc dữ liệu từ file theo định dạng
        getline(infile, newNode->data.Ma_KH, '|');
        getline(infile, newNode->data.ho_ten, '|');
        getline(infile, newNode->data.dia_chi, '|');
        getline(infile, newNode->data.sdt_KH, '|');
        infile >> newNode->data.so_tien_da_mua;
        infile.ignore(); // Bỏ qua ký tự xuống dòng sau số tiền

        newNode->next = nullptr;
        // Nếu danh sách rỗng, node mới trở thành đầu danh sách
        if (customerHead == nullptr)
        {
            customerHead = newNode;
        }
        else
        {
            // Liên kết node mới vào cuối danh sách
            temp->next = newNode;
        }
        temp = newNode;
    }
    infile.close(); // Đóng file
}
// read
//  Tìm kiếm theo tên sách,thể loại,tên,tác giả

// Định nghĩa hàm đọc sách từ file
void LinkedList::readBook(const string &fileName)
{
    ifstream infile(fileName);
    if (!infile.is_open())
    {
        cout << "Could not open the file " << fileName << endl;
        return;
    }

    int n; // Số lượng sách
    infile >> n;
    infile.ignore(); // Bỏ qua ký tự xuống dòng sau số lượng sách
    BookNode *temp = nullptr;
    for (int i = 0; i < n; ++i)
    {
        BookNode *newNode = new BookNode();
        count++;
        // Sử dụng getline để lấy mã sách
        getline(infile, newNode->data.Ma_Sach, '|');

        getline(infile, newNode->data.ten_sach, '|');
        getline(infile, newNode->data.the_loai, '|');
        getline(infile, newNode->data.tac_gia, '|');
        infile >> newNode->data.so_luong;
        infile.ignore(1, '|'); // Bỏ qua ký tự '|' sau so_luong
        infile >> newNode->data.gia_ban;
        infile.ignore(1, '|');                // Bỏ qua ký tự '|' sau gia_ban
        infile >> newNode->data.nam_xuat_ban; // Đọc năm xuất bản
        infile.ignore();                      // Bỏ qua ký tự xuống dòng

        newNode->next = NULL;

        if (bookHead == NULL)
        {
            // Nếu danh sách rỗng, node mới trở thành đầu danh sách
            bookHead = newNode;
        }
        else
        {
            // Liên kết node mới vào cuối danh sách
            temp->next = newNode;
        }

        temp = newNode; // Cập nhật temp để trỏ đến node cuối
    }

    infile.close(); // Đóng file
}

//=============================================== UPDATE BOOK=====================================//
int LinkedList::find_Node_Book(const string &ma_sach)
{
    BookNode *temp = this->bookHead;
    int position = 1;

    for (temp; temp != NULL; temp = temp->next)
    {
        if (temp->data.Ma_Sach == ma_sach)
        {
            return position;
        }
        ++position;
    }

    return -1; // Trả về -1 nếu không tìm thấy
}
int LinkedList::find_Node_Book(Book a)
{
    BookNode *temp = this->bookHead;
    int position = 0; // Bắt đầu từ vị trí 0 (hoặc 1 tùy theo cách bạn muốn)

    while (temp != NULL)
    {
        if (temp->data.getMa_Sach() == a.getMa_Sach())
        {
            return position; // Trả về vị trí hiện tại nếu tìm thấy sách
        }
        temp = temp->next;
        ++position; // Tăng vị trí sau mỗi lần duyệt qua node
    }

    return -1; // Trả về -1 nếu không tìm thấy sách
}
Book *LinkedList::getNodeBook(int position)
{
    int k = 1;
    BookNode *temp = this->bookHead;
    while (k != position && temp != NULL)
    {
        temp = temp->next;
        ++k;
    }
    if (temp != NULL)
    {
        return &(temp->data); // Trả về địa chỉ của đối tượng Book
    }
    else
    {
        return nullptr; // Nếu vị trí không hợp lệ
    }
}
bool LinkedList::delete_Node_Book(Book a)
{
    int position = find_Node_Book(a); // Tìm vị trí của node chứa sách cần xóa
    if (this->bookHead == NULL || position == -1)
    {
        return false; // Nếu danh sách rỗng hoặc không tìm thấy sách, trả về false
    }

    BookNode *temp = this->bookHead;

    // Trường hợp xóa node đầu tiên
    if (position == 0)
    {
        this->bookHead = this->bookHead->next; // Chuyển con trỏ đầu đến node tiếp theo
        delete temp;                           // Xóa node đầu tiên
    }
    else
    {
        // Duyệt danh sách đến vị trí node trước node cần xóa
        int k = 0;
        BookNode *prev = nullptr;
        while (temp != NULL && k != position)
        {
            prev = temp; // Lưu lại node trước đó
            temp = temp->next;
            ++k;
        }

        if (temp != NULL)
        {
            prev->next = temp->next; // Bỏ qua node cần xóa
            delete temp;             // Xóa node cần xóa
        }
    }

    return true; // Xóa thành công
}
bool LinkedList::Insert_NodeLast(Book B)
{
    if (this->isEmpty())
    {
        bookHead = new BookNode();
        bookHead->data = B;
        bookHead->next = NULL;
    }
    else if (this->find_Node_Book(B) == -1)
    {
        BookNode *temp = bookHead;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        BookNode *newNode = new BookNode();
        newNode->data = B;
        newNode->next = NULL;
        temp->next = newNode;
    }
    else
    {
        return false; // Node already exists
    }
    return true;
}
bool LinkedList::Insert_NodeMiddle(Book B, int position)
{
    // Tạo một node mới để chứa dữ liệu sách
    BookNode *newNode = new BookNode();
    newNode->data = B;
    newNode->next = NULL;

    // Trường hợp danh sách rỗng hoặc vị trí là đầu danh sách
    if (this->isEmpty() || position <= 0)
    {
        newNode->next = bookHead;
        bookHead = newNode;
    }
    else
    {
        BookNode *temp = bookHead;
        int index = 0;

        // Duyệt danh sách đến vị trí trước vị trí chỉ định
        while (temp != NULL && index < position - 1)
        {
            temp = temp->next;
            index++;
        }

        // Trường hợp vị trí chỉ định vượt quá số phần tử hiện tại
        if (temp == NULL)
        {
            delete newNode; // Xóa node mới vì không thể chèn vào vị trí ngoài phạm vi
            return false;
        }

        // Chèn node mới vào vị trí chỉ định
        newNode->next = temp->next;
        temp->next = newNode;
    }

    return true;
}

//--------------------- create_book-----------------
// viết thêm các hàm kiểm tra có nhập đúng hay không
// nhấn enter để tiếp tục nhập nhấn esc để thoát
// Function to validate input, ensuring that only alphabetic characters are allowed
// các điều kiện

// -------------------------------------------------------------------------------------------
int LinkedList::find_NodeCustomer(Customer a)
{
    CustomerNode *temp = this->customerHead;
    int position = 0;

    while (temp != NULL)
    {
        if (temp->data.getMaKH() == a.getMaKH())
        {
            return position;
        }
        temp = temp->next;
        ++position;
    }

    return -1;
}
bool LinkedList::Add_Customer(Customer B)
{
    if (this->isEmpty())
    {
        customerHead = new CustomerNode();
        customerHead->data = B;
        customerHead->next = nullptr;
    }
    else if (this->find_NodeCustomer(B) == -1)
    {
        CustomerNode *temp = customerHead;

        // Duyệt đến cuối danh sách
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        // Tạo nút mới và thêm vào cuối danh sách
        CustomerNode *newNode = new CustomerNode();
        newNode->data = B;
        newNode->next = nullptr;
        temp->next = newNode;
    }
    else
    {
        return false; // Khách hàng đã tồn tại
    }

    return true;
}
Customer *LinkedList::getNodeCustomer(int position)
{
    int k = 1;
    CustomerNode *temp = this->customerHead;

    // Duyệt danh sách đến vị trí cần tìm
    while (k != position && temp != NULL)
    {
        temp = temp->next;
        ++k;
    }

    // Nếu tìm thấy vị trí, trả về con trỏ đến dữ liệu, nếu không trả về nullptr
    if (temp != NULL)
    {
        return &(temp->data); // Trả về địa chỉ của đối tượng Book
    }
    else
    {
        return nullptr; // Nếu vị trí không hợp lệ
    }
}
int LinkedList::find_NodeCustomer(const string &CusCode)
{
    CustomerNode *temp = this->customerHead;
    int position = 1;

    for (temp; temp != NULL; temp = temp->next)
    {
        if (temp->data.Ma_KH == CusCode)
        {
            return position;
        }
        ++position;
    }

    return -1;
}
