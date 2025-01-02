// Login Class

#pragma once

#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <windows.h>
#include <vector>
#include <ctime>
#include <unordered_map>

#include "header.h"
#include "../Manage/ManageUser.h"

using namespace std;

class Login
{
private:
    string username;
    string password;
    unordered_map<string, string> users;
    ManageUser &manageUser;

    void loadUsers();

public:
    // constructor
    // Login();
    Login(ManageUser &userManager);

    
    // hàm login
    bool loginUser();

    // hàm in tiêu đề
    void printTitle();

    // hàm in lời chào
    void printGreeting();

    // hàm hiệu ứng loading
    int loadingAnimation();

    // hàm in thông tin khi đăng xuất
    void exitLogin();

    // getter
    string getUsername() { return username; }

    // getter
    string getPassword() { return password; }
};

Login::Login(ManageUser &userManager) : manageUser(userManager) {
    loadUsers();
}

void Login::loadUsers()
{
    ifstream file("../InputFile/users.txt");
    string line;
    while (getline(file, line))
    {
        size_t pos = line.find(",");
        if (pos != string::npos)
        {
            string fileUsername = line.substr(0, pos);
            string filePassword = line.substr(pos + 1);
            users[fileUsername] = filePassword;
        }
    }
}

void Login::printTitle()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);

    cout << "+=========================================================+\n";
    cout << "|       $$$ ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN $$$        |\n";
    cout << "|  Đồng hành cùng bạn trên hành trình tài chính bền vững  |\n";
    cout << "+=========================================================+\n\n";

    SetConsoleTextAttribute(hConsole, 7);
}

void Login::printGreeting()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int hour = ltm->tm_hour;

    string greetingMsg;
    if (hour >= 0 && hour < 12)
    {
        greetingMsg = " Chào buổi sáng☀️";
    }
    else if (hour >= 12 && hour < 18)
    {
        greetingMsg = " Chào buổi chiều🌤️";
    }
    else
    {
        greetingMsg = " Chào buổi tối🌓";
    }
    cout << greetingMsg << ", và chào mừng bạn đến với ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN!\n\n\n";
}

bool Login::loginUser()
{
    while (true)
    {
        system("cls");
        printTitle();
        cout << "-----------------------------------------------------------\n";
        cout << " Nhập tên người dùng: ";
        getline(cin, username);
        if (username.empty())
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "-----------------------------------------------------------\n";
            cout << "               Vui lòng nhập tên người dùng.\n";
            cout << "-----------------------------------------------------------\n";
            SetConsoleTextAttribute(hConsole, 7);
            pause();
            continue;
        }
        cout << endl;
        cout << " Nhập mật khẩu: ";
        password.clear();
        char ch;
        while ((ch = _getch()) != '\r') // '\r' là phím Enter
        {
            if (ch == '\b') // xử lý phím Backspace
            {
                if (!password.empty())
                {
                    password.pop_back();
                    cout << "\b \b"; // Xóa ký tự cuối cùng hiển thị
                }
            }
            else
            {
                password += ch;
                cout << '*';
            }
        }
        cout << endl;

        if (password.empty())
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 12);
            cout << "-----------------------------------------------------------\n";
            cout << "               Vui lòng nhập mật khẩu.\n";
            cout << "-----------------------------------------------------------\n";
            SetConsoleTextAttribute(hConsole, 7);
            pause();
            continue;
        }

        if (users.find(username) != users.end() && users[username] == password)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            cout << "-----------------------------------------------------------\n";
            cout << "                 Đăng nhập thành công.\n";
            cout << "-----------------------------------------------------------\n";
            SetConsoleTextAttribute(hConsole, 7);
            pause();
            return true;
        }

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-----------------------------------------------------------\n";
        cout << "        Tên người dùng hoặc mật khẩu không hợp lệ.\n";
        cout << "-----------------------------------------------------------\n";
        SetConsoleTextAttribute(hConsole, 7);

        cout << " Nhấn phím bất kì để nhập lại.\n\n";
        cout << " Nhấn ESC để quay lại.\n\n";

        int keyInput = _getch();
        if (keyInput == KEY_ESCAPE)
        {
            return false;
        }
        else if (keyInput != KEY_ESCAPE)
        {
            continue;
        }
        pause();
    }
}

int Login::loadingAnimation()
{
    system("COLOR 0e");
    system("cls");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\t       Loading...";
    cout << "\n\n\n\t       ";

    for (int i = 0; i < 31; i++)
        cout << (char)bar1;

    cout << "\r";
    cout << "\t       ";
    for (int i = 0; i < 31; i++)
    {
        cout << (char)bar2;
        Sleep(150);
    }

    cout << "\n\t       ";
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    pause();
    return 0;
}

void Login::exitLogin()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int exitSelection = 0;
    vector<string> exitChoices = {"Yes😟", "No😀"};

    while (true)
    {
        system("cls");
        printTitle();
        cout << "-----------------------------------------------------------\n";
        cout << " Bạn có chắc chắn là muốn thoát không 🤡🤡🤡?\n\n";
        displayMenu(exitChoices, exitSelection);

        int keyInput = _getch();
        if (keyInput == KEY_UP)
        {
            exitSelection = (exitSelection - 1 + exitChoices.size()) % exitChoices.size();
        }
        else if (keyInput == KEY_DOWN)
        {
            exitSelection = (exitSelection + 1) % exitChoices.size();
        }
        else if (keyInput == KEY_ENTER)
        {
            if (exitSelection == 0)
            {
                system("cls");
                printTitle();
                cout << "---------------------------------------------------------------------\n";
                cout << "Cảm ơn bạn đã sử dụng ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN. Tạm biệt💔!\n";
                cout << "---------------------------------------------------------------------\n";
                manageUser.WriteToFile();
                exit(0);
            }
            else
            {
                system("cls");
                printTitle();
                printGreeting();
                return;
            }
        }
    }
}
