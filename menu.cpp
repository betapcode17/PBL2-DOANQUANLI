#include "HeThong.h"
#include "condition.h"
#include "menu.h"
Menu::Menu()
{
}
Menu::~Menu()
{
}
void Menu::Start()
{
    this->readBook("books.txt"); // Load books
    this->readCustomer("customers.txt");
}
int calculatePageCount(BookNode *book)
{
    int length = 0;
    int pages;
    while (book != nullptr)
    {
        ++length;
        book = book->next;
    }
    if (length % 10 == 0)
    {
        pages = length / 10;
    }
    else
    {
        pages = length / 10 + 1;
    }
    return pages;
}
int calculatePageCount(CustomerNode *Customer)
{
    int length = 0;
    int sum;
    while (Customer != nullptr)
    {
        ++length;
        Customer = Customer->next;
    }
    if (length % 10 == 0)
    {
        sum = length / 10;
    }
    else
    {
        sum = length / 10 + 1;
    }
    return sum;
}
void outputCustomer(int x, int y, const Customer &customer)
{
    gotoXY(x + 10, y + 1);
    cout << customer.getMaKH();
    gotoXY(x + 30, y + 1);
    cout << customer.getHoTen();
    gotoXY(x + 60, y + 1);
    cout << customer.getDia_chi();
    gotoXY(x + 85, y + 1);
    cout << customer.getSdtKH();
    gotoXY(x + 104, y + 1);
    cout << customer.getSo_tien_da_mua();
}
void outputBook(int x, int y, const Book &book)
{
    gotoXY(x + 5, y + 1);
    cout << book.getMa_Sach();
    gotoXY(x + 25, y + 1);
    cout << book.getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << book.getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << book.getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << book.getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << book.getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << book.getGia_ban();
}
void Menu::ShowAllBook()
{

    BookNode *temp = this->bookHead;
    int sum = calculatePageCount(temp);     // Calculate total pages
    BookNode **first = new BookNode *[sum]; // Store first node of each page

    for (int i = 0; i < sum; i++)
    {
        first[i] = nullptr;
    }

    int a = 0, page = 1, tam = 0;
    system("cls");
    const wchar_t *name = L"[ THÔNG TIN SÁCH ]";
    writeString(2, 2, name);
    menuDisplay(2, 4, 23, page, sum); // Display header and page info

    while (tam == 0)
    {
        while (temp != NULL)
        {
            for (int i = 0; i < 10 && temp != NULL; i++)
            { // Display 10 items per page
                a += 2;
                outputBook(2, a + 4, temp->data);
                if (a == 2)
                {
                    first[page - 1] = temp; // Store first node of current page
                }
                temp = temp->next;
            }

            // Handle key events
            int key = setKeyBoard();
            if (key == 4 && temp != NULL)
            { // Next page
                system("cls");
                writeString(2, 2, name);
                page++;
                menuDisplay(2, 4, 23, page, sum);
                a = 0;
            }
            else if (key == 3 && page > 1)
            { // Previous page
                system("cls");
                writeString(2, 2, name);
                page--;
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page - 1];
                a = 0;
            }
            else if (key == 5)
            { // Exit
                system("cls");
                tam = 1;
                break;
            }
            else if ((key == 4 && temp == NULL) || (key == 3 && page == 1))
            { // Invalid navigation
                break;
            }
        }

        if (tam == 0)
        {
            // Handle lingering navigation or exit cases
            int thu = 0;
            while (true)
            {
                int key = setKeyBoard();
                if (key == 5)
                { // Exit
                    system("cls");
                    tam = 1;
                    break;
                }
                else if (key == 3 && page == sum && page != 1)
                { // Go to previous page from the last
                    system("cls");
                    writeString(2, 2, name);
                    page--;
                    menuDisplay(2, 4, 23, page, sum);
                    temp = first[page - 1];
                    a = 0;
                    break;
                }
                else if (key == 4 && page == 1 && page != sum)
                { // Go to the second page
                    system("cls");
                    writeString(2, 2, name);
                    page++;
                    menuDisplay(2, 4, 23, page, sum);
                    if (first[1] == nullptr)
                        thu = 1;
                    else
                        temp = first[1];
                    a = 0;
                    break;
                }
            }
            if (thu == 1)
                continue;
        }
    }

    delete[] first; // Clean up allocated memory
}
// =====================================
bool TD(int a, int b)
{
    return a > b; // Sắp xếp giảm dần
}

bool GD(int a, int b)
{
    return a < b; // Sắp xếp tăng dần
}

