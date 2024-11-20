#include "HeThong.h"
#include "Order.h"
#include "condition.h"
using namespace std;
Order::Order()
{
    this->Start();
    bookCode = new Book *[1000]; // Cấp phát mảng con trỏ
    bookCount = new int[1000];   // Cấp phát mảng số lượng sách
    types = 0;
}
Order::~Order()
{
    for (int i = 0; i < types; i++)
    {
        delete bookCode[i];
    }

    // Giải phóng mảng bookCode và bookCount
    delete[] bookCode;
    delete[] bookCount;
}
void Order ::Display_product()
{
    int x = 2, y = 2, a = 2;
    for (int i = 0; i < types; i++)
    {
        // Hiển thị thông tin sách đã chọn
        gotoXY(x + 10, a + 9);
        cout << bookCode[i]->getMa_Sach();
        gotoXY(x + 30, a + 9);
        cout << bookCode[i]->getTen_sach();
        gotoXY(x + 60, a + 9);
        cout << bookCode[i]->getThe_loai();
        gotoXY(x + 85, a + 9);
        cout << bookCode[i]->getTac_gia();
        gotoXY(x + 104, a + 9);
        cout << bookCode[i]->getNam_xuat_ban();
        gotoXY(x + 125, a + 9);
        cout << bookCount[i];
        gotoXY(x + 136, a + 9);
        cout << bookCode[i]->getGia_ban();

        a += 2; // Tăng tọa độ a để hiển thị thông tin của sách tiếp theo ở dòng dưới
    }
}
void Order::Add_Product()
{
    system("cls");
    int x = 2, y = 2, a = 2;
    string masach;
    int soluong;
    Book *foundBook = nullptr;
    int position;

    // Hiển thị giao diện nhập
    writeString(x + 125, y, L"Xem thông tin sách");
    menuTable(x + 120, y - 1, 25, 2);
    writeString(x, y, L"[Nhập mã sách cần bán]");
    menuTable(x + 23, y - 1, 25, 2);
    writeString(x + 70, y, L"[Nhập số lượng:]");
    menuTable(x + 90, y - 1, 25, 2);
    writeString(x + 1, y + 4, L"[ THÔNG TIN SẢN PHẨM ]");
    menuDisplay(x + 1, y + 6, 20, 1, 1);
    Display_product();
    gotoXY(x + 24, y);
    cout << string(20, ' '); // Xóa nội dung cũ
    gotoXY(x + 102, y);
    cout << string(10, ' ');
    while (true)
    {
        // Nhập mã sách
        while (true)
        {
            gotoXY(x + 24, y);
            cout << string(20, ' '); // Xóa nội dung cũ
            gotoXY(x + 24, y);
            masach = getinput();

            position = find_Node_Book(masach);
            if (position != -1)
            {
                foundBook = getNodeBook(position);
                break; // Tìm thấy sách
            }
            else
            {
                writeString(x + 23, y + 2, L"[Không tồn tại mã sách. Vui lòng nhập lại]");
            }
        }

        // Nhập số lượng
        while (true)
        {
            gotoXY(x + 102, y);
            cout << string(10, ' '); // Xóa nội dung cũ
            gotoXY(x + 102, y);
            try
            {
                soluong = stoi(getNumericInput());
                if (soluong > 0 && soluong <= foundBook->getSo_luong())
                {
                    break; // Nhập hợp lệ
                }
                else
                {
                    writeString(x + 70, y + 2, L"[Số lượng vượt quá số lượng hiện có hoặc không hợp lệ]");
                }
            }
            catch (exception &e)
            {
                writeString(x + 70, y + 2, L"[Đầu vào không hợp lệ. Vui lòng nhập số]");
            }
        }

        // Kiểm tra mã sách đã tồn tại trong danh sách
        bool exists = false;
        for (int i = 0; i < types; i++)
        {
            if (bookCode[i]->getMa_Sach() == masach)
            {
                bookCount[i] += soluong; // Cộng dồn số lượng
                writeString(x + 23, y + 3, L"[Sách đã tồn tại, số lượng được cập nhật]");
                exists = true;
                break;
            }
        }

        // Nếu sách chưa tồn tại, thêm mới
        if (!exists)
        {
            bookCode[types] = foundBook;
            bookCount[types] = soluong;
            types++;
        }

        // Hiển thị thông tin sản phẩm đã thêm hoặc cập nhật
        Display_product();

        // Hỏi người dùng có muốn thêm sản phẩm khác không
        int response = MessageBoxW(NULL, L"Bạn có muốn chọn thêm sản phẩm không?", L"Xác nhận", MB_OKCANCEL | MB_ICONQUESTION);
        if (response != IDOK)
        {
            break; // Người dùng không muốn thêm
        }
    }
}
void Order::confirm()
{
    string billDay, cusCode, newNameCus, newCusAddress, newCusSdt;
    int sum = 0;
    int x = 20, y = 2;
    int a = 5;
    int selectedOption = 0; // 0 = "Xóa sản phẩm", 1 = "Sửa sản phẩm", 2 = "Tiếp tục thanh toán"
    int selectedProduct;
    int keyInput;
    system("cls");
    writeString(x, y, L"[ DANH SÁCH SẢN PHẨM ĐÃ CHỌN ]");
    Ordertable(x, y + 4, 20);
    // Menu items positions
    int menuX = x, menuY = y + 30;
    while (true)
    {
        // Clear the screen and redraw menu
        system("cls");
        writeString(x, y, L"[ DANH SÁCH SẢN PHẨM ĐÃ CHỌN ]");
        Ordertable(x, y + 4, 20);
        a = 5;
        for (int i = 0; i < types; i++)
        {
            gotoXY(x + 5, a + 5);
            cout << i + 1;
            gotoXY(x + 20, a + 5);
            cout << bookCode[i]->getTen_sach();
            gotoXY(x + 50, a + 5);
            cout << bookCount[i];
            gotoXY(x + 70, a + 5);
            cout << bookCode[i]->getGia_ban();
            gotoXY(x + 85, a + 5);
            cout << bookCode[i]->getGia_ban() * bookCount[i];
            a = a + 2;
        }
        menuTable(menuX, menuY, 110, 2); // Tăng chiều rộng menu cho phù hợp với 4 mục
        writeString(menuX + 5, menuY + 1, selectedOption == 0 ? L"[ Xóa sản phẩm ]" : L"  Xóa sản phẩm");
        writeString(menuX + 30, menuY + 1, selectedOption == 1 ? L"[ Sửa sản phẩm ]" : L"  Sửa sản phẩm");
        writeString(menuX + 55, menuY + 1, selectedOption == 2 ? L"[ Thêm sản phẩm ]" : L"  Thêm sản phẩm");
        writeString(menuX + 80, menuY + 1, selectedOption == 3 ? L"[ Tiếp tục thanh toán ]" : L"  Tiếp tục thanh toán");
        // Chờ nhận phím từ hàm batphim
        keyInput = batphim();
        // Di chuyển trong menu dựa trên phím mũi tên
        if (keyInput == 8) // RIGHT key (sang phải)
        {
            if (selectedOption < 3) // Bây giờ có 4 lựa chọn (0-3)
            {
                selectedOption++;
            }
        }
        else if (keyInput == 7) // LEFT key (sang trái)
        {
            if (selectedOption > 0)
            {
                selectedOption--;
            }
        }
        else if (keyInput == 3) // Khi nhấn phím Enter
        {
            system("cls"); // Xóa màn hình khi chọn một mục
            if (selectedOption == 0)
            {
                // Xử lý "Xóa sản phẩm"
                writeString(x, y, L"[ Chọn sản phẩm cần xóa ]");
                writeString(x, y, L"[ Chọn sản phẩm cần xóa ]");
                menuTable(x + 25, y - 1, 20, 2);
                Ordertable(x, y + 4, 20);
                for (int i = 0; i < types; i++)
                {
                    gotoXY(x + 5, a + 3);
                    cout << i + 1;
                    gotoXY(x + 20, a + 3);
                    cout << bookCode[i]->getTen_sach();
                    gotoXY(x + 50, a + 3);
                    cout << bookCount[i];
                    gotoXY(x + 70, a + 3);
                    cout << bookCode[i]->getGia_ban();
                    gotoXY(x + 85, a + 3);
                    cout << bookCode[i]->getGia_ban() * bookCount[i];
                    a = a + 2;
                }
                gotoXY(x + 28, y);
                cin >> selectedProduct;
                if (selectedProduct >= 1 && selectedProduct <= types)
                {
                    // Show confirmation message
                    int response = MessageBoxW(
                        NULL,
                        L"Bạn có chắc chắn muốn xóa sản phẩm?",
                        L"Xác nhận",
                        MB_OKCANCEL | MB_ICONQUESTION);

                    // If the user confirms, delete the product
                    if (response == IDOK)
                    {
                        // Remove the product from the list
                        for (int i = selectedProduct - 1; i < types - 1; i++)
                        {
                            bookCode[i] = bookCode[i + 1];
                            bookCount[i] = bookCount[i + 1];
                        }
                        types--;
                    }
                    else
                    {
                        writeString(x, y + 2, L"Hủy bỏ thao tác xóa.");
                    }
                }
                else
                {
                    writeString(x, y + 2, L"Mã sản phẩm không hợp lệ.");
                }
            }
            else if (selectedOption == 1)
            {
                // Xử lý "Sửa sản phẩm"
                writeString(x, y, L"[ Chọn sản phẩm cần sửa ]");
                menuTable(x + 25, y - 1, 15, 2);
                Ordertable(x, y + 4, 20);
                for (int i = 0; i < types; i++)
                {
                    gotoXY(x + 5, a + 3);
                    cout << i + 1;
                    gotoXY(x + 20, a + 3);
                    cout << bookCode[i]->getTen_sach();
                    gotoXY(x + 50, a + 3);
                    cout << bookCount[i];
                    gotoXY(x + 70, a + 3);
                    cout << bookCode[i]->getGia_ban();
                    gotoXY(x + 85, a + 3);
                    cout << bookCode[i]->getGia_ban() * bookCount[i];
                    a = a + 2;
                }
                gotoXY(x + 28, y);
                cin >> selectedProduct;
                if (selectedProduct >= 1 && selectedProduct <= types)
                {
                    int newQuantity;
                    writeString(x + 50, y, L"[ Nhập số lượng mới ]");
                    menuTable(x + 80, y - 1, 15, 2);
                    gotoXY(x + 83, y);
                    cin >> newQuantity;
                    if (newQuantity > 0 && newQuantity <= bookCode[selectedProduct - 1]->getSo_luong())
                    {
                        bookCount[selectedProduct - 1] = newQuantity;
                        writeString(x, y, L"Đã sửa số lượng sản phẩm thành công.");
                    }
                    else
                    {
                        writeString(x, y + 2, L"Số lượng không hợp lệ.");
                    }
                }
                else
                {
                    writeString(x, y + 2, L"Mã sản phẩm không hợp lệ.");
                }
            }
            else if (selectedOption == 2)
            {
                // Xử lý "Thêm sản phẩm"
                Add_Product();
            }
            else if (selectedOption == 3)
            {
                // Xử lý "Tiếp tục thanh toán"
                for (int i = 0; i < types; i++)
                {
                    bookCode[i]->SetSo_Luong(bookCode[i]->getSo_luong() - bookCount[i]);
                }
                break; // Thoát khỏi vòng lặp menu để tiếp tục thanh toán
            }
        }
    }
}
void Order::bill()
{
    int x = 20, y = 5;
    int a = 5;
    string billDay, cusCode, newNameCus, newCusAddress, newCusSdt, newCusCode;
    int day, month, year;
    int sum = 0;
    // Input
    writeString(x + 6, y, L"[Nhập thông tin hóa đơn]");
    menuTable(x, y + 1, 45, 25);
    // Input for bill details
    writeString(x + 6, y + 2, L"[ Nhập ngày lập hóa đơn ]");
    menuTable(x + 6, y + 3, 30, 2);
    writeString(x + 6, y + 7, L"[ Nhập tên khách hàng ]");
    menuTable(x + 6, y + 8, 30, 2);
    writeString(x + 6, y + 12, L"[ Nhập địa chỉ khách hàng ]");
    menuTable(x + 6, y + 13, 30, 2);
    writeString(x + 6, y + 17, L"[ Nhập số điện thoại khách hàng ]");
    menuTable(x + 6, y + 18, 30, 2);

    // Validate bill day
    bool validDate = false;
    while (!validDate)
    {
        gotoXY(x + 7, y + 4);
        getline(cin, billDay);

        if (sscanf(billDay.c_str(), "%d/%d/%d", &day, &month, &year) == 3 && chuantime(day, month, year))
        {
            validDate = true;
        }
        else
        {
            gotoXY(x + 7, y + 6);
            trolaisua(x + 7, y + 4, billDay);
        }
    }
    billDay = formatDate(billDay);

    // Validate customer name
    while (true)
    {
        gotoXY(x + 7, y + 9);
        getline(cin, newNameCus);
        if (isAlphaString(newNameCus))
            break;
        else
            trolaisua(x + 7, y + 9, newNameCus);
    }

    // Validate customer address
    while (true)
    {
        gotoXY(x + 7, y + 14);
        getline(cin, newCusAddress);
        if (isAlphaString(newCusAddress))
            break;
        else
            trolaisua(x + 7, y + 14, newCusAddress);
    }

    // Validate customer phone number
    while (true)
    {
        gotoXY(x + 7, y + 19);
        getline(cin, newCusSdt);
        if (isPhoneNumber(newCusSdt))
            break;
        else
            trolaisua(x + 7, y + 19, newCusSdt);
    }

    // Calculate the total sum of the order
    sum = this->Calculator();
    // Generate a new customer code
    CustomerNode *cus = this->customerHead;
    bool customerExists = false;

    // Check if customer already exists
    while (cus != NULL)
    {
        if (cus->data.getSdtKH() == newCusSdt && cus->data.getDia_chi() == newCusAddress && cus->data.getSdtKH() == newCusSdt)
        {
            // Customer exists, add sum to existing customer's amount
            cus->data.setSTDM(cus->data.getSo_tien_da_mua() + sum);
            customerExists = true;
            break;
        }
        cus = cus->next;
    }

    if (!customerExists)
    {
        // Generate a new customer code
        cus = this->customerHead;
        std::string cusCode;
        while (cus != NULL)
        {
            cusCode = cus->data.getMaKH();
            cus = cus->next;
        }

        if (cusCode.length() > 2)
        {
            int numberPart = std::stoi(cusCode.substr(2)) + 1;
            cusCode = "KH" + std::to_string(numberPart).insert(0, 3 - std::to_string(numberPart).length(), '0');
        }
        else
        {
            cusCode = "KH001"; // Default customer code if none exists
        }

        // Create and add a new customer
        Customer newCus(cusCode, newNameCus, newCusAddress, newCusSdt, sum);
        Add_Customer(newCus);
        newCusCode = cusCode;
        std::ifstream infile("customers.txt");
        if (!infile)
        {
            std::cerr << "File could not be opened!" << std::endl;
            return;
        }

        int n;
        infile >> n;
        infile.ignore();
        n += 1;
        std::ofstream outfile("customers.txt", std::ios::in);
        if (!outfile)
        {
            std::cerr << "File could not be opened for writing!" << std::endl;
            return;
        }
        outfile << n << "\n";
        outfile.seekp(0, std::ios::end);
        for (int i = 0; i < types; i++)
        {
            outfile << "\n"
                    << cusCode << "|" << newNameCus << "|" << newCusAddress << "|" << newCusSdt
                    << "|" << sum;
        }
        outfile.close();
        // Read the number of records
    }
    system("cls");
    y = 3;
    writeString(x + 28, y, L"[ HÓA ĐƠN BÁN HÀNG ]");
    writeString(x, y + 2, L"Tên khách hàng:");
    gotoXY(x + 20, y + 2);
    cout << newNameCus;
    writeString(x + 40, y + 2, L"Ngày lập hóa đơn:");
    gotoXY(x + 60, y + 2);
    cout << billDay;
    writeString(x, y + 4, L"Địa chỉ:");
    gotoXY(x + 20, y + 4);
    cout << newCusAddress;
    writeString(x, y + 6, L"Số điện thoại:");
    gotoXY(x + 20, y + 6);
    cout << newCusSdt;

    // Display the order table
    Ordertable(x, y + 8, 18);
    for (int i = 0; i < types; i++)
    {
        gotoXY(x + 5, a + 9);
        cout << i + 1;
        gotoXY(x + 20, a + 9);
        cout << bookCode[i]->getTen_sach();
        gotoXY(x + 50, a + 9);
        cout << bookCount[i];
        gotoXY(x + 70, a + 9);
        cout << bookCode[i]->getGia_ban();
        gotoXY(x + 85, a + 9);
        cout << bookCode[i]->getGia_ban() * bookCount[i];
        a += 2;
    }
    writeString(x + 80, y + 30, L"[ TỔNG TIỀN ]");
    gotoXY(x + 96, y + 30);
    cout << Calculator();
    std::string maHoaDon, ngayLap, makhachhang;
    int soLuong, tongTien;
    std::ifstream infile("bill.txt");
    if (!infile)
    {
        std::cerr << "File could not be opened!" << std::endl;
        return;
    }

    int n;
    infile >> n; // Read the number of records
    infile.ignore();
    // Read the existing records (if necessary)
    for (int i = 1; i <= n; ++i)
    {
        getline(infile, maHoaDon, '|');
        getline(infile, makhachhang, '|');
        getline(infile, ngayLap, '|');
        infile >> soLuong;
        infile.ignore(1);
        infile >> tongTien;
        infile.ignore(1);
    }
    infile.close();
    n += 1;
    int numberPart = std::stoi(maHoaDon.substr(2)) + 1;
    maHoaDon = "HD" + std::string(3 - std::to_string(numberPart).length(), '0') + std::to_string(numberPart);
    std::ofstream outfile("bill.txt", std::ios::in);
    if (!outfile)
    {
        std::cerr << "File could not be opened for writing!" << std::endl;
        return;
    }
    outfile << n << "\n";
    outfile.seekp(0, std::ios::end);
    for (int i = 0; i < types; i++)
    {
        outfile << "\n"
                << maHoaDon << "|" << newCusCode << "|" << billDay << "|" << bookCount[i]
                << "|" << bookCode[i]->getGia_ban() * bookCount[i];
    }
    outfile.close();
    // Wait for Esc to exit
    while (true)
    {
        if (setKeyBoard() == 5) // ASCII code for Esc
        {
            break;
        }
    }
}
long long Order::Calculator()
{
    long long sum = 0;
    for (int i = 0; i < types; i++)
    {
        sum += bookCode[i]->getGia_ban() * bookCount[i];
    }
    return sum;
}
void Order::ProcessOrder()
{
    Add_Product();
    confirm();
    bill();
    for (int i = 0; i < types; ++i)
    {
        if (bookCode[i]->getSo_luong() == 0)
        {
            int position = find_Node_Book(bookCode[i]->getMa_Sach());
            Book *DeleteBook = getNodeBook(position);
            delete_Node_Book(*DeleteBook); // Xóa sách khỏi hệ thống
        }
    }
}