// Class Account Screen

#pragma once

#include <iostream>
#include <vector>

#include "ScreenADT.h"

using namespace std;

class AccountScreen : public Screen
{
private:
    int selection = 0;
    vector<string> menuItems;

public:
    AccountScreen(ManageUser &userManager);

    void display() override;

    int handleInput(int keyInput) override;
};

AccountScreen::AccountScreen(ManageUser &userManager) : Screen(userManager)
{
    menuItems = {"Xem thông tin tài khoản", "Thêm tài khoản", "Xóa tài khoản", "Cập nhật tiền", "Báo cáo", "Lịch sử giao dịch", "Quay lại trang trước"};
    selection = 0;
}

void AccountScreen::display()
{
    system("cls");
    login.printTitle();
    displayMenu(menuItems, selection);
}

int AccountScreen::handleInput(int keyInput)
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
        // XỬ LÝ HIỂN THỊ THÔNG TIN TÀI KHOẢN
        if (selection == 0)
        {
            system("cls");
            login.printTitle();

            vector<string> itemAccounts = manageUser.getAccounts();
            if (itemAccounts.size() == 0)
            {
                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                SetConsoleTextAttribute(hConsole, 4);
                cout << "-----------------------------------------------------------\n";
                cout << "        Chưa có tài khoản! Vui lòng thêm tài khoản\n";
                cout << "-----------------------------------------------------------\n";
                pause();
                return SCREEN_ACCOUNTMANAGE;
            }
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "------------- Tổng số dư của tất cả tài khoản -------------" << endl
                 << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            double balance = manageUser.getBalance();
            string ans = to_string(balance);
            ans = ans.substr(0, ans.size() - 4);
            ans = formatNumber(ans);
            cout << "Số dư: " << ans + " VND" << endl
                 << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "----------------- Số dư của từng tài khoản ----------------" << endl
                 << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            manageUser.getBalanceBank();
            pause();
            return SCREEN_ACCOUNTMANAGE;
        }
        // XỬ LÝ THÊM TÀI KHOẢN
        else if (selection == 1)
        {
            system("cls");
            login.printTitle();

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << "--------- Nhập thông tin tài khoản bạn muốn thêm ---------" << endl
                 << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            AccountBank newBank;
            newBank.EditBank();
            cin.ignore();

            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 10);
            cout << "------- Bạn có chắc chắn muốn thêm khoản tài khoản ? -------" << endl
                 << endl;
            vector<string> choiceItems = {"Chắc chắn", "Không"};
            int choice = 0;
            int keyInput;
            int startLine = getCurrentLine();
            bool flag = false;
            while (!flag)
            {
                clearLines(startLine, choiceItems.size());

                displayMenu2(choiceItems, choice, startLine);

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
                    if (choice == 0)
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "               Thêm tài khoản thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                        pause();
                        manageUser.addAccountBank(newBank);
                    }
                    else if (choice == 1)
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(hConsole, 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "           Thêm tài khoản không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                        pause();
                    }
                    flag = true;
                    break;
                }
                }
            }
        }
        else if (selection == 2)
        {
            int choice = 0;
            system("cls");
            login.printTitle();
            bool exit = false;
            while (!exit)
            {
                system("cls");
                login.printTitle();
                vector<string> itemAccounts = manageUser.getAccounts();
                itemAccounts.push_back("Quay lại trang trước");
                choice = (choice + itemAccounts.size()) % itemAccounts.size();
                if (itemAccounts.size() == 1)
                {
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "-----------------------------------------------------------\n";
                    cout << "         Chưa có tài khoản! Vui lòng thêm tài khoản\n";
                    cout << "-----------------------------------------------------------\n";
                    pause();
                    return SCREEN_ACCOUNTMANAGE;
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "--------------- Chọn tài khoản bạn muốn xóa ---------------\n\n";
                displayMenu(itemAccounts, choice);
                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + itemAccounts.size()) % itemAccounts.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % itemAccounts.size();
                    break;
                case KEY_ENTER:
                {
                    if (choice == itemAccounts.size() - 1)
                    {
                        exit = true;
                        break;
                    }
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "------- Bạn có chắc chắn muốn xóa khoản tài khoản ? -------" << endl
                         << endl;
                    vector<string> choiceItems = {"Chắc chắn", "Không"};
                    int option = 0;
                    int keyInput;
                    int startLine = getCurrentLine();
                    bool flag = false;
                    while (!flag)
                    {
                        clearLines(startLine, choiceItems.size());

                        displayMenu2(choiceItems, option, startLine);

                        keyInput = _getch();
                        switch (keyInput)
                        {
                        case KEY_UP:
                            option = (option - 1 + choiceItems.size()) % choiceItems.size();
                            break;
                        case KEY_DOWN:
                            option = (option + 1) % choiceItems.size();
                            break;
                        case KEY_ENTER:
                        {
                            if (option == 0)
                            {
                                cout << endl
                                     << endl;
                                manageUser.deleteAccountBank(choice + 1);
                                HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                                SetConsoleTextAttribute(hConsole, 10);
                                cout << "-----------------------------------------------------------\n";
                                cout << "               Xóa tài khoản thành công.\n";
                                cout << "-----------------------------------------------------------\n";
                                pause();
                            }
                            else if (option == 1)
                            {
                                cout << endl
                                     << endl;
                                SetConsoleTextAttribute(hConsole, 4);
                                cout << "-----------------------------------------------------------\n";
                                cout << "             Xóa tài khoản không thành công.\n";
                                cout << "-----------------------------------------------------------\n";
                                pause();
                            }
                            flag = true;
                            break;
                        }
                        }
                    }
                    break;
                }
                }
            }
        }

        // XỬ LÝ CẬP NHẬT TIỀN
        else if (selection == 3)
        {
            int choice = 0;
            system("cls");
            login.printTitle();
            bool exit = false;
            while (!exit)
            {
                system("cls");
                login.printTitle();

                vector<string> itemAccounts = manageUser.getAccounts();
                itemAccounts.push_back("Quay lại trang trước");
                if (itemAccounts.size() == 1)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                    cout << "-----------------------------------------------------------\n";
                    cout << "         Chưa có tài khoản! Vui lòng thêm tài khoản\n";
                    cout << "-----------------------------------------------------------\n";
                    pause();
                    return SCREEN_ACCOUNTMANAGE;
                }

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "--------- Chọn tài khoản bạn muốn cập nhật tiền ----------\n\n";

                displayMenu(itemAccounts, choice);
                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choice = (choice - 1 + itemAccounts.size()) % itemAccounts.size();
                    break;
                case KEY_DOWN:
                    choice = (choice + 1) % itemAccounts.size();
                    break;
                case KEY_ENTER:
                {
                    if (choice == itemAccounts.size() - 1)
                    {
                        exit = true;
                        break;
                    }
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << "Nhập số tiền bạn muốn cập nhật: ";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    double result;
                    string sotien;
                    getAmount(sotien, result);

                    cout << endl
                         << endl;
                    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "------- Bạn có chắc chắn muốn cập nhật số tiền này? -------" << endl
                         << endl;
                    vector<string> choiceItems = {"Chắc chắn", "Không"};
                    int option = 0;
                    int startLine = getCurrentLine();
                    bool flag = false;
                    cout << endl<<endl;
                    while (!flag)
                    {
                        clearLines(startLine, choiceItems.size());
                        displayMenu2(choiceItems, option, startLine);
                        keyInput = _getch();
                        switch (keyInput)
                        {
                        case KEY_UP:
                            option = (option - 1 + choiceItems.size()) % choiceItems.size();
                            break;
                        case KEY_DOWN:
                            option = (option + 1) % choiceItems.size();
                            break;
                        case KEY_ENTER:
                        {
                            if (option == 0)
                            {
                                if (manageUser.updateBalance(result, choice + 1))
                                {
                                    SetConsoleTextAttribute(hConsole, 10);
                                    cout << endl;
                                    cout << "-----------------------------------------------------------\n";
                                    cout << "                  Cập nhật thành công\n";
                                    cout << "-----------------------------------------------------------\n";
                                }
                                else
                                {
                                    SetConsoleTextAttribute(hConsole, 4);
                                    cout << endl;
                                    cout << "-----------------------------------------------------------\n";
                                    cout << "                 Cập nhật không thành công\n";
                                    cout << "-----------------------------------------------------------\n";
                                }
                            }
                            else if (option == 1)
                            {
                                SetConsoleTextAttribute(hConsole, 4);
                                cout << endl;
                                cout << "-----------------------------------------------------------\n";
                                cout << "                Cập nhật không thành công\n";
                                cout << "-----------------------------------------------------------\n";
                            }
                            pause();
                            flag = true;
                            break;
                        }
                        }
                    }
                    break;
                }
                }
            }
        }

        else if (selection == 4)
        {
            int choiceReport = 0;
            system("cls");
            login.printTitle();
            while (true)
            {
                system("cls");
                login.printTitle();

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "--------- Chọn loại báo cáo mà bạn muốn xem ----------\n\n";

                vector<string> Report = {"Báo cáo chung", "Báo cáo riêng từng tài khoản", "Quay lại trang trước"};
                choiceReport = (choiceReport + Report.size()) % Report.size();
                displayMenu(Report, choiceReport);

                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choiceReport = (choiceReport - 1 + Report.size()) % Report.size();
                    break;
                case KEY_DOWN:
                    choiceReport = (choiceReport + 1) % Report.size();
                    break;
                case KEY_ENTER:
                {
                    if (choiceReport == 0)
                    {
                        system("cls");
                        login.printTitle();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << endl;
                        cout << "---------------------- Mục chi tiêu ----------------------\n";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                        manageUser.printReport();
                        pause();
                    }
                    else if (choiceReport == 1)
                    {
                        int choice = 0;
                        system("cls");
                        login.printTitle();
                        bool flag = false;
                        while (!flag)
                        {
                            system("cls");
                            login.printTitle();
                            vector<string> itemAccounts = manageUser.getAccounts();
                            if (itemAccounts.size() == 0)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                cout << "-----------------------------------------------------------\n";
                                cout << "         Chưa có tài khoản! Vui lòng thêm tài khoản\n";
                                cout << "-----------------------------------------------------------\n";
                                pause();
                                return SCREEN_ACCOUNTMANAGE;
                            }
                            itemAccounts.push_back("Tất cả");
                            itemAccounts.push_back("Quay lại trang trước");
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                            cout << "------------------- Thông tin tài khoản -------------------" << endl
                                 << endl;
                            choice = (choice + itemAccounts.size()) % itemAccounts.size();
                            displayMenu(itemAccounts, choice);
                            int key = _getch();
                            switch (key)
                            {
                            case KEY_UP:
                                choice = (choice - 1 + itemAccounts.size()) % itemAccounts.size();
                                break;
                            case KEY_DOWN:
                                choice = (choice + 1) % itemAccounts.size();
                                break;
                            case KEY_ENTER:
                            {
                                if (choice == itemAccounts.size() - 1)
                                {
                                    flag = true;
                                    break;
                                }
                                if (choice + 1 == itemAccounts.size() - 1)
                                {
                                    system("cls");
                                    login.printTitle();
                                    manageUser.printReportBank(0);
                                }
                                else
                                {
                                    system("cls");
                                    login.printTitle();
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "Thông tin tài khoản: ";
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                    cout << itemAccounts[choice] << endl;
                                    manageUser.printReportBank(choice + 1);
                                }
                                pause();
                                break;
                            }
                            }
                        }
                    }
                    else if (choiceReport == 2)
                    {
                        return SCREEN_ACCOUNTMANAGE;
                    }
                    break;
                }
                }
            }
        }
        // XỬ LÝ TRA CỨU LỊCH SỬ
        else if (selection == 5)
        {
            int choiceReport = 0;
            system("cls");
            login.printTitle();
            while (true)
            {
                system("cls");
                login.printTitle();
                vector<string> Report = {"Xem lịch sử", "Xem lịch sử riêng từng tài khoản", "Tra cứu lịch sử theo tiêu chí chi tiêu", "Tra cứu lịch sử theo thời gian", "Quay lại trang trước"};
                choiceReport = (choiceReport + Report.size()) % Report.size();
                displayMenu(Report, choiceReport);
                keyInput = _getch();
                switch (keyInput)
                {
                case KEY_UP:
                    choiceReport = (choiceReport - 1 + Report.size()) % Report.size();
                    break;
                case KEY_DOWN:
                    choiceReport = (choiceReport + 1) % Report.size();
                    break;
                case KEY_ENTER:
                {
                    if (choiceReport == 0)
                    {
                        system("cls");
                        login.printTitle();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << endl;
                        cout << "------------------- Lịch sử giao dịch -------------------\n\n";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

                        manageUser.printHistory();
                        cout << endl;
                        pause();
                    }
                    else if (choiceReport == 1)
                    {
                        int choice = 0;
                        system("cls");
                        login.printTitle();
                        bool flag = false;
                        while (!flag)
                        {
                            system("cls");
                            login.printTitle();
                            vector<string> itemAccounts = manageUser.getAccounts();
                            if (itemAccounts.size() == 0)
                            {
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                                cout << "-----------------------------------------------------------\n";
                                cout << "         Chưa có tài khoản! Vui lòng thêm tài khoản\n";
                                cout << "-----------------------------------------------------------\n";
                                cout << endl;
                                pause();
                                return SCREEN_ACCOUNTMANAGE;
                            }

                            itemAccounts.push_back("Tất cả");
                            itemAccounts.push_back("Quay lại trang trước");
                            choice = (choice + itemAccounts.size()) % itemAccounts.size();
                            displayMenu(itemAccounts, choice);
                            int key = _getch();
                            switch (key)
                            {
                            case KEY_UP:
                                choice = (choice - 1 + itemAccounts.size()) % itemAccounts.size();
                                break;
                            case KEY_DOWN:
                                choice = (choice + 1) % itemAccounts.size();
                                break;
                            case KEY_ENTER:
                            {
                                if (choice == itemAccounts.size() - 1)
                                {
                                    flag = true;
                                    break;
                                }
                                if (choice + 1 == itemAccounts.size() - 1)
                                {
                                    system("cls");
                                    login.printTitle();

                                    manageUser.printHistoryBank(0);
                                    cout << endl;
                                }
                                else
                                {
                                    system("cls");
                                    login.printTitle();
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                    cout << "Thông tin tài khoản: ";
                                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                    cout << itemAccounts[choice] << endl;

                                    manageUser.printHistoryBank(choice + 1);
                                    cout << endl;
                                }
                                pause();
                                break;
                            }
                            }
                        }
                    }
                    else if (choiceReport == 2)
                    {
                        int choice = 0;
                        system("cls");
                        login.printTitle();
                        bool flag = false;
                        while (!flag)
                        {
                            system("cls");
                            login.printTitle();
                            vector<string> itemAccounts = {"Giáo dục", "Sức khỏe", "Gia đình", "Mua sắm", "Ăn uống", "Đầu tư", "Khẩn cấp", "Du lịch", "Di chuyển", "Khác", "Quay lại trang trước"};
                            vector<string> listPurpose = {"Giao duc", "Suc khoe", "Gia dinh", "Mua sam", "An uong", "Dau tu", "Khan cap", "Du lich", "Di chuyen", "Khac"};
                            choice = (choice + itemAccounts.size()) % itemAccounts.size();
                            displayMenu(itemAccounts, choice);
                            int key = _getch();
                            switch (key)
                            {
                            case KEY_UP:
                                choice = (choice - 1 + itemAccounts.size()) % itemAccounts.size();
                                break;
                            case KEY_DOWN:
                                choice = (choice + 1) % itemAccounts.size();
                                break;
                            case KEY_ENTER:
                            {
                                if (choice == itemAccounts.size() - 1)
                                {
                                    flag = true;
                                    break;
                                }
                                system("cls");
                                login.printTitle();
                                string purpose = listPurpose[choice];
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                                cout << "Lịch sử giao dịch chi tiêu cho mục đích: ";
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                                cout << itemAccounts[choice] << endl
                                     << endl;

                                manageUser.filterTransaction(purpose);
                                cout << endl;
                                pause();
                                break;
                            }
                            }
                        }
                    }
                    else if (choiceReport == 3)
                    {
                        system("cls");
                        login.printTitle();
                        string Start, End;

                        cout << "Nhập thời gian bắt đầu  kiểm tra theo định dạng (DD/MM/YYYY): ";
                        getline(cin, Start);
                        cout << "Nhập ngày kết thúc kiểm tra theo định dạng (DD/MM/YYYY): ";
                        getline(cin, End);
                        while (!isValidDate(Start) || !isValidDate(End))
                        {
                            system("cls");
                            login.printTitle();
                            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                            SetConsoleTextAttribute(hConsole, 4);
                            cout << "-----------------------------------------------------------\n";
                            cout << "               Lỗi! Vui lòng nhập lại!\n";
                            cout << "-----------------------------------------------------------\n";
                            SetConsoleTextAttribute(hConsole, 7);
                            cout << "Nhập ngày bắt đầu kiểm tra theo định dạng (DD/MM/YYYY): ";
                            getline(cin, Start);
                            cout << "Nhập ngày kết thúc kiểm tra theo định dạng (DD/MM/YYYY): ";
                            getline(cin, End);
                        }
                        std::tm timeStart = stringChangeDate(Start);
                        std::tm timeEnd = stringChangeDate(End);

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "\nLịch sử giao dịch trong khoảng thời gian: ";
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        printDate(timeStart);
                        cout << " - ";
                        printDate(timeEnd);
                        cout << endl
                             << endl;

                        manageUser.filterTransaction(timeStart, timeEnd);
                        pause();
                    }
                    else if (choiceReport == 4)
                    {
                        return SCREEN_ACCOUNTMANAGE;
                    }
                    break;
                }
                }
            }
        }
        else
        {
            return SCREEN_MAIN;
        }

        break;
    }
    return SCREEN_ACCOUNTMANAGE;
}
