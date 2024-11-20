#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string.h>
#include <windows.h>
#include "HeThong.h"
using namespace std;
inline string getinput()
{
    string name;
    char ch;
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
inline string getNumericInput()
{
    string number;
    char ch;
    while ((ch = _getch()) != '\r')
    { // Đọc cho đến khi nhấn Enter ('\r')
        if (ch == '\b' && number.length() > 0)
        { // Xử lý phím Backspace
            wcout << "\b \b";
            number.pop_back();
        }
        else if (isdigit(ch)) // Kiểm tra nếu ký tự là số
        {
            wcout << ch; // Hiển thị ký tự số
            number.push_back(ch);
        }
    }
    return number;
}
// hàm kiểm tra có phải là số hay không?
inline bool isNumeric(const string &str)
{
    for (char const &c : str)
    {
        if (isdigit(c) == 0)
            return false;
    }
    return true;
}
// hàm kiểm tra có phải là chuỗi hay không?
inline bool isAlphaString(const string &str)
{
    for (char const &c : str)
    {
        if (!isalpha(c) && !isspace(c))
        { // Kiểm tra nếu không phải chữ cái hoặc khoảng trắng
            return false;
        }
    }
    return true;
}
// hàm quay lại sửa
inline void trolaisua(int x, int y, string oldInput)
{
    gotoXY(x, y);
    for (int i = 0; i < oldInput.length(); i++)
    {
        cout << " ";
    }
    gotoXY(x, y);
}
// hàm kiểm tra giá tiền có hợp lệ không?
inline bool isValidPrice(string price)
{
    // Kiểm tra xem chuỗi có phải là số hợp lệ không
    if (price.empty() || !isNumeric(price))
    {
        return false; // Chuỗi rỗng hoặc không phải số
    }

    int value = stoi(price); // Chuyển chuỗi sang số nguyên

    // Kiểm tra nếu giá phải lớn hơn 1000
    if (value < 1000)
    {
        return false; // Giá quá nhỏ
    }

    return true; // Giá hợp lệ
}
// Hàm lấy năm hiện tại
inline int getCurrentYear()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year; // Trả về năm hiện tại
}
// Hàm kiểm tra năm có đúng hay không
inline bool isValidYear(string year)
{
    // Kiểm tra xem chuỗi có phải là số hợp lệ không
    if (year.empty() || !isNumeric(year))
    {
        return false; // Chuỗi rỗng hoặc không phải là số
    }

    // Kiểm tra nếu năm có đúng 4 chữ số
    if (year.length() != 4)
    {
        return false; // Không đủ hoặc thừa số chữ số cho năm
    }

    int value = stoi(year); // Chuyển chuỗi sang số nguyên

    // Kiểm tra nếu năm nằm trong khoảng hợp lý (ví dụ: từ 1900 đến năm hiện tại)
    if (value < 1900 || value > getCurrentYear())
    {
        return false; // Năm quá nhỏ hoặc lớn hơn năm hiện tại
    }

    return true; // Năm hợp lệ
}
// hàm kiểm tra tháng có đúng hay không
inline bool isValidMonth(const std::string &month)
{
    // Kiểm tra xem chuỗi có phải là số hợp lệ không
    if (month.empty() || !isNumeric(month))
    {
        return false; // Chuỗi rỗng hoặc không phải là số
    }

    // Kiểm tra nếu tháng có nhiều nhất 2 chữ số
    if (month.length() > 2)
    {
        return false; // Thừa số chữ số cho tháng
    }

    int value = std::stoi(month); // Chuyển chuỗi sang số nguyên

    // Kiểm tra nếu tháng nằm trong khoảng hợp lệ (1 đến 12)
    if (value < 1 || value > 12)
    {
        return false; // Tháng không nằm trong khoảng hợp lệ
    }

    return true; // Tháng hợp lệ
}
//
inline bool isValidDate(const std::string &day, const std::string &month)
{
    if (day.empty() || month.empty() || !isNumeric(day) || !isNumeric(month))
    {
        return false;
    }
    int dayValue = std::stoi(day);
    int monthValue = std::stoi(month);
    if (monthValue < 1 || monthValue > 12)
    {
        return false;
    }
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (dayValue < 1 || dayValue > daysInMonth[monthValue])
    {
        return false;
    }
    return true;
}
// hàm kiểm tra số lượng có đúng hay không
inline bool isValidQuantity(string quantity)
{
    // Kiểm tra xem chuỗi có phải là số hợp lệ không
    if (quantity.empty() || !isNumeric(quantity))
    {
        return false; // Chuỗi rỗng hoặc không phải là số
    }

    int value = stoi(quantity); // Chuyển chuỗi sang số nguyên

    // Kiểm tra nếu số lượng là số nguyên dương và nằm trong khoảng hợp lý
    if (value <= 0 || value > 999)
    {
        return false; // Số lượng không hợp lệ (nhỏ hơn hoặc bằng 0 hoặc quá lớn)
    }

    return true;
}
// hàm kiểm tra có đúng định dạng ngày hay không
inline string formatDate(string rawDate)
{
    // Assuming rawDate is input as DD/MM/YYYY
    stringstream dateStream(rawDate);
    string day, month, year;

    getline(dateStream, day, '/');   // Get day
    getline(dateStream, month, '/'); // Get month
    getline(dateStream, year);       // Get year

    // Return in YYYY-MM-DD format
    return year + "-" + month + "-" + day;
}
// hàm kiểm tra số điện thoại có đủ 8 chữ số hay không
inline bool isPhoneNumber(const string &str)
{
    // Check if the string is empty or contains invalid characters
    if (str.empty() || str.length() != 10) // Check if the string length is not 8
        return false;

    for (char const &c : str)
    {
        if (!isdigit(c))
        { // Check if the character is not a digit
            return false;
        }
    }
    return true;
}
// xem thử thời gian có đúng hay không
inline int chuantime(int ngay, int thang, int nam)
{
    int ngaymax;
    if (nam < 1900 || nam > 2222 || thang < 1 || thang > 12 || ngay < 1 || ngay > 31)
    {
        return 0;
    }
    else
    {
        switch (thang)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ngaymax = 31;
            break;
        case 2:
            if (nam % 4 == 0)
                ngaymax = 29;
            else
                ngaymax = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            ngaymax = 30;
            break;
        }
        if (ngay <= ngaymax)
            return 1;
        else
            return 0;
    }
}