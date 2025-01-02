// Check Valid Date
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#define all(x) x.begin(), x.end()
using namespace std;

// // Hàm kiểm tra ngày hợp lệ
// bool isValidDate(string &s)
// {
//     s.erase(remove(all(s), ' '), s.end());
//     auto valid = [](int day, int month, int year)
//     {
//         if (year < 1 || month < 1 || month > 12)
//             return false;
//         int daysInMonth = 31;
//         if (month == 4 || month == 6 || month == 9 || month == 11)
//             daysInMonth = 30;
//         else if (month == 2)
//             daysInMonth = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 29 : 28;
//         return day >= 1 && day <= daysInMonth;
//     };

//     // Kiểm tra nếu tồn tại kí tự là chữ hoặc kí tự đặc biệt (trừ '/')
//     auto hasSpecialOrAlphabet = [](string &S)
//     {
//         for (char c : S)
//             if (!isdigit(c) && !isspace(c) && c != '/')
//                 return true;
//         return false;
//     };

//     // Tách string thành day-month-year và kiểm tra dữ liệu
//     auto check = [&](string &S) -> bool
//     {
//         if (count(all(S), '/') != 2 || hasSpecialOrAlphabet(S))
//             return false;
//         vector<string> ret;
//         stringstream ss(S);
//         string token;
//         while (getline(ss, token, '/'))
//         {
//             if (token.empty() || !all_of(token.begin(), token.end(), ::isdigit))
//                 return false;
//             ret.push_back(token);
//         }
//         if (ret.size() != 3)
//             return false;
//         return valid(stoi(ret[0]), stoi(ret[1]), stoi(ret[2]));
//     };
//     return (check(s) ? true : false);
// }


double StringToDouble(const string &str){
    try{
        size_t pos; 
        double result = stod(str, &pos); 
        if (pos !=str.length()){
            return nan(""); 
        }
        return result;
    }catch(const invalid_argument& e){
        return nan("");
    }catch(const out_of_range& e){
        return nan(""); 
    }
}

bool laNamNhuan(int nam)
{
    return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
}

// Hàm kiểm tra ngày hợp lệ
bool isValidDate(string &s)
{
    int ngay, thang, nam;
    char separator1, separator2;

    // Sử dụng stringstream để tách chuỗi thành ngày, tháng, năm
    stringstream ss(s);
    ss >> ngay >> separator1 >> thang >> separator2 >> nam;

    // Kiểm tra định dạng đúng với "dd/mm/yyyy"
    if (ss.fail() || separator1 != '/' || separator2 != '/')
        return false;

    // Kiểm tra tháng hợp lệ
    if (thang < 1 || thang > 12)
        return false;
    if (to_string(nam).size() > 4)
        return false;
    // Kiểm tra ngày hợp lệ
    if (nam <= 1900)
        return false;
    // Số ngày tối đa trong từng tháng
    int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Nếu là năm nhuận, tháng 2 có 29 ngày
    if (thang == 2 && laNamNhuan(nam))
        ngayTrongThang[1] = 29;
    string hoangha = "";
    if (ngay < 10)
        hoangha = hoangha + "0" + to_string(ngay);
    else
        hoangha = hoangha + to_string(ngay);
    hoangha = hoangha + "/";
    if (thang < 10)
        hoangha = hoangha + "0" + to_string(thang);
    else
        hoangha = hoangha + to_string(thang);
    hoangha = hoangha + "/";
    hoangha = hoangha + to_string(nam);
    if (ngay > 0 && ngay <= ngayTrongThang[thang - 1])
    {
        s = hoangha;

        return true;
    }
    return false;
}

// change to date
std::tm stringChangeDate(const string &time)
{
    std::tm date;
    string day = time.substr(0, 2);
    string month = time.substr(3, 2);
    string year = time.substr(6, 4);
    date.tm_year = stoi(year) - 1900;
    date.tm_mon = stoi(month) - 1;
    date.tm_mday = stoi(day);
    return date;
}

