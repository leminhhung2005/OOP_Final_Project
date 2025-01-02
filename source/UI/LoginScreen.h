// Class Login Screen

#pragma once

#include <iostream>
#include <vector>

#include "ScreenADT.h"

using namespace std;

class LoginScreen : public Screen
{
private:
    int selection;
    vector<string> menuItems;

public:
    LoginScreen(ManageUser &userManager);

    void display() override;

    int handleInput(int keyInput) override;
};

LoginScreen::LoginScreen(ManageUser &userManager) : Screen(userManager)
{
    menuItems = {"Đăng Nhập", "Thoát ứng dụng"};
    selection = 0;
}

void LoginScreen::display()
{
    system("cls");
    login.printTitle();
    login.printGreeting();
    displayMenu(menuItems, selection);
}

int LoginScreen::handleInput(int keyInput)
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
            system("cls");
            login.printTitle();
            login.printGreeting();
            if (login.loginUser())
            {
                login.loadingAnimation();
                return SCREEN_MAIN;
            }
        }
        else if (selection == 1)
        {
            login.exitLogin();
        }
        break;
    }
    return SCREEN_LOGIN;
}