// Class Transaction

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <fstream>

#include "../Date_Time/CheckValidDate.h"

using namespace std;

class Transaction
{
public:
	string nameBank;
	std::tm date;
	double amount;
	double balance; // so du tai khoan
	string purpose;
	string note;
	Transaction()
	{
		this->nameBank = "";
		this->date = {};
		this->amount = 0;
		this->balance = 0;
		this->purpose = "";
		this->note = "";
	}
	void inputTransaction();
	void displayTransaction();
	void setTransaction(const string &nameBank, const std::tm &date, const double &amount, const double &balance, const string &purpose);
	void setTransaction(const std::tm &date, const double &amount, const double &balance, const string &purpose);
	// void setTransaction(const string& nameBank, const std::tm& date, const double& amount,double const& sodu, const string& purpose);
	void dispalyForManage(); // dung cho manage
	void printDate();
	void loadFromFile(istream &file);
	void WriteToFile(ostream &file);
};

void Transaction::WriteToFile(ostream &file)
{
	file << this->nameBank << endl;
	file << this->amount << " " << this->balance << " ";
	file << std::put_time(&this->date, "%d/%m/%Y");
	file << " " << standardize(this->purpose) << " " << endl;
}

void Transaction::loadFromFile(istream &file)
{
	string time;
	getline(file, this->nameBank);
	double sodu;
	file >> this->amount >> this->balance >> time;
	file.ignore();
	this->date = stringChangeDate(time);
	getline(file, this->purpose);
}

void Transaction::dispalyForManage()
{
	string tmp = to_string(this->amount);
	if (tmp.size() > 4)
		tmp = tmp.substr(0, tmp.length() - 4);
	tmp = formatNumber(tmp);
	string ans = to_string(this->balance);
	if (ans.size() > 4)
		ans = ans.substr(0, ans.size() - 4);

	ans = formatNumber(ans);
	cout << left << setw(20) << this->nameBank << " ";
	cout << setw(42)
		 << (this->amount > 0 ? "+" : "") + tmp + " VND " + "| SD: " + ans + " VND ";
	printDate();
	if (!standardize(this->purpose).empty())
		cout << setw(20) << "   " + standardize(this->purpose) << endl;
	else
		cout << endl;
}

void Transaction::inputTransaction()
{
	double data;
	cout << "Nhap so tien giao dich: ";
	cin >> data;
	string ngay;
	cout << "Nhap ngay giao dich dinh dang (DD/MM/YYYY): ";
	cin.ignore();
	getline(cin, ngay);
	this->amount = data;
	if (ngay.size() >= 10)
	{
		string day = ngay.substr(0, 2);
		string month = ngay.substr(3, 2);
		string year = ngay.substr(6, 4);
		this->date.tm_year = stoi(year) - 1900;
		this->date.tm_mon = stoi(month) - 1;
		this->date.tm_mday = stoi(day);
	}
}

void Transaction::displayTransaction()
{
	printDate();
	string tmp = to_string(this->amount);
	if (tmp.size() > 4)
		tmp = tmp.substr(0, tmp.length() - 4);
	tmp = formatNumber(tmp);
	string ans = to_string(this->balance);
	if (ans.size() > 4)
		ans = ans.substr(0, ans.length() - 4);
	ans = formatNumber(ans);
	cout << "  ";
	cout << left;
	cout << left << setw(40)
		 << (this->amount > 0 ? "+" : "") + tmp + "VND | SD:" + ans + "VND"
		 << setw(20) << standardize(this->purpose) << endl;
}

// hàm in ngày tháng theoi định dạng yyyy-mm--dd
void Transaction::printDate()
{
	cout << std::put_time(&this->date, "%d/%m/%Y");
}

void Transaction::setTransaction(const string &nameBank, const std::tm &date, const double &amount, const double &balance, const string &purpose)
{
	this->nameBank = nameBank;
	this->date = date;
	this->amount = amount;
	this->balance = balance;
	this->purpose = purpose;
	if (this->purpose.size() >= 1)
		this->purpose = standardize(this->purpose);
}

void Transaction::setTransaction(const ::tm &date, const double &amount, const double &balance, const string &purpose)
{
	this->date = date;
	this->amount = amount;
	this->balance = balance;
	this->purpose = purpose;
	if (this->purpose.size() >= 1)
		this->purpose = standardize(this->purpose);
}