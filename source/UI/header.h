#pragma once

#include <conio.h>
#include <iostream>

using namespace std;

// color
#define MAIN_COLOR 11
#define SECONDARY_COLOR 224
#define COLOR_WHITE 15
#define COLOR_GREY 7
#define COLOR_YELLOW 14

// control
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_BACKSPACE 8
#define KEY_ESCAPE 27
#define KEY_ENTER 13

// screen
#define SCREEN_LOGIN 0
#define SCREEN_MAIN 1
#define SCREEN_SHOWBALANCE 2
#define SCREEN_ACCOUNTMANAGE 3
#define SCREEN_LOANMANAGE 4

// pause function
// ở trước các hàm này có thể sử dụng inline nhưng dev c cảnh báo nên bỏ, thêm vào sẽ tối ưu time chạy
// learn inline here https://www.youtube.com/watch?v=clHYkvjYOAU
void pause()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
    cout << "\nNhấn phím bất kì để tiếp tục . . . 😜😜😜" << endl;
    _getch();
}

// lamda function for display menu
auto displayMenu = [](const vector<string> &menuItems, int selection)
{
    if (selection < 0 || selection >= menuItems.size())
    {
        cout << "Chỉ số lựa chọn không hợp lệ!" << endl;
        pause();
        return;
    }

    for (int i = 0; i < menuItems.size(); i++)
    {
        if (i == selection)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), SECONDARY_COLOR);
            cout << " -> " << menuItems[i] << " " << endl
                 << endl;
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
            cout << "    " << menuItems[i] << " " << endl
                 << endl;
        }
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_WHITE);
    cout << "\nSử dụng phím mũi tên 👆 và 👇 để điều hướng.\n\n";
    cout << "Nhấn ENTER để chọn 😱😱😱\n\n";
};

int getCurrentLine()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    if (GetConsoleScreenBufferInfo(hConsole, &consoleInfo))
    {
        return consoleInfo.dwCursorPosition.Y; // Lấy dòng hiện tại
    }
    return 0; // Mặc định trả về 0 nếu không lấy được
}

// Xóa một vùng trên console
void clearLines(int startLine, int numLines)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    for (int i = 0; i < numLines; ++i)
    {
        COORD cursorPosition = {0, (SHORT)(startLine + 2 * i)};
        SetConsoleCursorPosition(hConsole, cursorPosition);
        DWORD charsWritten;
        FillConsoleOutputCharacter(hConsole, ' ', consoleInfo.dwSize.X, cursorPosition, &charsWritten);
    }

    // Đặt lại con trỏ về vị trí bắt đầu
    SetConsoleCursorPosition(hConsole, {0, (SHORT)startLine});
}

// Dùng xóa trong thêm lend, borrow
void clearLines2(int startLine, int numLines)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);

    for (int i = 0; i < numLines; ++i)
    {
        COORD cursorPosition = {0, (SHORT)(startLine + i)};
        SetConsoleCursorPosition(hConsole, cursorPosition);
        DWORD charsWritten;
        FillConsoleOutputCharacter(hConsole, ' ', consoleInfo.dwSize.X, cursorPosition, &charsWritten);
        FillConsoleOutputAttribute(hConsole, consoleInfo.wAttributes, consoleInfo.dwSize.X, cursorPosition, &charsWritten);
    }

    SetConsoleCursorPosition(hConsole, {0, (SHORT)startLine});
}

// Hiển thị menu tại vị trí chỉ định
void displayMenu2(const vector<string> &items, int choice, int startLine)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < items.size(); ++i)
    {
        COORD cursorPosition = {0, (SHORT)(startLine + 2 * i)}; // Tăng khoảng cách mỗi mục
        SetConsoleCursorPosition(hConsole, cursorPosition);

        if (i == choice)
        {
            SetConsoleTextAttribute(hConsole, SECONDARY_COLOR);
            cout << " -> " << items[i] << "   ";
        }
        else
        {
            SetConsoleTextAttribute(hConsole, COLOR_WHITE);
            cout << "    " << items[i] << "    ";
        }
    }

    SetConsoleTextAttribute(hConsole, 7);
}

// confirm update
bool confirmUpdate()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\n------- Bạn có chắc chắn muốn cập nhật khoản cho vay? -------" << endl
         << endl;

    vector<string> optionItems = {"Chắc chắn", "Không"};
    int option = 0;
    bool flag = false;

    int startLine = getCurrentLine();
    while (!flag)
    {
        clearLines(startLine, optionItems.size());
        displayMenu2(optionItems, option, startLine);
        int key_choice = _getch();
        switch (key_choice)
        {
        case KEY_UP:
            option = (option - 1 + optionItems.size()) % optionItems.size();
            break;
        case KEY_DOWN:
            option = (option + 1) % optionItems.size();
            break;
        case KEY_ENTER:
            flag = true;
            return option == 0;
        }
    }
    return false;
}

// print title
void printTitle()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14);
    cout << "+=========================================================+\n";
    cout << "|       $$$ ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN $$$        |\n";
    cout << "|  Đồng hành cùng bạn trên hành trình tài chính bền vững  |\n";
    cout << "+=========================================================+\n\n";
    SetConsoleTextAttribute(hConsole, 7);
}

// ràng buộc điều kiện số
auto getAmount = [](string sotien, double &amount)
{
    char ch;
    bool hasDecimalPoint = false;
    bool isNegative = false;

    while ((ch = _getch()) != '\r' || sotien.empty()) // '\r' là phím Enter
    {
        if (ch == '\b') // xử lý phím Backspace
        {
            if (!sotien.empty())
            {
                if (sotien.back() == '.')
                {
                    hasDecimalPoint = false;
                }
                sotien.pop_back();
                cout << "\b \b";
            }
        }
        else if (isdigit(ch))
        {
            sotien += ch;
            cout << ch;
        }
        else if (ch == '.' && !hasDecimalPoint)
        {
            sotien += ch;
            cout << ch;
            hasDecimalPoint = true;
        }
        else if (ch == '-' && sotien.empty()) // dấu - ở đầu
        {
            sotien += ch;
            cout << ch;
            isNegative = true;
        }
    }
    amount=stod(sotien);
};