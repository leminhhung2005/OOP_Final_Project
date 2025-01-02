// Class Loan Screen

#pragma once

#include <iostream>
#include <vector>

#include "ScreenADT.h"
#include "../Manage/LoanManager.h"

using namespace std;

class LoanScreen : public Screen
{
private:
    int selection = 0;
    vector<string> menuItems;

public:
    LoanScreen(ManageUser &userManager);

    void display() override;

    int handleInput(int keyInput) override;
};

LoanScreen::LoanScreen(ManageUser &userManager) : Screen(userManager)
{
    menuItems = {"Báo cáo khoản vay và cho vay", "Thêm khoản vay hoặc cho vay", "Xóa khoản vay hoặc cho vay", "Cập nhật khoản vay hoặc cho vay", "Thanh toán khoản vay hoặc cho vay", "Tra cứu khoản vay và cho vay", "Quay lại trang trước"};
    selection = 0;
}

void LoanScreen::display()
{
    system("cls");
    login.printTitle();
    displayMenu(menuItems, selection);
}

int LoanScreen::handleInput(int keyInput)
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
    {
        // XỬ LÝ BÁO CÁO KHOẢN VAY VÀ CHO VAY
        if (selection == 0)
        {
            system("cls");
            login.printTitle();
            vector<string> choiceItems = {"Báo cáo tổng thể", "Báo cáo chi tiết", "Quay lại trang trước"};
            int choice = 0;
            while (true)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                    if (choice == 0)
                    {
                        system("cls");
                        login.printTitle();
                        manageUser.generateReport();
                        pause();
                    }
                    else if (choice == 1)
                    {
                        system("cls");
                        login.printTitle();
                        manageUser.generateReportAll();
                        pause();
                    }
                    else if (choice == 2)
                    {
                        return SCREEN_LOANMANAGE;
                    }
                    break;
                }
            }
            break;
        }
        // XỬ LÝ THÊM KHOẢN VAY HOẶC CHO VAY
        else if (selection == 1)
        {
            system("cls");
            login.printTitle();
            vector<string> choiceItems = {"Thêm khoản cho vay", "Thêm khoản vay", "Quay lại trang trước"};
            int choice = 0;

            while (true)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                {
                    // XỬ LÝ THÊM KHOẢN CHO VAY
                    if (choice == 0)
                    {
                        system("cls");
                        login.printTitle();
                        manageUser.addLoan(true);
                    }
                    // XỬ LÝ THÊM KHOẢN VAY
                    else if (choice == 1)
                    {
                        system("cls");
                        login.printTitle();
                        manageUser.addLoan(false);
                    }
                    // XỬ LÝ QUAY LẠI MÀN HÌNH
                    else if (choice == 2)
                    {
                        return SCREEN_LOANMANAGE;
                    }
                }
                }
            }
        }
        // XỬ LÝ XÓA KHOẢN VAY VÀ CHO VAY
        else if (selection == 2)
        {
            system("cls");
            login.printTitle();
            vector<string> choiceItems = {"Xóa khoản cho vay", "Xóa khoản vay ", "Quay lại trang trước"};
            int choice = 0;
            while (true)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                {
                    // XỬ LÝ XÓA KHOẢN CHO VAY
                    if (choice == 0)
                    {
                        int choice1 = 0;
                        bool exit = false;
                        while (!exit)
                        {
                            system("cls");
                            login.printTitle();
                            vector<string> lendloanItems = this->manageUser.getLends();
                            if (lendloanItems.size() == 0)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                cout << "-------------------------------------------------------------------\n";
                                cout << "           Chưa có khoản cho vay! Vui lòng thêm khoản cho vay\n";
                                cout << "-------------------------------------------------------------------\n";
                                pause();
                                return SCREEN_LOANMANAGE;
                            }

                            lendloanItems.push_back("Quay lại trang trước");

                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                            cout << "------------- Chọn khoản cho vay bạn muốn xóa -------------\n\n";
                            choice1 = choice1 % lendloanItems.size();
                            displayMenu(lendloanItems, choice1);
                            keyInput = _getch();
                            switch (keyInput)
                            {
                            case KEY_UP:
                                choice1 = (choice1 - 1 + lendloanItems.size()) % lendloanItems.size();
                                break;
                            case KEY_DOWN:
                                choice1 = (choice1 + 1) % lendloanItems.size();
                                break;
                            case KEY_ENTER:
                                if (choice1 == lendloanItems.size() - 1)
                                {
                                    exit = true;
                                    break;
                                }
                                else
                                {
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "--------- Bạn có chắc chắn muốn xoá khoản cho vay ? ---------" << endl
                                         << endl;
                                    vector<string> optionItems = {"Chắc chắn", "Không"};
                                    int option = 0;
                                    int keyInput;
                                    int startLine = getCurrentLine();
                                    bool flag = false;
                                    while (!flag)
                                    {
                                        clearLines(startLine, optionItems.size());

                                        displayMenu2(optionItems, option, startLine);

                                        keyInput = _getch();
                                        switch (keyInput)
                                        {
                                        case KEY_UP:
                                            option = (option - 1 + optionItems.size()) % optionItems.size();
                                            break;
                                        case KEY_DOWN:
                                            option = (option + 1) % optionItems.size();
                                            break;
                                        case KEY_ENTER:
                                        {
                                            if (option == 0)
                                            {
                                                cout << endl
                                                     << endl;
                                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                                cout << "-----------------------------------------------------------\n";
                                                cout << "               Xóa khoản cho vay thành công.\n";
                                                cout << "-----------------------------------------------------------\n";
                                                manageUser.deleteLoan(true, choice1);
                                                pause();
                                            }
                                            else if (option == 1)
                                            {
                                                cout << endl
                                                     << endl;
                                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                                cout << "-----------------------------------------------------------\n";
                                                cout << "           Xóa khoản cho vay không thành công.\n";
                                                cout << "-----------------------------------------------------------\n";
                                                pause();
                                            }
                                            flag = true;
                                            break;
                                        }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    // XỬ LÝ XÓA KHOẢN VAY
                    else if (choice == 1)
                    {
                        int choice1 = 0;
                        bool exit = false;
                        while (!exit)
                        {
                            system("cls");
                            vector<string> borrowloanItems = this->manageUser.getBorrows();
                            if (borrowloanItems.size() == 0)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                cout << "-------------------------------------------------------------------\n";
                                cout << "           Chưa có khoản vay! Vui lòng thêm khoản vay\n";
                                cout << "-------------------------------------------------------------------\n";
                                pause();
                                return SCREEN_LOANMANAGE;
                            }
                            borrowloanItems.push_back("Quay lại trang trước");

                            login.printTitle();
                            cout << "--------------- Chọn khoản vay bạn muốn xóa ---------------\n\n";
                            choice1 = choice1 % borrowloanItems.size();
                            displayMenu(borrowloanItems, choice1);
                            int key_input = _getch();
                            switch (key_input)
                            {
                            case KEY_UP:
                                choice1 = (choice1 - 1 + borrowloanItems.size()) % borrowloanItems.size();
                                break;
                            case KEY_DOWN:
                                choice1 = (choice1 + 1) % borrowloanItems.size();
                                break;
                            case KEY_ENTER:
                                if (choice1 == borrowloanItems.size() - 1)
                                {
                                    exit = true;
                                    break;
                                }
                                else
                                {
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "--------- Bạn có chắc chắn muốn xoá khoản vay ? ---------" << endl
                                         << endl;
                                    vector<string> optionItems = {"Chắc chắn", "Không"};
                                    int option = 0;
                                    int key_choice;
                                    int startLine = getCurrentLine();
                                    bool flag = false;
                                    while (!flag)
                                    {
                                        clearLines(startLine, optionItems.size());

                                        displayMenu2(optionItems, option, startLine);

                                        key_choice = _getch();
                                        switch (key_choice)
                                        {
                                        case KEY_UP:
                                            option = (option - 1 + optionItems.size()) % optionItems.size();
                                            break;
                                        case KEY_DOWN:
                                            option = (option + 1) % optionItems.size();
                                            break;
                                        case KEY_ENTER:
                                        {
                                            if (option == 0)
                                            {
                                                cout << endl
                                                     << endl;
                                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                                cout << "-----------------------------------------------------------\n";
                                                cout << "                 Xóa khoản vay thành công.\n";
                                                cout << "-----------------------------------------------------------\n";
                                                manageUser.deleteLoan(false, choice1);
                                                pause();
                                            }
                                            else if (option == 1)
                                            {
                                                cout << endl
                                                     << endl;
                                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                                cout << "-----------------------------------------------------------\n";
                                                cout << "             Xóa khoản vay không thành công.\n";
                                                cout << "-----------------------------------------------------------\n";
                                                pause();
                                            }
                                            flag = true;
                                            break;
                                        }
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                    // XỬ LÝ QUAY LẠI MÀN HÌNH
                    else if (choice == 2)
                    {
                        return SCREEN_LOANMANAGE;
                    }
                }
                }
            }
            break;
        }
        // XỬ LÝ CẬP NHẬT KHOẢN VAY VÀ CHO VAY
        else if (selection == 3)
        {
            vector<string> choiceItems = {"Cập nhật khoản cho vay", "Cập nhật khoản vay", "Quay lại trang trước"};
            int choice = 0;
            while (true)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                {
                    // XỬ LÝ CẬP NHẬT KHOẢN CHO VAY
                    if (choice == 0)
                    {
                        int choice1 = 0;
                        bool exit = false;
                        while (!exit)
                        {
                            system("cls");
                            login.printTitle();
                            vector<string> lendloanItems = this->manageUser.getLends();
                            if (lendloanItems.size() == 0)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                cout << "-------------------------------------------------------------------\n";
                                cout << "        Chưa có khoản cho vay! Vui lòng thêm khoản cho vay\n";
                                cout << "-------------------------------------------------------------------\n";
                                pause();
                                return SCREEN_LOANMANAGE;
                            }
                            lendloanItems.push_back("Quay lại trang trước");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                            cout << "---------- Chọn khoản cho vay bạn muốn cập nhật -----------\n\n";
                            choice1 = (choice1 + lendloanItems.size()) % lendloanItems.size();

                            displayMenu(lendloanItems, choice1);

                            keyInput = _getch();
                            switch (keyInput)
                            {
                            case KEY_UP:
                                choice1 = (choice1 - 1 + lendloanItems.size()) % lendloanItems.size();
                                break;
                            case KEY_DOWN:
                                choice1 = (choice1 + 1) % lendloanItems.size();
                                break;
                            case KEY_ENTER:
                                if (choice1 == lendloanItems.size() - 1)
                                {
                                    exit = true;
                                    break;
                                }
                                else
                                {
                                    manageUser.updateLoan(true, choice1);
                                    exit = true;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    // XỬ LÝ CẬP NHẬT KHOẢN VAY
                    else if (choice == 1)
                    {
                        int choice1 = 0;
                        bool exit = false;
                        while (!exit)
                        {
                            system("cls");
                            vector<string> borrowloanItems = this->manageUser.getBorrows();
                            if (borrowloanItems.size() == 0)
                            {
                                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                SetConsoleTextAttribute(hConsole, 4);
                                cout << "-------------------------------------------------------------------\n";
                                cout << "           Chưa có khoản vay! Vui lòng thêm khoản vay\n";
                                cout << "-------------------------------------------------------------------\n";
                                pause();
                                return SCREEN_LOANMANAGE;
                            }
                            borrowloanItems.push_back("Quay lại trang trước");
                            login.printTitle();
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                            cout << "-------------- Chọn khoản vay bạn muốn cập nhật --------------\n\n";
                            displayMenu(borrowloanItems, choice1);
                            keyInput = _getch();
                            switch (keyInput)
                            {
                            case KEY_UP:
                                choice1 = (choice1 - 1 + borrowloanItems.size()) % borrowloanItems.size();
                                break;
                            case KEY_DOWN:
                                choice1 = (choice1 + 1) % borrowloanItems.size();
                                break;
                            case KEY_ENTER:
                                if (choice1 == borrowloanItems.size() - 1)
                                {
                                    exit = true;
                                    break;
                                }
                                else
                                {
                                    manageUser.updateLoan(false, choice1);
                                    exit = true;
                                    break;
                                }
                            }
                        }
                    }
                    // XỬ LÝ QUAY LẠI MÀN HÌNH
                    else if (choice == 2)
                    {
                        return SCREEN_LOANMANAGE;
                    }
                }
                }
            }
            break;
        }

        // XỬ LÝ THANH TOÁN KHOẢN VAY VÀ CHO VAY
        else if (selection == 4)
        {
            system("cls");
            login.printTitle();
            vector<string> choiceItems = {"Thanh toán khoản cho vay", "Thanh toán khoản vay", "Quay lại trang trước"};
            int choice = 0;

            while (true)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                {
                    // XỬ LÝ THANH TOÁN KHOẢN CHO VAY
                    if (choice == 0)
                    {
                        system("cls");
                        login.printTitle();
                        int option = 0;
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "--------------- Danh sách các khoản cho vay ---------------" << endl
                             << endl
                             << endl;
                        int startLine = getCurrentLine();
                        vector<string> itemLends = manageUser.getLends();
                        if (itemLends.size() == 0)
                        {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 4);
                            cout << "-------------------------------------------------------------------\n";
                            cout << "           Chưa có khoản cho vay! Vui lòng thêm khoản cho vay\n";
                            cout << "-------------------------------------------------------------------\n";
                            pause();
                            return SCREEN_LOANMANAGE;
                        }
                        itemLends.push_back("Quay lại trang trước");

                        int key_input;
                        bool flag = false;
                        while (!flag)
                        {
                            clearLines(startLine, itemLends.size());
                            displayMenu2(itemLends, option, startLine);
                            cout << "\n\n\n Sử dụng phím mũi tên ↑ và ↓ để điều hướng.\n\n";
                            cout << " Nhấn ENTER để chọn.\n\n";

                            key_input = _getch();
                            switch (key_input)
                            {
                            case KEY_UP:
                                option = (option - 1 + itemLends.size()) % itemLends.size();
                                break;
                            case KEY_DOWN:
                                option = (option + 1) % itemLends.size();
                                break;
                            case KEY_ENTER:
                            {
                                flag = true;
                                break;
                            }
                            }
                            if (flag && option != itemLends.size() - 1)
                            {
                                system("cls");
                                login.printTitle();
                                manageUser.makePayment(true, option);
                                pause();
                            }
                            else if (flag && option == itemLends.size() - 1)
                            {
                                break;
                            }
                        }
                    }
                    // XỬ LÝ THANH TOÁN KHOẢN VAY
                    else if (choice == 1)
                    {
                        system("cls");
                        login.printTitle();
                        int option = 0;
                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "----------------- Danh sách các khoản vay -----------------" << endl
                             << endl
                             << endl;
                        int startLine = getCurrentLine();
                        vector<string> itemBorrows = manageUser.getBorrows();

                        if (itemBorrows.size() == 0)
                        {
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 4);
                            cout << "-------------------------------------------------------------------\n";
                            cout << "           Chưa có khoản vay! Vui lòng thêm khoản vay\n";
                            cout << "-------------------------------------------------------------------\n";
                            pause();
                            return SCREEN_LOANMANAGE;
                        }
                        itemBorrows.push_back("Quay lại trang trước");
                        int key_input;
                        bool flag = false;
                        while (!flag)
                        {
                            clearLines(startLine, itemBorrows.size());
                            displayMenu2(itemBorrows, option, startLine);
                            cout << "\n\n\n Sử dụng phím mũi tên ↑ và ↓ để điều hướng.\n\n";
                            cout << " Nhấn ENTER để chọn.\n\n";

                            key_input = _getch();
                            switch (key_input)
                            {
                            case KEY_UP:
                                option = (option - 1 + itemBorrows.size()) % itemBorrows.size();
                                break;
                            case KEY_DOWN:
                                option = (option + 1) % itemBorrows.size();
                                break;
                            case KEY_ENTER:
                                flag = true;
                                break;
                            }
                        }
                        if (flag && option != itemBorrows.size() - 1)
                        {
                            system("cls");
                            login.printTitle();
                            manageUser.makePayment(false, option);
                            pause();
                        }
                        else if (flag && option == itemBorrows.size() - 1)
                        {
                            break;
                        }
                    }
                    // XỬ LÝ QUAY LẠI MÀN HÌNH
                    else if (choice == 2)
                    {
                        return SCREEN_LOANMANAGE;
                    }
                }
                }
            }
        }
        // XỬ LÝ TRA CỨU
        else if (selection == 5)
        {
            system("cls");
            login.printTitle();
            vector<string> choiceItems = {"Tra cứu khoản vay và cho vay", "Tra cứu lịch sử thanh toán", "Quay lại trang trước"};
            int choice = 0;
            bool exit = false;

            while (!exit)
            {
                system("cls");
                login.printTitle();
                displayMenu(choiceItems, choice);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + choiceItems.size()) % choiceItems.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % choiceItems.size();
                    break;
                case KEY_ENTER:
                {
                    // XỬ LÝ CHỌN MENU
                    if (choice == 0) // Tra cứu khoản vay và cho vay
                    {
                        int option = 0;
                        vector<string> itemSearch = {"Tra cứu theo tài khoản", "Tra cứu theo thời gian", "Quay lại trang trước"};
                        int key_input;
                        bool flag = false;

                        while (!flag)
                        {
                            system("cls");
                            login.printTitle();
                            displayMenu(itemSearch, option);
                            key_input = _getch();
                            switch (key_input)
                            {
                            case KEY_UP:
                                option = (option - 1 + itemSearch.size()) % itemSearch.size();
                                break;
                            case KEY_DOWN:
                                option = (option + 1) % itemSearch.size();
                                break;
                            case KEY_ENTER:
                                if (option == 0)
                                {
                                    system("cls");
                                    login.printTitle();
                                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    vector<string> listLoans = manageUser.getLends();
                                    vector<string> listBorrows = manageUser.getBorrows();
                                    for (auto &x : listBorrows)
                                    {
                                        listLoans.push_back(x);
                                    }
                                    if (listLoans.size() == 0)
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                        cout << "-------------------------------------------------------------------\n";
                                        cout << "            Chưa có khoản vay và cho vay! Vui lòng thêm\n";
                                        cout << "-------------------------------------------------------------------\n";
                                        pause();
                                        return SCREEN_LOANMANAGE;
                                    }
                                    listLoans.push_back("Quay lại trang trước");
                                    int search_input = 0;
                                    bool search = false;
                                    while (!search)
                                    {
                                        system("cls");
                                        login.printTitle();
                                        SetConsoleTextAttribute(hConsole, 10);
                                        cout << "------------ Danh sách các khoản vay và cho vay -----------" << endl
                                             << endl
                                             << endl;
                                        displayMenu(listLoans, search_input);

                                        key_input = _getch();
                                        switch (key_input)
                                        {
                                        case KEY_UP:
                                            search_input = (search_input - 1 + listLoans.size()) % listLoans.size();
                                            break;
                                        case KEY_DOWN:
                                            search_input = (search_input + 1) % listLoans.size();
                                            break;
                                        case KEY_ENTER:
                                            if (search_input != listLoans.size() - 1)
                                            {
                                                system("cls");
                                                login.printTitle();
                                                if (search_input < listLoans.size() - listBorrows.size() - 1)
                                                {
                                                    manageUser.reportLoan(true, search_input);
                                                }
                                                else
                                                {
                                                    manageUser.reportLoan(false, search_input - listLoans.size() + listBorrows.size() + 1);
                                                }
                                                pause();
                                            }
                                            else if (search_input == listLoans.size() - 1)
                                            {
                                                search = true;
                                            }
                                            break;
                                        }
                                    }
                                }
                                else if (option == 1)
                                {
                                    system("cls");
                                    login.printTitle();
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "------- Tra cứu khoản vay và cho vay theo thời gian -------" << endl
                                         << endl
                                         << endl;
                                    string Start, End;
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                    cout << "Nhập thời gian bắt đầu tra cứu theo định dạng (DD/MM/YYYY): ";
                                    getline(cin, Start);
                                    cout << "Nhập ngày kết thúc tra cứu theo định dạng (DD/MM/YYYY): ";
                                    getline(cin, End);
                                    while (!isValidDate(Start) || !isValidDate(End))
                                    {
                                        system("cls");
                                        login.printTitle();
                                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                        SetConsoleTextAttribute(hConsole, 4);
                                        cout << "-----------------------------------------------------------\n";
                                        cout << "                Lỗi! Vui lòng nhập lại!\n ";
                                        cout << "-----------------------------------------------------------\n";
                                        SetConsoleTextAttribute(hConsole, 7);
                                        cout << "Nhập thời gian bắt đầu tra cứu theo định dạng (DD/MM/YYYY): ";
                                        getline(cin, Start);
                                        cout << "Nhập ngày kết thúc tra cứu theo định dạng (DD/MM/YYYY): ";
                                        getline(cin, End);
                                    }
                                    cout << endl
                                         << endl;
                                    std::tm timeStart = stringChangeDate(Start);
                                    std::tm timeEnd = stringChangeDate(End);
                                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "-------------------------------------------------------------------\n";
                                    SetConsoleTextAttribute(hConsole, 7);
                                    cout << "Khoản vay và cho vay trong khoản thời gian: ";
                                    printDate(timeStart);
                                    cout << " - ";
                                    printDate(timeEnd);
                                    cout << endl;
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "-------------------------------------------------------------------\n";
                                    cout << endl;
                                    SetConsoleTextAttribute(hConsole, 7);
                                    manageUser.filterLoan(timeStart, timeEnd);
                                    pause();
                                }
                                else if (option == 2) // Quay lại trang trước
                                {
                                    flag = true;
                                }
                                break;
                            }
                        }
                    }
                    else if (choice == 1) // Tra cứu lịch sử thanh toán
                    {
                        system("cls");
                        login.printTitle();
                        int option = 0;

                        vector<string> itemSearch = {"Tra cứu theo tài khoản", "Tra cứu theo thời gian", "Quay lại trang trước"};
                        int key_input;
                        bool flag = false;
                        while (!flag)
                        {
                            system("cls");
                            login.printTitle();
                            displayMenu(itemSearch, option);
                            key_input = _getch();
                            switch (key_input)
                            {
                            case KEY_UP:
                                option = (option - 1 + itemSearch.size()) % itemSearch.size();
                                break;
                            case KEY_DOWN:
                                option = (option + 1) % itemSearch.size();
                                break;
                            case KEY_ENTER:
                            {
                                if (option == 0) // Tra cứu theo tài khoản
                                {
                                    system("cls");
                                    login.printTitle();
                                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    vector<string> listLoans = manageUser.getLends();
                                    vector<string> listBorrows = manageUser.getBorrows();
                                    for (auto &x : listBorrows)
                                    {
                                        listLoans.push_back(x);
                                    }
                                    if (listLoans.empty())
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                        cout << "-------------------------------------------------------------------\n";
                                        cout << "            Chưa có khoản vay và cho vay! Vui lòng thêm\n";
                                        cout << "-------------------------------------------------------------------\n";
                                        pause();
                                        break; // Quay lại menu hiện tại
                                    }
                                    listLoans.push_back("Quay lại trang trước");
                                    int search_input = 0;
                                    bool search = false;
                                    while (!search)
                                    {
                                        system("cls");
                                        login.printTitle();
                                        SetConsoleTextAttribute(hConsole, 10);
                                        cout << "------------ Danh sách các khoản vay và cho vay -----------" << endl
                                             << endl
                                             << endl;
                                        displayMenu(listLoans, search_input);

                                        key_input = _getch();
                                        switch (key_input)
                                        {
                                        case KEY_UP:
                                            search_input = (search_input - 1 + listLoans.size()) % listLoans.size();
                                            break;
                                        case KEY_DOWN:
                                            search_input = (search_input + 1) % listLoans.size();
                                            break;
                                        case KEY_ENTER:
                                            if (search_input != listLoans.size() - 1)
                                            {
                                                system("cls");
                                                login.printTitle();
                                                if (search_input < listLoans.size() - listBorrows.size() - 1)
                                                {
                                                    manageUser.displayPaymentHistory(true, search_input);
                                                }
                                                else
                                                {
                                                    manageUser.displayPaymentHistory(false, search_input - listLoans.size() + listBorrows.size() + 1);
                                                }
                                                pause();
                                            }
                                            else if (search_input == listLoans.size() - 1) // Quay lại trang trước
                                            {
                                                search = true;
                                            }
                                            break;
                                        }
                                    }
                                }
                                else if (option == 1) // Tra cứu theo thời gian
                                {
                                    system("cls");
                                    login.printTitle();
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "------- Tra cứu khoản vay và cho vay theo thời gian -------" << endl
                                         << endl
                                         << endl;
                                    string Start, End;
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                    cout << "Nhập thời gian bắt đầu tra cứu theo định dạng (DD/MM/YYYY): ";
                                    getline(cin, Start);
                                    cout << "Nhập ngày kết thúc tra cứu theo định dạng (DD/MM/YYYY): ";
                                    getline(cin, End);
                                    while (!isValidDate(Start) || !isValidDate(End))
                                    {
                                        system("cls");
                                        login.printTitle();
                                        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                        SetConsoleTextAttribute(hConsole, 4);
                                        cout << "-----------------------------------------------------------\n";
                                        cout << "              Lỗi! Vui lòng nhập lại!\n ";
                                        cout << "-----------------------------------------------------------\n";
                                        SetConsoleTextAttribute(hConsole, 7);
                                        cout << "Nhập thời gian bắt đầu tra cứu theo định dạng (DD/MM/YYYY): ";
                                        getline(cin, Start);
                                        cout << "Nhập ngày kết thúc tra cứu theo định dạng (DD/MM/YYYY): ";
                                        getline(cin, End);
                                    }
                                    cout << endl
                                         << endl;
                                    std::tm timeStart = stringChangeDate(Start);
                                    std::tm timeEnd = stringChangeDate(End);
                                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "-------------------------------------------------------------------\n";
                                    SetConsoleTextAttribute(hConsole, 7);
                                    cout << "Khoản vay và cho vay trong khoản thời gian: ";
                                    printDate(timeStart);
                                    cout << " - ";
                                    printDate(timeEnd);
                                    cout << endl;
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << "-------------------------------------------------------------------\n";
                                    cout << endl;
                                    SetConsoleTextAttribute(hConsole, 7);
                                    manageUser.filterPayment(timeStart, timeEnd);
                                    pause();
                                }
                                else if (option == 2) // Quay lại trang trước
                                {
                                    flag = true;
                                }
                                break;
                            }
                            }
                        }
                    }

                    else if (choice == 2) // Quay lại trang trước
                    {
                        exit = true;
                    }
                    break;
                }
                }
            }
        }
        // XỬ LÝ QUAY LẠI MÀN HÌNH
        else if (selection == 6)
        {
            return SCREEN_MAIN;
        }
        break;
    }
    }
    return SCREEN_LOANMANAGE;
}