void Swap(Book &a, Book &b)
{
    Book temp = a;
    a = b;
    b = temp;
}
void Sort(bool (*q)(int, int), int k, BookNode *b)
{

    for (BookNode *i = b; i != nullptr; i = i->next)
    {
        for (BookNode *j = i->next; j != nullptr; j = j->next)
        {
            // So sánh theo thuộc tính k với hàm con trỏ q
            switch (k)
            {
            case 1: // Sắp xếp theo Giá bán
                if ((*q)(i->data.getSo_luong(), j->data.getSo_luong()))
                {
                    Swap(i->data, j->data);
                }
                break;
            case 2: // Sắp xếp theo Số lượng
                if ((*q)(i->data.getGia_ban(), j->data.getGia_ban()))
                {
                    Swap(i->data, j->data);
                }
                break;
            case 3: // Sắp xếp theo Năm xuất bản
                if ((*q)(i->data.getNam_xuat_ban(), j->data.getNam_xuat_ban()))
                {
                    Swap(i->data, j->data);
                }
                break;
            }
        }
    }
}
BookNode *CloneList(BookNode *head)
{
    if (head == nullptr)
    {
        return nullptr;
    }

    BookNode *newHead = new BookNode(head->data);
    BookNode *current = newHead;
    BookNode *original = head->next;
    while (original != nullptr)
    {
        current->next = new BookNode(original->data);
        current = current->next;
        original = original->next;
    }

    return newHead;
}
void DeleteList(BookNode *head)
{
    while (head != nullptr)
    {
        BookNode *temp = head;
        head = head->next;
        delete temp;
    }
}
void Menu::ShowSortedBooks(int i, BookNode *b)
{
    BookNode *temp = b;
    int sum = calculatePageCount(temp);     // Tổng số trang
    BookNode **first = new BookNode *[sum]; // Lưu node đầu mỗi trang

    for (int j = 0; j < sum; j++)
    {
        first[j] = nullptr;
    }

    int a = 0, page = 1, exitFlag = 0;
    system("cls");

    // Tiêu đề theo loại sắp xếp
    const wchar_t *name;
    switch (i)
    {
    case 1:
        name = L"[ Sắp xếp tăng dần theo số lượng ]";
        break;
    case 2:
        name = L"[ Sắp xếp giảm dần theo số lượng ]";
        break;
    case 3:
        name = L"[ Sắp xếp tăng dần theo giá bán ]";
        break;
    case 4:
        name = L"[ Sắp xếp giảm dần theo giá bán ]";
        break;
    case 5:
        name = L"[ Sắp xếp tăng dần theo năm xuất bản ]";
        break;
    case 6:
        name = L"[ Sắp xếp giảm dần theo năm xuất bản ]";
        break;
    default:
        name = L"[ Sách ]";
        break;
    }

    writeString(2, 2, name);          // Hiển thị tiêu đề
    menuDisplay(2, 4, 23, page, sum); // Hiển thị trang đầu

    while (exitFlag == 0)
    {
        while (temp != NULL)
        {
            for (int j = 0; j < 10 && temp != NULL; j++)
            { // Hiển thị tối đa 10 sách mỗi trang
                a += 2;
                outputBook(2, a + 4, temp->data);
                if (a == 2)
                {
                    first[page - 1] = temp; // Lưu node đầu trang hiện tại
                }
                temp = temp->next;
            }

            // Xử lý sự kiện bàn phím
            int key = setKeyBoard();
            if (key == 4 && temp != NULL)
            { // Qua trang sau
                system("cls");
                writeString(2, 2, name);
                page++;
                menuDisplay(2, 4, 23, page, sum);
                a = 0;
            }
            else if (key == 3 && page > 1)
            { // Qua trang trước
                system("cls");
                writeString(2, 2, name);
                page--;
                menuDisplay(2, 4, 23, page, sum);
                temp = first[page - 1];
                a = 0;
            }
            else if (key == 5)
            { // Thoát
                system("cls");
                exitFlag = 1;
                break;
            }
            else if ((key == 4 && temp == NULL) || (key == 3 && page == 1))
            { // Không thể qua trang
                break;
            }
        }

        if (exitFlag == 0)
        {
            // Xử lý thoát hoặc lặp lại cuối vòng
            while (true)
            {
                int key = setKeyBoard();
                if (key == 5)
                { // Thoát
                    system("cls");
                    exitFlag = 1;
                    break;
                }
                else if (key == 3 && page == sum && page != 1)
                { // Quay lại trang trước từ trang cuối
                    system("cls");
                    writeString(2, 2, name);
                    page--;
                    menuDisplay(2, 4, 23, page, sum);
                    temp = first[page - 1];
                    a = 0;
                    break;
                }
                else if (key == 4 && page == 1 && page != sum)
                { // Đi tới trang tiếp theo từ trang đầu
                    system("cls");
                    writeString(2, 2, name);
                    page++;
                    menuDisplay(2, 4, 23, page, sum);
                    temp = first[1];
                    a = 0;
                    break;
                }
            }
        }
    }

    delete[] first; // Giải phóng bộ nhớ
}
void Menu::Sort_BookUporDown(int i, int t)
{
    BookNode *temp = CloneList(bookHead); // Use a temporary pointer to avoid modifying bookHead
    int sum = calculatePageCount(temp);   // Not sure if 'sum' is needed, but it's left here as in your code
    system("cls");                        // Clear screen once before sorting and displaying
    // Check which sorting criteria the user wants (price, quantity, or year)
    if (i == 1)
    {
        if (t == 0)
        {
            Sort(TD, 1, temp);        // Sort by price descending
            ShowSortedBooks(1, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 1, temp);        // Sort by price ascending
            ShowSortedBooks(2, temp); // Display sorted result
        }
    }
    else if (i == 2)
    {
        if (t == 0)
        {
            Sort(TD, 2, temp);        // Sort by quantity descending
            ShowSortedBooks(3, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 2, temp);        // Sort by quantity ascending
            ShowSortedBooks(4, temp); // Display sorted result
        }
    }
    else if (i == 3)
    {
        if (t == 0)
        {
            Sort(TD, 3, temp);        // Sort by year descending
            ShowSortedBooks(5, temp); // Display sorted result
        }
        else if (t == 1)
        {
            Sort(GD, 3, temp);        // Sort by year ascending
            ShowSortedBooks(6, temp); // Display sorted result
        }
    }
    DeleteList(temp);
}

