// Class User Interface

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <functional>
#include <memory>

#include "LoginScreen.h"
#include "MainScreen.h"
#include "AccountScreen.h"
#include "LoanScreen.h"
#include "BalanceScreen.h"

#include "../Manage/ManageUser.h"

class UI
{
private:
    HANDLE hConsole;
    bool exitProgram;
    int selection;
    int keyInput;
    int currentScreen;

    Login login;


    void setTextColor(int color);

    ManageUser manageUser;

public:
    UI();

    // ~UI();

    void process();
};

UI::UI() : exitProgram(false), selection(0), keyInput(0), currentScreen(SCREEN_LOGIN),login(manageUser)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // manageUser = new ManageUser();
    manageUser.loadFromFile("../InputFile/inputUser.txt");
}

// UI::~UI(){
//     manageUser.WriteToFile();
// }

void UI::setTextColor(int color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void UI::process()
{
    // learn here https://www.geeksforgeeks.org/unique_ptr-in-cpp/
    unique_ptr<Screen> screen = make_unique<LoginScreen>(manageUser);

    while (!exitProgram)
    {
        screen->display();
        keyInput = _getch();

        int nextScreen = screen->handleInput(keyInput);
        if (nextScreen != currentScreen)
        {
            currentScreen = nextScreen;

            switch (currentScreen)
            {
            case SCREEN_MAIN:
                screen = make_unique<MainScreen>(manageUser);
                break;
            case SCREEN_SHOWBALANCE:
                screen = make_unique<BalanceScreen>(manageUser);
                break;
            case SCREEN_ACCOUNTMANAGE:
                screen = make_unique<AccountScreen>(manageUser);
                break;
            case SCREEN_LOANMANAGE:
                screen = make_unique<LoanScreen>(manageUser);
                break;
            default:
                break;
            }
        }
        keyInput = 0; // reset keyInput
    }
}