// change date to string
string dateChangeString(const std::tm &date)
{
    ostringstream oss;

    // định dạng ngày thành DD/MM/YYYY
    oss << (date.tm_mday < 10 ? "0" : "") << date.tm_mday << "/" << (date.tm_mon + 1 < 10 ? "0" : "") << date.tm_mon + 1 << "/" << (date.tm_year + 1900);
    return oss.str();
}

// chuan hoa string
string standardize(string name)
{
    if (name.empty())
        return "";
    stringstream ss(name);
    string tmp;
    string result = "";
    while (ss >> tmp)
    {
        for (int i = 0; i < tmp.size(); i++)
        {
            tmp[i] = tolower(tmp[i]);
        }
        result = result + tmp + " ";
    }
    if (!result.empty())
    {
        result[0] = toupper(result[0]);
        result.erase(result.size() - 1);
    }
    return result;
}

void inputDate(std::tm &date)
{
    string ngay;
    cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): ";
    getline(cin, ngay);
    string day = ngay.substr(0, 2);
    string month = ngay.substr(3, 2);
    string year = ngay.substr(6, 4);
    date.tm_year = stoi(year) - 1900;
    date.tm_mon = stoi(month) - 1;
    date.tm_mday = stoi(day);
}

void printDate(std::tm date)
{
    cout << std::put_time(&date, "%d/%m/%Y");
}

// string formatNumber(const string &input)
// {
//     // Kiểm tra dấu âm
//     bool isNegative = (input[0] == '-');
//     string number = isNegative ? input.substr(1) : input; // Loại bỏ dấu trừ nếu có

//     size_t dotPos = number.find('.');                                           // Vị trí dấu chấm thập phân
//     string integerPart = number.substr(0, dotPos);                              // Phần nguyên
//     string decimalPart = (dotPos != string::npos) ? number.substr(dotPos) : ""; // Phần thập phân (nếu có)

//     // Thêm dấu ',' vào phần nguyên
//     string formattedInteger;
//     int count = 0;
//     for (int i = integerPart.size() - 1; i >= 0; --i)
//     {
//         formattedInteger.push_back(integerPart[i]);
//         count++;
//         if (count == 3 && i > 0)
//         { // Chỉ thêm ',' nếu không phải ký tự đầu tiên
//             formattedInteger.push_back(',');
//             count = 0;
//         }
//     }
//     reverse(formattedInteger.begin(), formattedInteger.end()); // Đảo ngược chuỗi phần nguyên sau khi thêm dấu ','

//     // Ghép phần nguyên với phần thập phân, và thêm lại dấu trừ nếu là số âm
//     return (isNegative ? "-" : "") + formattedInteger + decimalPart;
// }

string formatNumber(const string &input)
{
    // Kiểm tra dấu âm
    bool isNegative = (input[0] == '-');
    string number = isNegative ? input.substr(1) : input; // Loại bỏ dấu trừ nếu có

    size_t dotPos = number.find('.');                                           // Vị trí dấu chấm thập phân
    string integerPart = number.substr(0, dotPos);                              // Phần nguyên
    string decimalPart = (dotPos != string::npos) ? number.substr(dotPos + 1) : ""; // Phần thập phân (nếu có)

    // Loại bỏ các số 0 dư ở cuối phần thập phân
    while (!decimalPart.empty() && decimalPart.back() == '0')
    {
        decimalPart.pop_back();
    }
    // Nếu phần thập phân rỗng sau khi loại bỏ các số 0, không cần giữ lại dấu '.'
    if (!decimalPart.empty())
    {
        decimalPart = "." + decimalPart;
    }

    // Thêm dấu ',' vào phần nguyên
    string formattedInteger;
    int count = 0;
    for (int i = integerPart.size() - 1; i >= 0; --i)
    {
        formattedInteger.push_back(integerPart[i]);
        count++;
        if (count == 3 && i > 0)
        { // Chỉ thêm ',' nếu không phải ký tự đầu tiên
            formattedInteger.push_back(',');
            count = 0;
        }
    }
    reverse(formattedInteger.begin(), formattedInteger.end()); // Đảo ngược chuỗi phần nguyên sau khi thêm dấu ','

    // Ghép phần nguyên với phần thập phân, và thêm lại dấu trừ nếu là số âm
    return (isNegative ? "-" : "") + formattedInteger + decimalPart;
}