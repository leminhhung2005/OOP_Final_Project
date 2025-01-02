// Class Balance Screen

#pragma once

#include <iostream>
#include <vector>
#include "ScreenADT.h"
#include "../Manage/ManageUser.h"

using namespace std;

class BalanceScreen : public Screen
{
private:
	int selection = 0;
	vector<string> menuItems;

public:
	BalanceScreen(ManageUser &userManager);

	void display() override;
	int handleInput(int keyInput) override;
};

BalanceScreen::BalanceScreen(ManageUser &userManager) : Screen(userManager)
{
	menuItems = {"Hiển thị tổng số dư tất cả tài khoản", "Hiển thị tổng số dư của từng tài khoản", "Quay lại trang trước"};
	selection = 0;
}

void BalanceScreen::display()
{
	system("cls");
	login.printTitle();
	displayMenu(menuItems, selection);
}

int BalanceScreen::handleInput(int keyInput)
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
			vector<string> itemAccounts = manageUser.getAccounts();
			if (itemAccounts.size() == 0)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 4);
				cout << "-----------------------------------------------------------\n";
				cout << "        Chưa có tài khoản! Vui lòng thêm tài khoản\n";
				cout << "-----------------------------------------------------------\n";
				pause();
				return SCREEN_SHOWBALANCE;
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
			pause();
		}
		else if (selection == 1)
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
				return SCREEN_SHOWBALANCE;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			cout << "----------------- Số dư của từng tài khoản ----------------" << endl
				 << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			manageUser.getBalanceBank();
			pause();
		}
		else
		{
			return SCREEN_MAIN;
		}
		break;
	}
	return SCREEN_SHOWBALANCE;
}