void Menu::ShowAllCus()
{

    CustomerNode *temp = this->customerHead;
    int sum = calculatePageCount(temp);             // Tính tổng số trang
    CustomerNode **first = new CustomerNode *[sum]; // Lưu node đầu trang
    int a = 0, page = 1, tam = 0;

    const wchar_t *name = L"[ THÔNG TIN KHÁCH HÀNG ]";
    system("cls");
    writeString(2, 2, name);
    menuDisplay2(2, 4, 23, page, sum); // In tiêu đề trang sách
    while (tam == 0)
    {
        while (temp != NULL)
        {
            for (int i = 1; i <= 10; i++)
            {
                if (temp != NULL)
                {
                    a += 2;
                    outputCustomer(2, a + 4, temp->data); // Xuất thông tin khách hàng
                    if (a == 2)
                    {
                        first[page] = temp; // Lưu node đầu trang
                    }
                    temp = temp->next;
                }
            }

            if (setKeyBoard() == 4 && temp != NULL) // Ấn qua phải
            {
                system("cls");
                writeString(2, 2, name);
                page++;
                menuTable(2, 4, 30, 2);
                a = 0;
            }
            else if (setKeyBoard() == 3 && page > 1) // Ấn qua trái
            {
                system("cls");
                writeString(2, 2, name);
                page--;
                menuTable(2, 4, 30, 2);
                temp = first[page];
                a = 0;
            }
            else if (setKeyBoard() == 4 && temp == NULL) // Ấn qua phải ở trang cuối
            {
                break;
            }
            else if (setKeyBoard() == 3 && page - 1 <= 0) // Ấn qua trái ở trang đầu
            {
                break;
            }
            else if (setKeyBoard() == 5) // Thoát
            {
                system("cls");
                tam = 1;
                break;
            }
        }

        if (tam == 0)
        {
            int thu = 0;
            while (true)
            {
                if (setKeyBoard() == 5) // Thoát
                {
                    system("cls");
                    tam = 1;
                    break;
                }
                else if (setKeyBoard() == 3 && page == sum && page > 1) // Quay về trang trước
                {
                    system("cls");
                    writeString(2, 2, name);
                    menuTable(2, 4, 30, 2);
                    page--;
                    temp = first[page];
                    a = 0;
                    break;
                }
                else if (setKeyBoard() == 4 && page == 1 && page != sum) // Đi tới trang tiếp theo
                {
                    while (true)
                    {
                        if (setKeyBoard() == 4)
                        {
                            system("cls");
                            writeString(2, 2, name);
                            menuTable(2, 4, 30, 2);
                            page = 2;
                            if (first[2] == nullptr)
                            {
                                thu = 1;
                            }
                            else
                                temp = first[2];
                            a = 0;
                            break;
                        }
                        else if (setKeyBoard() == 5) // Thoát
                        {
                            system("cls");
                            tam = 1;
                            break;
                        }
                    }
                }
                break;
            }
            if (thu == 1)
            {
                continue;
            }
        }
    }

    // Dọn dẹp bộ nhớ
    delete[] first;
}
BookNode *Menu::filterBooks(string str, int i)
{
    BookNode *newBook = nullptr; // Head of the new list
    BookNode *tail = nullptr;    // Tail pointer to append nodes
    BookNode *temp = this->bookHead;
    int NXB;
    if (i == 4 || i == 0)
        NXB = stoi(str);

    // Iterate through the linked list
    while (temp != nullptr)
    {
        bool match = false; // Flag to track if a match is found

        // Determine what to search based on the value of i
        if (i == 1 && temp->data.getTen_sach().find(str) != string::npos)
        {
            match = true; // Search in `ten_sach`
        }
        else if (i == 2 && temp->data.getThe_loai().find(str) != string::npos)
        {
            match = true; // Search in `the_loai`
        }
        else if (i == 3 && temp->data.getTac_gia().find(str) != string::npos)
        {
            match = true; // Search in `tac_gia`
        }
        else if (i == 4 && temp->data.getNam_xuat_ban() == NXB)
        {
            match = true; // Search in `nam_xuat_ban`
        }

        // If a match is found, create a new node
        if (match)
        {
            BookNode *newNode = new BookNode;
            newNode->data = temp->data;
            newNode->next = nullptr;

            // Append to the list
            if (newBook == nullptr)
            {
                newBook = newNode; // Set as head
                tail = newNode;    // Set as tail
            }
            else
            {
                tail->next = newNode;
                tail = newNode; // Move the tail to the last node
            }
        }

        // Move to the next node
        temp = temp->next;
    }

    // If no matches are found, return nullptr
    if (newBook == nullptr)
    {
        return nullptr;
    }

    // Return the newBook list containing matched books
    return newBook;
}
void Menu::search_book(int x)
{
    int sum;
    string search;
    BookNode *temp = nullptr;
    // const wchar_t* name = L"[ THÔNG TIN SÁCH ]";

    const wchar_t *name;
    if (x == 1)
        name = L"[ Nhập tên sách ]";
    else if (x == 2)
        name = L"[ Nhập tên thể loại ]";
    else if (x == 3)
        name = L"[ Nhập tên tác giả: ]";
    else if (x == 4)
        name = L"[ Nhập năm xuất bản ]";
    if (x == 1)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->filterBooks(search, x);
            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = calculatePageCount(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 2)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->filterBooks(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = calculatePageCount(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 3)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->filterBooks(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = calculatePageCount(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    else if (x == 4)
    {
        while (true)
        {
            system("cls");
            writeString(2, 2, name);
            menuTable(2, 3, 30, 2);
            gotoXY(4, 4);
            search = getinput();

            // Gọi hàm read để tìm sách
            temp = this->filterBooks(search, x);

            // Nếu không tìm thấy sách phù hợp
            if (temp == nullptr)
            {
                writeString(4, 7, L"[ Không tìm thấy sách phù hợp ]");
                writeString(4, 8, L"[ Nhấn Enter để tìm lại hoặc ESC để thoát ]");
                int tam = getch();

                if (tam == 5)
                { // ESC để thoát
                    return;
                }
                else
                {
                    continue; // Nhấn phím khác để tiếp tục tìm kiếm
                }
            }
            else
            {
                sum = calculatePageCount(temp);
                break; // Tìm thấy sách thì thoát vòng lặp
            }
        }
    }
    int tam = 0;
    int currentPage = 0;
    const int itemsPerPage = 5;

    while (tam != 5)
    {
        int length = 0;
        BookNode *current = temp; // Dùng con trỏ khác để duyệt danh sách

        // Tính độ dài của danh sách
        for (; current != NULL; current = current->next)
        {
            ++length;
        }

        // Kiểm tra nếu length > 5 mới thực hiện phân trang
        if (length > 5)
        {
            // Vòng lặp phân trang
            while (true)
            {
                system("cls"); // Xóa màn hình trước khi hiển thị lại dữ liệu mới
                writeString(2, 2, name);
                menuTable(2, 3, 30, 2);
                gotoXY(4, 4);
                cout << search;

                // Tính tổng số trang
                int totalPages = (length + itemsPerPage - 1) / itemsPerPage;

                // Đặt con trỏ về đầu danh sách và đến đúng trang
                current = temp;
                for (int i = 0; i < currentPage * itemsPerPage && current != NULL; ++i)
                {
                    current = current->next;
                }

                // Hiển thị các sách trong trang hiện tại
                writeString(2, 7, L"[ THÔNG TIN SẢN PHẨM ]");
                bangsanpham(2, 8, itemsPerPage + 5);

                int a = 8;
                for (int i = 1; i <= itemsPerPage && current != NULL; ++i)
                {
                    a += 2;
                    outputBook(2, a, current->data);
                    current = current->next;
                }

                // Hiển thị điều hướng nếu có nhiều hơn 1 trang
                writeString(2, 2, name);
                menuTable(2, 3, 30, 2);
                gotoXY(4, 4);
                cout << search;
                gotoXY(100, 6);
                cout << "Trang " << currentPage + 1 << " / " << totalPages;
                writeString(2, 25, L"Nhấn nút [->] để tới trang tiếp theo, [<-] để quay về trang trước!!");
                // Nhận phím từ người dùng
                tam = setKeyBoard();

                // Điều hướng trái/phải qua các trang
                if (tam == 4 && currentPage < totalPages - 1)
                {
                    currentPage++; // Sang trang tiếp theo
                }
                else if (tam == 3 && currentPage > 0)
                {
                    currentPage--; // Quay lại trang trước
                }
                else if (tam == 5)
                {          // Nếu nhấn ESC (giá trị 27)
                    break; // Thoát khỏi vòng lặp phân trang
                }
            }
        }

        else
        {
            // Nếu danh sách <= 5, hiển thị bình thường
            current = temp;
            writeString(2, 7, L"[ THÔNG TIN SẢN PHẨM ]");
            bangsanpham(2, 8, length + 5);

            int a = 8;
            for (int i = 1; i <= length && current != NULL; ++i)
            {
                a += 2;
                outputBook(2, a, current->data);
                current = current->next;
            }

            // Không cần phân trang, chỉ thoát khi người dùng nhấn phím
            tam = setKeyBoard();
            if (tam == 5)
            {
                return; // Thoát
            }
        }
    }
}
void WriteBookToFile(const string &bookID, const string &bookName, const string &bookGenre,
                     const string &bookAuthor, int quantity, int price, int publicationYear)
{
    // Mở file để đọc
    std::ifstream inFile("books.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::ostringstream tempBuffer;
    std::string line;
    bool bookFound = false;
    int totalBooks = 0;

    // Đọc dòng đầu tiên để lấy tổng số sách hiện tại
    if (std::getline(inFile, line))
    {
        totalBooks = std::stoi(line); // Chuyển đổi số sách từ chuỗi sang int
    }

    // Đọc các dòng còn lại của file và kiểm tra sự tồn tại của sách
    while (std::getline(inFile, line))
    {
        std::istringstream lineStream(line);
        std::string id, name, genre, author;
        int existingQuantity, existingPrice, year;

        std::getline(lineStream, id, '|');
        std::getline(lineStream, name, '|');
        std::getline(lineStream, genre, '|');
        std::getline(lineStream, author, '|');
        lineStream >> year;
        lineStream.ignore(1, '|');
        lineStream >> existingQuantity;
        lineStream.ignore(1, '|');
        lineStream >> existingPrice;

        if (id == bookID)
        {
            bookFound = true;
            // Ghi dữ liệu sách mới vào bộ đệm tạm khi tìm thấy
            tempBuffer << bookID << "|" << bookName << "|" << bookGenre << "|" << bookAuthor << "|"
                       << quantity << "|" << price << "|" << publicationYear << "\n";
        }
        else
        {
            // Ghi lại dòng cũ vào bộ đệm tạm
            tempBuffer << line << "\n";
        }
    }

    inFile.close();

    // Nếu sách không tồn tại, thêm sách mới và tăng tổng số sách
    if (!bookFound)
    {
        totalBooks += 1; // Tăng tổng số sách lên 1
        tempBuffer << bookID << "|" << bookName << "|" << bookGenre << "|" << bookAuthor << "|"
                   << quantity << "|" << price << "|" << publicationYear << "\n";
    }

    // Ghi lại nội dung mới vào file, bao gồm dòng tổng số sách ở đầu
    std::ofstream outFile("books.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    outFile << totalBooks << "\n"; // Ghi lại tổng số sách ở dòng đầu tiên
    outFile << tempBuffer.str();   // Ghi lại nội dung của các sách còn lại
    outFile.close();
}
bool Menu::CreateBook()
{
    ShowCursor(TRUE);
    int x = 2, y = 2;
    string bookID, bookName, bookGenre, bookAuthor, publicationYear, quantity, price;
    int gia_ban, so_luong, year;
    menuTable(x + 18, y + 28, 50, 2);
    writeString(x + 20, y + 29, L"[ENTER]  CONTINUE");
    writeString(x + 40, y + 29, L"[ESC]  SAVE & EXIT");
    writeString(x, y, L"[ THÊM SẢN PHẨM ]");
    bangsanpham(x, y + 1, 20);
    if (this->bookHead != nullptr)
    {
        BookNode *book = this->bookHead;
        while (book->next != nullptr)
        {
            book = book->next;
        }
        bookID = book->data.getMa_Sach();
        try
        {
            // Tách phần số từ chuỗi và tăng lên 1
            int numberPart = std::stoi(bookID.substr(1)) + 1;
            bookID = "B" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error processing bookID: " << e.what() << std::endl;
            return false; // Thoát nếu không thể chuyển đổi
        }
    }
    else
    {
        // If there are no books in the list, start with B001
        bookID = "B001";
    }
    do
    {
        gotoXY(x + 4, y + 4);
        cout << bookID;
        while (true)
        {
            writeString(37, 2, L"[ Tên sách phải dài ít nhất 4 ký tự! ]");
            gotoXY(x + 25, y + 4);
            getline(cin, bookName); // Dùng getline để nhập tên sách, có thể chứa khoảng trắng
            if (bookName.length() >= 4 && isAlphaString(bookName))
            {
                break;
            }
            else
            {
                trolaisua(x + 25, y + 4, bookName);
            }
        }

        while (true)
        {
            writeString(37, 2, L"[ Thể loại phải dài ít nhất 3 ký tự! ]");
            gotoXY(x + 60, y + 4);
            getline(cin, bookGenre); // Dùng getline để nhập thể loại
            if (bookGenre.length() >= 3 && isAlphaString(bookGenre))
            {
                break;
            }
            else
            {
                trolaisua(x + 60, y + 4, bookGenre);
            }
        }

        while (true)
        {
            writeString(37, 2, L"Tên tác giả phải dài ít nhất 4 ký tự!");
            gotoXY(x + 85, y + 4);
            getline(cin, bookAuthor); // Dùng getline để nhập tên tác giả
            if (bookAuthor.length() >= 4 && isAlphaString(bookAuthor))
            {
                break;
            }
            else
            {
                trolaisua(x + 85, y + 4, bookAuthor);
            }
        }
        while (true)
        {
            string nam_xuat_ban;
            writeString(37, 2, L"  Năm xuất bản phải có 4 kí tự!      ");
            gotoXY(x + 104, y + 4);
            nam_xuat_ban = getinput();
            if (isValidYear(nam_xuat_ban))
            {
                try
                {
                    year = stoi(nam_xuat_ban);
                    gotoXY(x + 104, y + 4);
                    cout << nam_xuat_ban;
                    break;
                }
                catch (const std::exception &e)
                {
                    writeString(37, 2, L"  Năm xuất bản phải có 4 kí tự!      ");
                }
            }
            else
            {
                trolaisua(x + 104, y + 4, nam_xuat_ban);
            }
        }
        while (true)
        {
            string quantity;
            writeString(37, 2, L"  Số lượng phải nhỏ hơn 999!         ");

            gotoXY(x + 125, y + 4);
            quantity = getinput();
            if (isValidQuantity(quantity))
            {
                try
                {
                    so_luong = stoi(quantity);
                    gotoXY(x + 125, y + 4);
                    cout << so_luong;
                    break;
                }
                catch (const std::exception &e)
                {
                    writeString(50, y + 7, L"Lỗi: Giá trị số lượng không hợp lệ.");
                }
            }
            else
            {

                trolaisua(x + 125, y + 4, quantity);
            }
        }
        while (true)
        {
            string price;
            writeString(37, 2, L"  Giá sách phải lớn hơn 1000!         ");
            gotoXY(x + 136, y + 4);
            price = getinput();
            if (isValidPrice(price))
            {
                try
                {
                    gia_ban = stoi(price);
                    gotoXY(x + 136, y + 4);
                    cout << gia_ban;
                    break;
                }
                catch (const std::exception &e)
                {
                    writeString(50, y + 7, L"Lỗi: Giá trị giá sách không hợp lệ.");
                }
            }
            else
            {
                trolaisua(x + 136, y + 4, price);
            }
        }
        Book newBook(bookID, bookName, bookGenre, bookAuthor, year, so_luong, gia_ban);
        Insert_NodeLast(newBook);
        WriteBookToFile(bookID, bookName, bookGenre, bookAuthor, so_luong, gia_ban, year);
        int numberPart = std::stoi(bookID.substr(1)) + 1;
        bookID = "B" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
        // system("cls");
        // cout<<bookID;
        // system("pause");
        int key = batphim();
        if (key == 3)
        {
            y += 2;
            continue;
        }
        else if (key == 4)
        {
            break;
        }
    } while (true);
    return true;
}
bool Menu::UpdateBook()
{
    int position;
    while (true)
    {
        const wchar_t *name = L"[ Nhập Mã sách ]";
        writeString(10, 2, name);
        menuTable(27, 1, 30, 2);
        gotoXY(28, 2);

        string searchmasach = getinput();
        position = find_Node_Book(searchmasach); // Tìm vị trí sách bằng cách tìm mã sách

        if (position == -1)
        {
            writeString(27, 4, L"Không tồn tại sách có mã như trên.");
            gotoXY(28, 2);
            cout << string(10, ' ');
        }
        else
        {
            break;
        }
    }
    // Lấy thông tin sách
    Book *update = getNodeBook(position);
    // Xóa sách tại vị trí cũ
    // Hiển thị bảng sản phẩm để cập nhật
    bangsanpham(3, 8, 2);
    int x = 4, y = 10;
    writeString(x + 1, y - 4, L"[ THÔNG TIN SẢN PHẨM ]");

    // Hiển thị thông tin hiện tại của sách
    gotoXY(x + 10, y + 1);
    cout << update->getMa_Sach();
    gotoXY(x + 30, y + 1);
    cout << update->getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << update->getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << update->getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << update->getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << update->getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << update->getGia_ban();
    delete_Node_Book(*update);
    // Bảng sửa sản phẩm
    writeString(x + 1, y + 6, L"[ SỬA SẢN PHẨM ]");
    bangsanpham(3, 18, 2);
    // Vòng lặp chỉnh sửa trực tiếp
    int x_click, y_click;
    string new_TenSach, new_TheLoai, new_TacGia;
    while (true)
    {
        gotoXY(x + 10, y + 12);
        cout << update->getMa_Sach();
        setClick(x_click, y_click);

        if (23 <= x_click && x_click <= 52 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Tên Sách
            while (true)
            {
                writeString(50, y + 6, L" Tên sách phải dài ít nhất 4 ký tự! ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 30, y + 12);
                new_TenSach = getinput(); // Dùng getline để nhập tên sách, có thể chứa khoảng trắng
                if (new_TenSach.length() >= 4 && isAlphaString(new_TenSach))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 30, y + 12, new_TenSach);
                }
            }
            update->SetTen_sach(new_TenSach);
            gotoXY(x + 30, y + 12);
            cout << new_TenSach;
        }
        else if (52 <= x_click && x_click <= 82 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Thể Loại
            while (true)
            {
                writeString(50, y + 6, L"[ Thể loại phải dài ít nhất 3 ký tự! ]");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 60, y + 12);
                new_TheLoai = getinput(); // Dùng getline để nhập thể loại
                if (new_TheLoai.length() >= 3 && isAlphaString(new_TheLoai))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 60, y + 4, new_TheLoai);
                }
            }
            update->SetThe_Loai(new_TheLoai);
            gotoXY(x + 60, y + 12);
            cout << new_TheLoai;
        }
        else if (82 <= x_click && x_click <= 102 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Tác Giả
            while (true)
            {
                writeString(50, y + 6, L"Tên tác giả phải dài ít nhất 4 ký tự!");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 85, y + 12);
                new_TacGia = getinput(); // Dùng getline để nhập tên tác giả
                if (new_TacGia.length() >= 4 && isAlphaString(new_TacGia))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 85, y + 12, new_TacGia);
                }
            }
            update->SetTac_Gia(new_TacGia);
            gotoXY(x + 85, y + 12);
            cout << new_TacGia;
        }
        else if (102 <= x_click && x_click <= 122 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Năm Xuất Bản
            string nam_xuat_ban;
            while (true)
            {

                writeString(50, y + 6, L"  Năm xuất bản phải có 4 kí tự!      ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 104, y + 12);
                nam_xuat_ban = getinput(); // Dùng getline để nhập năm xuất bản
                if (isValidYear(nam_xuat_ban))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 104, y + 4, nam_xuat_ban);
                }
            }
            int year;
            year = stoi(nam_xuat_ban);
            update->SetNXB(year);
            gotoXY(x + 104, y + 12);
            cout << nam_xuat_ban;
        }
        else if (122 <= x_click && x_click <= 132 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Số Lượng
            string quantity;
            while (true)
            {

                writeString(50, y + 6, L"  Số lượng phải nhỏ hơn 999!         ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 125, y + 12);
                quantity = getinput(); // Dùng getline để nhập số lượng
                if (isValidQuantity(quantity))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 125, y + 12, quantity);
                }
            }
            int so_luong;
            so_luong = stoi(quantity);
            update->SetSo_Luong(so_luong);
            gotoXY(x + 125, y + 12);
            cout << so_luong;
        }
        else if (132 <= x_click && x_click <= 152 && 17 <= y_click && y_click <= 22)
        {
            // Sửa Giá Bán
            string price;
            while (true)
            {

                writeString(50, y + 6, L"  Giá sách phải lớn hơn 1000!        ");
                menuTable(49, y + 5, 40, 2);
                gotoXY(x + 136, y + 12);
                price = getinput(); // Dùng getline để nhập giá sách
                if (isValidPrice(price))
                {
                    break;
                }
                else
                {
                    trolaisua(x + 136, y + 12, price);
                }
            }
            int gia_ban;
            gia_ban = stoi(price);
            update->SetGia_Ban(gia_ban);
            gotoXY(x + 136, y + 12);
            cout << gia_ban;
        }
        else
        {
            break; // Kết thúc cập nhật
        }
    }
    WriteBookToFile(update->getMa_Sach(), update->getTen_sach(), update->getThe_loai(),
                    update->getTac_gia(), update->getSo_luong(), update->getGia_ban(), update->getNam_xuat_ban());
    Insert_NodeMiddle(*update, position - 1);
    return true;
}
void DeleteBookFromFile(const std::string &bookID)
{
    // Mở file để đọc
    std::ifstream inFile("books.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Error opening file for reading!" << std::endl;
        return;
    }

    std::ostringstream tempBuffer;
    std::string line;
    bool bookFound = false;
    int totalBooks = 0;

    // Đọc dòng đầu tiên để lấy tổng số sách hiện tại
    if (std::getline(inFile, line))
    {
        try
        {
            totalBooks = std::stoi(line); // Chuyển đổi số sách từ chuỗi sang int
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid number format in the input file: " << e.what() << std::endl;
            inFile.close();
            return;
        }
    }

    // Đọc các dòng còn lại của file và kiểm tra sự tồn tại của sách
    while (std::getline(inFile, line))
    {
        std::istringstream lineStream(line);
        std::string id, name, genre, author;
        int existingQuantity, existingPrice, year;

        std::getline(lineStream, id, '|');
        std::getline(lineStream, name, '|');
        std::getline(lineStream, genre, '|');
        std::getline(lineStream, author, '|');
        lineStream >> year;
        lineStream.ignore(1, '|');
        lineStream >> existingQuantity;
        lineStream.ignore(1, '|');
        lineStream >> existingPrice;

        if (id == bookID)
        {
            bookFound = true;
            totalBooks -= 1; // Giảm tổng số sách vì sách đã được xóa
            continue;        // Bỏ qua dòng chứa sách cần xóa
        }
        else
        {
            // Ghi lại dòng cũ vào bộ đệm tạm
            tempBuffer << line << "\n";
        }
    }

    inFile.close();

    // Kiểm tra nếu sách không được tìm thấy
    if (!bookFound)
    {
        std::cerr << "Book with ID " << bookID << " not found!" << std::endl;
        return;
    }

    // Ghi lại nội dung mới vào file, bao gồm dòng tổng số sách ở đầu
    std::ofstream outFile("books.txt");
    if (!outFile.is_open())
    {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    outFile << totalBooks << "\n"; // Ghi lại tổng số sách ở dòng đầu tiên
    outFile << tempBuffer.str();   // Ghi lại nội dung của các sách còn lại
    outFile.close();
}
bool Menu::DeleteBook()
{
    int position;
    while (true)
    {
        const wchar_t *name = L"[ Nhập Mã sách ]";
        writeString(10, 2, name);
        menuTable(27, 1, 30, 2);
        gotoXY(28, 2);

        string searchmasach = getinput();
        position = find_Node_Book(searchmasach); // Tìm vị trí sách bằng cách tìm mã sách

        if (position == -1)
        {
            writeString(27, 4, L"Không tồn tại sách có mã như trên.");
            gotoXY(28, 2);
            cout << string(10, ' ');
        }
        else
        {
            break;
        }
    }
    Book *DeleteBook = getNodeBook(position);

    // Hiển thị thông tin sách cần xóa
    bangsanpham(3, 8, 2);
    int x = 4, y = 10;
    writeString(x + 1, y - 4, L"[ THÔNG TIN SẢN PHẨM ]");
    gotoXY(x + 10, y + 1);
    cout << DeleteBook->getMa_Sach();
    gotoXY(x + 30, y + 1);
    cout << DeleteBook->getTen_sach();
    gotoXY(x + 60, y + 1);
    cout << DeleteBook->getThe_loai();
    gotoXY(x + 85, y + 1);
    cout << DeleteBook->getTac_gia();
    gotoXY(x + 104, y + 1);
    cout << DeleteBook->getNam_xuat_ban();
    gotoXY(x + 125, y + 1);
    cout << DeleteBook->getSo_luong();
    gotoXY(x + 136, y + 1);
    cout << DeleteBook->getGia_ban();
    int response = MessageBoxW(NULL, L"Bạn có chắc chắn muốn xóa sách này không?", L"Xác nhận", MB_OKCANCEL | MB_ICONQUESTION);
    if (response == IDOK)
    {
        delete_Node_Book(*DeleteBook);
        DeleteBookFromFile(DeleteBook->getMa_Sach()); // Xóa sách nếu người dùng nhấn OK
        return true;
    }
    else
    {
        writeString(30, 22, L"Hủy bỏ việc xóa sách.");
        return false;
    }
}
void outputInvoice(int x, int y, string maHoaDon, string makhachhang, string ngayLap, int soLuong, int tongTien)
{
    gotoXY(x + 5, y + 1); // Position for Mã HĐ
    cout << maHoaDon;
    gotoXY(x + 25, y + 1); // Position for Mã KH
    cout << makhachhang;
    gotoXY(x + 45, y + 1); // Position for Ngày lập hóa đơn
    cout << ngayLap;
    gotoXY(x + 70, y + 1); // Position for Số lượng
    cout << soLuong;
    gotoXY(x + 90, y + 1); // Position for Tổng tiền
    cout << tongTien;
}
void displayInvoice(int n, string maHoaDonArr[], string makhachhangArr[], string ngayLapArr[], int soLuongArr[], int tongTienArr[])
{
    int page = 1;
    int totalPages = (n + 4) / 5; // Tổng số trang, mỗi trang 10 hóa đơn
    int tam = 0;
    while (tam == 0)
    {
        system("cls");
        const wchar_t *title = L"[ THÔNG TIN HÓA ĐƠN ]";
        writeString(2, 2, title);
        Bill_Table(2, 4, 23, page, totalPages);
        // In hóa đơn trên trang hiện tại
        int start = (page - 1) * 10;
        int end = min(start + 10, n);

        int y = 6;
        for (int i = start; i < end; ++i)
        {
            outputInvoice(2, y, maHoaDonArr[i], makhachhangArr[i], ngayLapArr[i], soLuongArr[i], tongTienArr[i]);
            y += 2;
        }

        int key = setKeyBoard();
        if (key == 4 && page < totalPages)
        { // Ấn qua phải để sang trang tiếp theo
            page++;
        }
        else if (key == 3 && page > 1)
        { // Ấn qua trái để quay lại trang trước
            page--;
        }
        else if (key == 5)
        { // Ấn thoát
            system("cls");
            tam = 1;
            break;
        }
    }
}
void Menu::statistical()
{

    int x = 30, y = 5;
    int thang, nam;
    int sum_products = 0;
    int sum_capital = 0;
    int num_customers = 0;
    int total_revenue = 0;
    int count_books = 0;
    // Initial statistics
    BookNode *tempBook = this->bookHead;
    while (tempBook != nullptr)
    {
        sum_products += tempBook->data.getSo_luong();
        sum_capital += tempBook->data.getGia_ban();
        count_books++;
        tempBook = tempBook->next;
    }

    // Customer statistics
    CustomerNode *tempCustomer = customerHead;
    while (tempCustomer != nullptr)
    {
        num_customers++;
        total_revenue += tempCustomer->data.getSo_tien_da_mua();
        tempCustomer = tempCustomer->next;
    }

    int selectedOption = 0;
    char key;
    while (true)
    {
        system("cls");
        menuTable(x, y - 3, 60, 2);
        writeString(x + 15, y - 2, L"[THỐNG KÊ THÔNG TIN CỬA HÀNG]");
        menuTable(x, y, 60, 20);
        writeString(x + 2, y + 2, L"Tổng số mặt hàng sách trong cửa hàng:");
        gotoXY(x + 40, y + 2);
        cout << count_books;
        writeString(x + 2, y + 5, L"Tổng số lượng sách:");
        gotoXY(x + 25, y + 5);
        cout << sum_products;
        writeString(x + 2, y + 7, L"Vốn nhập hàng:");
        gotoXY(x + 16, y + 7);
        cout << sum_capital;
        writeString(x + 2, y + 9, L"Tổng số khách hàng mua hàng:");
        gotoXY(x + 30, y + 9);
        cout << num_customers;
        gotoXY(x + 2, y + 12);
        cout << "Tổng tiền thu được: " << total_revenue;
        writeString(x + 2, y + 18, selectedOption == 0 ? L"[ CHI TIẾT ]" : L"  CHI TIẾT  ");
        writeString(x + 30, y + 18, selectedOption == 1 ? L"[ TRO VE ]" : L"  TRO VE  ");
        key = batphim();

        if (key == 8)
        {
            if (selectedOption < 2)
            {
                selectedOption++;
            }
        }
        else if (key == 7)
        {
            if (selectedOption > 0)
            {
                selectedOption--;
            }
        }
        else if (key == 3)
        {
            if (selectedOption == 0)
            {
                bool detailMenu = true;
                while (detailMenu)
                {
                    system("cls");
                    string year, month, day;
                    bool found = false;
                    // nhập năm
                    writeString(x, y, L"Nhập Năm cần thống kê");
                    menuTable(x + 25, y - 1, 20, 2);
                    gotoXY(x + 26, y);
                    getline(cin, year);

                    if (!isValidYear(year))
                    {
                        trolaisua(x + 26, y, year);
                        continue;
                    }
                    // nhập tháng
                    writeString(x, y + 4, L"Nhập Tháng cần thống kê");
                    menuTable(x + 25, y + 3, 20, 2);
                    gotoXY(x + 27, y + 4);
                    getline(cin, month);

                    if (!isValidMonth(month))
                    {
                        trolaisua(x + 27, y + 4, month);
                        continue;
                    }
                    // nhập ngày
                    writeString(x, y + 8, L"Nhập ngày cần thống kê");
                    menuTable(x + 25, y + 7, 20, 2);
                    gotoXY(x + 27, y + 8);
                    getline(cin, day);

                    if (!isValidDate(day, month))
                    {
                        trolaisua(x + 27, y + 8, day);
                        continue;
                    }
                    ifstream infile("bill.txt");
                    if (!infile)
                    {
                        cout << "Khong the mo file!" << endl;
                        return;
                    }

                    int sum_productsdetail = 0, sum_capitaldetail = 0, sum_cusDetail = 0, sum_BookDetail = 0;
                    int n;
                    infile >> n;
                    int count = 0; // Biến đếm số lượng hóa đơn hợp lệ
                    infile.ignore();
                    string maHoaDonArr[1000]; // Giả sử số hóa đơn không quá 1000
                    string makhachhangArr[1000];
                    string ngayLapArr[1000];
                    int soLuongArr[1000];
                    int tongTienArr[1000];
                    for (int i = 1; i <= n; ++i)
                    {
                        string maHoaDon, ngayLap, makhachhang;
                        int soLuong, tongTien, ngay, thang_hoa_don, nam_hoa_don;
                        getline(infile, maHoaDon, '|');
                        getline(infile, makhachhang, '|');
                        getline(infile, ngayLap, '|');
                        infile >> soLuong;
                        infile.ignore(1);
                        infile >> tongTien;
                        infile.ignore(1);
                        sscanf(ngayLap.c_str(), "%d-%d-%d", &nam_hoa_don, &thang_hoa_don, &ngay);
                        if (thang_hoa_don == stoi(month) && nam_hoa_don == stoi(year) && ngay == stoi(day))
                        {
                            maHoaDonArr[count] = maHoaDon;
                            makhachhangArr[count] = makhachhang;
                            ngayLapArr[count] = ngayLap;
                            soLuongArr[count] = soLuong;
                            tongTienArr[count] = tongTien;

                            sum_productsdetail += soLuong;
                            sum_capitaldetail += tongTien;
                            sum_cusDetail++;
                            sum_BookDetail++;
                            found = true;
                            count++; // Tăng biến đếm
                        }
                    }
                    infile.close();

                    if (found)
                    {
                        int Sub_selectedOption = 0;
                        while (true)
                        {
                            system("cls");
                            menuTable(x, y - 3, 60, 2);
                            writeString(x + 15, y - 2, L"[THỐNG KÊ CHI TIẾT TRONG THÁNG]");
                            menuTable(x, y, 60, 15);
                            writeString(x + 2, y + 4, L"Tổng số lượng sách đã bán:");
                            gotoXY(x + 30, y + 4);
                            cout << sum_productsdetail;
                            writeString(x + 2, y + 6, L"Doanh thu trong tháng:");
                            gotoXY(x + 40, y + 6);
                            cout << sum_capitaldetail << " VND";
                            writeString(x + 2, y + 8, L"Số lượng khách hàng:");
                            gotoXY(x + 30, y + 8);
                            cout << sum_cusDetail;
                            writeString(x + 2, y + 18, Sub_selectedOption == 0 ? L"[ CHI TIẾT ]" : L"  CHI TIẾT  ");
                            writeString(x + 30, y + 18, Sub_selectedOption == 1 ? L"[ TRO VE ]" : L"  TRO VE  ");

                            int Sub_key = batphim();
                            if (Sub_key == 8) // Right arrow
                            {
                                if (Sub_selectedOption < 1)
                                {
                                    Sub_selectedOption++;
                                }
                            }
                            else if (Sub_key == 7) // Left arrow
                            {
                                if (Sub_selectedOption > 0)
                                {
                                    Sub_selectedOption--;
                                }
                            }
                            else if (Sub_key == 3) // Enter key
                            {
                                if (Sub_selectedOption == 0)
                                {
                                    displayInvoice(count, maHoaDonArr, makhachhangArr, ngayLapArr, soLuongArr, tongTienArr);
                                }
                                else if (Sub_selectedOption == 1)
                                {
                                    detailMenu = false; // Exit to main statistics view
                                    break;
                                }
                            }
                        }
                    }
                    else
                    {
                        system("cls");
                        writeString(x + 1, y + 4, L"Không tồn tại năm, tháng như đã nhập");
                        menuTable(x, y + 3, 42, 2);
                        if (setKeyBoard() == 5)
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                return;
            }
        }
    }
}
