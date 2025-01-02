#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Users.h"
#include "HeThong.h"
#include <algorithm> // For std::remove_if
#include <limits>
#include <fcntl.h>
#include <io.h>
#include <windows.h>
using namespace std;
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include "condition.h"
using namespace std;

wstring Users::getPassword(int x, int y)
{
    wstring password;
    char ch;
    bool showPassword = false;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Thiết lập màu chữ trắng trên nền xám (0x70: nền xám, chữ trắng)
    SetConsoleTextAttribute(consoleHandle, 0x70);
    while ((ch = _getch()) != '\r')
    {
        if (ch == '\b' && !password.empty())
        {
            wcout << "\b \b";
            password.pop_back();
        }
        else if (ch == '\t')
        {

            showPassword = !showPassword;

            wcout << "\r                          \r";
            if (showPassword)
            {
                gotoXY(x, y);
                wcout << password;
            }
            else
            {
                gotoXY(x, y);
                wcout << wstring(password.length(), '*');
            }
        }
        else if (ch != '\b')
        {

            password.push_back(ch);
            if (showPassword)
                wcout << ch;
            else
                wcout << '*';
        }
    }

    return password;
}
wstring Users::getName()
{
    wstring name;
    char ch;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // Thiết lập màu chữ trắng trên nền xám (0x70: nền xám, chữ trắng)
    SetConsoleTextAttribute(consoleHandle, 0x70);
    while ((ch = _getch()) != '\r')
    { // Đọc cho đến khi nhấn Enter ('\r')
        if (ch == '\b' && name.length() > 0)
        { // Xử lý phím Backspace
            wcout << "\b \b";
            name.pop_back();
        }
        else if (ch != '\b')
        {                // Nếu không phải Backspace, thêm vào mật khẩu
            wcout << ch; // Hiển thị * thay vì ký tự thực
            name.push_back(ch);
        }
    }
    return name;
}
bool Users::login()
{
    int role;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD savedAttributes;
    GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
    savedAttributes = consoleInfo.wAttributes;
    display_login();

    while (true)
    {
        int x = 0, y = 0;
        setClick(x, y);
        // cout << x << y;
        // system("pause");
        // Check if the "forgot password" button is clicked
        if (x >= 59 && x <= 75 && y == 23)
        {
            forgot_password(); // Call forgot password and return to login
            display_login();
            continue; // Continue login loop after password recovery
        }
        // 47 --> 55
        else if (x >= 47 && x <= 55 && y == 23)
        {
            register_account(); // Call forgot password and return to login
            display_login();
            continue; // Continue login loop after password recovery
        }
        wstring username, password;

        // Get username
        while (true)
        {
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 10 && y <= 13)
            {
                gotoXY(46, 11); // Assuming gotoXY is defined elsewhere
                username = getName();
                break;
            }
            if (x >= 59 && x <= 75 && y == 23)
            {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
            if (x >= 47 && x <= 55 && y == 23)
            {
                register_account(); // Call forgot password and return to login
                display_login();
                continue; // Continue login loop after password recovery
            }
        }
        while (true)
        {
            writeString(46, 11, username, 0x70);
            setClick(x, y);
            if (x >= 45 && x <= 75 && y >= 15 && y <= 18)
            {
                gotoXY(46, 16);
                password = getPassword(46, 16);
                break;
            }
            if (x >= 59 && x <= 75 && y == 23)
            {
                forgot_password(); // Call forgot password and return to login
                display_login();
                continue;
            }
            else if (x >= 47 && x <= 55 && y == 23)
            {

                register_account(); // Call forgot password and return to login
                display_login();
                return login();
            }
        }
        // Validate login credentials
        wfstream infile("dangnhap.txt", ios_base::in);
        if (!infile.is_open())
        {
            menuTable(53, 10, 66, 4); // Assuming menuTable is defined elsewhere
            writeString(57, 12, L"Khong the mo tap tin", 0x70);
            if (_getch())
                system("cls");
            return false;
        }

        int n, tempRole, i = 1;
        infile >> n;
        infile.ignore();

        bool loginSuccess = false;
        while (i <= n)
        {
            wstring fileUsername, filePassword;
            int fileRole;
            infile >> fileUsername >> filePassword >> fileRole;

            if (username == fileUsername && password == filePassword)
            {
                role = fileRole;
                loginSuccess = true;
                break;
            }
            i++;
        }
        infile.close();

        if (!loginSuccess)
        {
            SetConsoleTextAttribute(consoleHandle, 0x74);
            writeChar(55, 3, L"THONG TIN DANG NHAP KHONG CHINH XAC!!");
            SetConsoleTextAttribute(consoleHandle, savedAttributes);
            display_login(); // Re-display the login screen for another attempt
        }
        else
        {
            break; // Successful login
        }
    }
    return role;
}
void Users::setRole(int role)
{
    this->role = role;
}
void Users::forgot_password()
{
    system("cls");
    setTextColor(11);
    _setmode(_fileno(stdout), _O_U16TEXT);
    SetConsoleBackgroundToGray();
    display_forgetPassword();
    wstring username_input;
    bool username_found = false;
    int index;
    // Lấy dữ liệu từ file
    vector<wstring> usernames, passwords;
    vector<int> roles;
    wstring line;

    // Mở file và tải dữ liệu
    wifstream infile("dangnhap.txt");
    infile.imbue(locale(""));

    if (!infile)
    {
        writeString(46, 13, L"KHÔNG THỂ MỞ TỆP TIN!", 0x70);
        _getch();
        return;
    }

    while (getline(infile, line))
    {
        wistringstream iss(line);
        wstring username, password;
        int role;
        if (iss >> username >> password >> role)
        {
            usernames.push_back(username);
            passwords.push_back(password);
            roles.push_back(role);
        }
    }
    infile.close();

    // Vòng lặp để nhập tài khoản
    do
    {
        // Nhập tên đăng nhập
        gotoXY(46, 11);
        getline(wcin, username_input);

        // Kiểm tra tài khoản
        auto it = find(usernames.begin(), usernames.end(), username_input);
        if (it == usernames.end())
        {
            writeString(47, 13, L"[ Tài khoản không tồn tại ]", 0x74);
        }
        else
        {
            username_found = true;
            index = distance(usernames.begin(), it);
            writeString(47, 13, L"[Tài khoản hợp lệ!]", 0x72);
        }

    } while (!username_found);
    wstring new_password;
    gotoXY(46, 16);
    new_password = getPassword(46, 16);
    while (!isPasswordValid(new_password))
    {
        writeString(46, 18, L"[ Mật khẩu không hợp lệ ]", 0x74);
        gotoXY(46, 16);
        wcout << wstring(15, L' ');
        gotoXY(46, 16);
        new_password = getPassword(46, 16);
    }
    // Password input again
    gotoXY(46, 21);
    wstring new_password_again;
    new_password_again = getPassword(46, 21);
    while (new_password != new_password_again)
    {
        writeString(46, 23, L"[ Mật khẩu không trùng khớp ]", 0x74);
        gotoXY(46, 21);
        wcout << wstring(15, L' ');
        gotoXY(46, 21);
        new_password_again = getPassword(46, 21);
    }
    passwords[index] = new_password;
    // Ghi lại file
    wofstream outfile("dangnhap.txt");
    outfile.imbue(locale(""));

    // Ghi số lượng tài khoản
    outfile << usernames.size() << L"\n";

    // Ghi dữ liệu từng tài khoản
    for (size_t i = 0; i < usernames.size(); ++i)
    {
        outfile << usernames[i] << L" " << passwords[i] << L" " << roles[i] << L"\n";
    }
    outfile.close();

    if (MessageBoxW(NULL, L"Cập nhật mật khẩu thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION) == IDOK)
    {
        return; // Exit the function when "OK" is clicked
    }
}

void Users::register_account()
{

    system("cls");
    setTextColor(11);
    _setmode(_fileno(stdout), _O_U16TEXT); // Enable Unicode output

    // Check for account count in file
    // Display title
    SetConsoleBackgroundToGray();
    display_register();
    // Validate and input username
    wstring username_input;
    bool valid_username = false;
    while (!valid_username)
    {
        gotoXY(46, 11);
        wcout << wstring(15, L' ');
        gotoXY(46, 11);
        getline(wcin, username_input);

        // Remove extra whitespace
        username_input.erase(remove_if(username_input.begin(), username_input.end(), iswspace), username_input.end());

        if (username_input.empty())
        {
            writeString(44, 13, L"[ TÊN ĐĂNG NHẬP KHÔNG ĐƯỢC ĐỂ TRỐNG ]", 0x70);
            continue;
        }

        // Check if username already exists
        wifstream infile("dangnhap.txt");
        if (!infile.is_open())
        {
            writeString(50, 24, L"KHÔNG THỂ MỞ TỆP TIN ĐỂ KIỂM TRA.", 0x70);
            return;
        }

        wstring file_line;
        bool account_exists = false;
        while (getline(infile, file_line))
        {
            wstring file_username, file_password;
            int file_role;
            wstringstream ss(file_line);
            ss >> file_username >> file_password >> file_role;

            // Trim spaces in file_username
            file_username.erase(remove_if(file_username.begin(), file_username.end(), iswspace), file_username.end());

            if (username_input == file_username)
            {
                account_exists = true;
                break;
            }
        }
        infile.close();

        if (account_exists)
        {
            writeString(46, 13, L"[ Tên đăng nhập đã tồn tại ]", 0x74);
        }
        else
        {
            valid_username = true;
        }
    }

    // Password input
    gotoXY(46, 16);
    wstring password_input;
    password_input = getPassword(46, 16);
    int Role = 0;
    while (!isPasswordValid(password_input))
    {
        writeString(46, 18, L"[ Mật khẩu không hợp lệ ]", 0x74);
        gotoXY(46, 16);
        wcout << wstring(15, L' ');
        gotoXY(46, 16);
        password_input = getPassword(46, 16);
    }
    // Password input again
    gotoXY(46, 21);
    wstring password_input_again;
    password_input_again = getPassword(46, 21);
    while (password_input != password_input_again)
    {
        writeString(46, 23, L"[ Mật khẩu không trùng khớp ]", 0x74);
        gotoXY(46, 21);
        wcout << wstring(15, L' ');
        gotoXY(46, 21);
        password_input_again = getPassword(46, 21);
    }
    wofstream account_file("dangnhap.txt", ios::app);
    if (!account_file.is_open())
    {
        writeString(50, 24, L"KHÔNG THỂ MỞ TỆP TIN ĐỂ LƯU THÔNG TIN.", 0x70);
        return;
    }
    account_file << username_input << L" " << password_input << L" " << Role << L"\n";
    account_file.close();
    int n = 0;
    wifstream infile("dangnhap.txt");
    if (!infile)
    {
        wcerr << L"Không thể mở tệp tin dangnhap.txt!" << endl;
        return;
    }
    infile >> n;
    infile.ignore();
    n += 1;
    std::ofstream outfile("dangnhap.txt", std::ios::in);
    // Update account count in file
    if (!outfile)
    {
        std::cerr << "File could not be opened for writing!" << std::endl;
        return;
    }
    outfile << n;
    outfile.seekp(0, std::ios::end);
    outfile.close();
    // Success message
    MessageBoxW(NULL, L"Bạn đã đăng ký tài khoản thành công!", L"Thông báo", MB_OK | MB_ICONINFORMATION);
}
