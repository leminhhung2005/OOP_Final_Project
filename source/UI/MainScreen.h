// Class Main Screen

#pragma once

#include <iostream>
#include <vector>

#include "ScreenADT.h"
#include "AccountScreen.h"
#include "LoanScreen.h"
#include "BalanceScreen.h"

using namespace std;

class MainScreen : public Screen
{
private:
    int selection = 0;
    vector<string> menuItems;
    AccountScreen accountScreen;
    LoanScreen loanScreen;
    BalanceScreen balanceScreen;

public:
    MainScreen(ManageUser &userManager);

    void display() override;

    int handleInput(int keyInput) override;
};

MainScreen::MainScreen(ManageUser &userManager) : Screen(userManager), accountScreen(userManager), loanScreen(userManager), balanceScreen(userManager)
{
    menuItems = {"Hiển thị số dư", "Quản lý tài khoản", "Quản lý khoản vay và cho vay", "Thoát ứng dụng"};
    selection = 0;
}

void MainScreen::display()
{
    system("cls");
    login.printTitle();
    std::tm currentDate = getCurrentDate();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\t        Hôm nay là ngày: " << dateChangeString(currentDate) << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "   Chúc bạn một ngày vui 👉👈!" << endl
         << endl;
    cout << "   Chào mừng bạn đến với ỨNG DỤNG QUẢN LÝ TÀI CHÍNH CÁ NHÂN 🤗!" << endl
         << endl;
    // Tài khoản ít tiền hơn 100k thì thông báo
    if (manageUser.getBalance() <= 100000)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "  TÀI KHOẢN CỦA BẠN SẮP HẾT\n\n";
    }
    manageUser.remindDueDate();
    string ans = dateChangeString(currentDate);
    stringstream ss(ans);
    int day;
    ss >> day;
    if (day == 1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\t\t\tMỤC CHI TIÊU\n";
        ;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        manageUser.printReport();
    }
    else if (day == 2)
    {
        manageUser.reset();
    }
    cout << endl;
    displayMenu(menuItems, selection);
}

int MainScreen::handleInput(int keyInput)
{
    switch (keyInput)
    {
    case KEY_UP:
        selection = (selection - 1 + menuItems.size()) % menuItems.size();
        break;
    case KEY_DOWN:
        selection = (selection + 1) % menuItems.size();
        break;
    case KEY_ENTER:
        if (selection == 0)
        {
            balanceScreen.display();
            return SCREEN_SHOWBALANCE;
        }
        else if (selection == 1)
        {
            accountScreen.display();
            return SCREEN_ACCOUNTMANAGE;
        }
        else if (selection == 2)
        {
            loanScreen.display();
            return SCREEN_LOANMANAGE;
        }
        else if (selection == 3)
        {
            login.exitLogin();
        }
        break;
    }
    return SCREEN_LOGIN;
}
