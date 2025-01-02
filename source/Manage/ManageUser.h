// Class Manage User

#pragma once

#include "../Bank/AccountBank.h"
#include "TransactionManage.h"
#include "BankManage.h"
#include "LoanManager.h"

using namespace std;

class ManageUser
{
private:
	string nameUser;
	vector<double> purpose;
	BankManage bankManage;
	TransactionManage transManage;
	LoanManager loanManager;

public:
	// defaut constructor
	ManageUser()
	{
		this->nameUser = "";
	}


	// đọc file
	void loadFromFile(const string &fileName);

	// viết file
	void WriteToFile();

	// lien quan den BankManage
	void printHistoryBank();

	void printHistoryBank(int index);

	// thêm tài khoản
	void addAccountBank();

	// thêm tài khoản
	void addAccountBank(AccountBank &Bank);

	// xóa tài khoản
	void deleteAccountBank();

	vector<AccountBank> getBank();

	void deleteAccountBank(int index);

	// tổng số dư của tất cả tài khoản
	double getBalance();

	// tổng số dư của từng tài khoản
	double getBalanceBank();

	void updatePurpose();

	// lấy thông tin tất cả tài khoản
	vector<string> getAccounts();

	

	void updateBalance();

	void updateBalance(double &money);

	bool updateBalance(double &money, int index);

	// bao cao chi tieu theo tung tai khoan
	void printReportBank();

	void printReportBank(int index);

	// lien quan den TransactionManage
	void printHistory();

	// tra cuu lich su giao dich voi muc dich
	void filterTransaction(string &purpose);

	// tra cứu lịch sử giao dịch với khoảng thời gian
	void filterTransaction(const std::tm timeStart, const std::tm timeEnd);

	void editNameUser();

	void displayManage();

	void printReport();

	

	void reset();

	// QUẢN LÝ KHOẢN CHO VAY VÀ VAY

	// báo cáo tổng thể UI
	void generateReport();

	// báo cáo chi tiết UI
	void generateReportAll();

	// thêm các khoản vay hoặc cho vay UI
	void addLoan(bool isLend);

	// xóa các khoản vay hoặc cho vay UI
	void deleteLoan(bool isLend, int choice);

	// cập nhật các khoản vay hoặc cho vay UI
	void updateLoan(bool isLend, int choice);

	// thực hiện thanh toán UI
	void makePayment(bool isLend, int index);

	// tra cứu khoản vay và cho vay theo thời gian
	void filterLoan(const std::tm timeStart, const std::tm timeEnd);

	// tra cứu thanh toán theo thời gian
	void filterPayment(const std::tm timeStart, const std::tm timeEnd);

	// lấy thông tin của khoản cho vay UI
	vector<string> getLends();

	// lấy thông tin của khoản vay UI
	vector<string> getBorrows();

	

	// báo cáo khoản vay và cho vay theo index
	void reportLoan(bool isLend, int index);

	void displayPaymentHistory(bool isLend, int index);

	

	void remindDueDate();

	
};

void ManageUser::reset()
{
	this->bankManage.reset();
}

void ManageUser::updateLoan(bool isLend, int choice)
{
	if (isLend)
	{
		this->loanManager.updateLoan(true, choice);
	}
	else
	{
		this->loanManager.updateLoan(false, choice);
	}
}

vector<AccountBank> ManageUser::getBank()
{
	return this->bankManage.getBank();
}

void ManageUser::remindDueDate()
{
	this->loanManager.remindDueDate();
}

void ManageUser::updateBalance(double &money)
{
	int index = this->bankManage.updateBalance(money);
	if (index != -1)
	{
		Transaction ans = this->bankManage.getBank()[index].history[this->bankManage.getBank()[index].history.size() - 1];
		this->transManage.insertTransaction(ans);
		string purpose = ans.purpose;
		purpose = standardize(purpose);
		for (int i = 0; i < 10; i++)
		{
			if (standardize(destArr[i]) == purpose)
			{
				this->purpose[i] -= money;
			}
		}
	}
}

void ManageUser::updateBalance()
{
	cout << "Nhap so tien ban muon cap nhat: ";
	double money;
	cin >> money;
	int index = this->bankManage.updateBalance(money);
	if (index != -1)
	{
		Transaction ans = this->bankManage.getBank()[index].history[this->bankManage.getBank()[index].history.size() - 1];
		this->transManage.insertTransaction(ans);
		string purpose = ans.purpose;
		purpose = standardize(purpose);
		for (int i = 0; i < 10; i++)
		{
			if (standardize(destArr[i]) == purpose)
			{
				this->purpose[i] -= money;
			}
		}
	}
}

void ManageUser::filterTransaction(const std::tm timeStart, const std::tm timeEnd)
{
	this->transManage.filterTransaction(timeStart, timeEnd);
}

void ManageUser::filterTransaction(string &purpose)
{
	this->transManage.printHistoryReport(purpose);
}

void ManageUser::updatePurpose()
{
	this->purpose.assign(10, 0);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < this->bankManage.getBank().size(); j++)
		{
			this->purpose[i] += this->bankManage.getBank()[j].purpose[i];
		}
	}
}

void ManageUser::printReport()
{
	cout << endl;
	updatePurpose();
	cout << "\t\t[1]. Giáo dục  : " << formatNumber(to_string((this->purpose[0]))) << " VND" << '\n';
	cout << "\t\t[2]. Sức khỏe  : " << formatNumber(to_string((this->purpose[1]))) << " VND" << '\n';
	cout << "\t\t[3]. Gia đình  : " << formatNumber(to_string((this->purpose[2]))) << " VND" << '\n';
	cout << "\t\t[4]. Mua sắm   : " << formatNumber(to_string((this->purpose[3]))) << " VND" << '\n';
	cout << "\t\t[5]. Ăn uống   : " << formatNumber(to_string((this->purpose[4]))) << " VND" << '\n';
	cout << "\t\t[6]. Đầu tư    : " << formatNumber(to_string((this->purpose[5]))) << " VND" << '\n';
	cout << "\t\t[7]. Khẩn cấp  : " << formatNumber(to_string((this->purpose[6]))) << " VND" << '\n';
	cout << "\t\t[8]. Du lịch   : " << formatNumber(to_string((this->purpose[7]))) << " VND" << '\n';
	cout << "\t\t[9]. Di chuyển : " << formatNumber(to_string((this->purpose[8]))) << " VND" << '\n';
	cout << "\t\t[10].Khác     : " << formatNumber(to_string((this->purpose[9]))) << " VND" << '\n';
}

void ManageUser::printReportBank()
{
	this->bankManage.printReport();
}

void ManageUser::printReportBank(int index)
{
	this->bankManage.printReport(index);
}

void ManageUser::displayManage()
{
	cout << "Ten tai khoan: " << this->nameUser << endl;
	string ans = to_string(this->getBalance());
	ans = ans.substr(0, ans.size() - 4);
	ans = formatNumber(ans);
	cout << "So du: " << ans + "VND" << endl;
}

double ManageUser::getBalanceBank()
{
	return this->bankManage.getBalanceBank();
}

double ManageUser::getBalance()
{
	return this->bankManage.getBalance();
}

void ManageUser::deleteAccountBank()
{
	this->bankManage.deleteAccountBank();
}

void ManageUser::addAccountBank()
{
	this->bankManage.addAccountBank();
}

void ManageUser::addAccountBank(AccountBank &Bank)
{
	this->bankManage.addAccountBank(Bank);
}

void ManageUser::editNameUser()
{
	cout << "Nhap ten: ";
	getline(cin, this->nameUser);
}

void ManageUser::WriteToFile()
{
	string fileName = "../InputFile/inputUser.txt";
	ofstream file(fileName);
	// file << this->nameUser << endl;
	this->bankManage.WriteToFile();
	this->transManage.WirteToFile();
	this->loanManager.writeToFile("../InputFile/inputLoan.txt");
	file.close();
}

void ManageUser::printHistoryBank()
{
	this->bankManage.printHistoryBank();
}

void ManageUser::printHistoryBank(int index)
{
	this->bankManage.printHistoryBank(index);
}

void ManageUser::deleteLoan(bool isLend, int choice)
{
	if (isLend)
	{
		this->loanManager.deleteLoan(true, choice);
	}
	else
	{
		this->loanManager.deleteLoan(false, choice);
	}
}

void ManageUser::printHistory()
{
	this->transManage.printHistory();
}



void ManageUser::loadFromFile(const string &fileName)
{
	ifstream file(fileName);
	if (!file)
	{
		cout << "Loi mo file\n";
		return;
	}
	// getline(file, this->nameUser);
	this->purpose.assign(10,0);
	
	this->bankManage.loadFromFile();
	this->transManage.LoadFromFile();
	this->loanManager.loadFromFile("../InputFile/inputLoan.txt");

	vector<Transaction> Trans = this->transManage.getTrans();
	vector<AccountBank> Bank = this->bankManage.getBank();

	// kiem tra tat ca giao dich de them giao dich vao cac tai khoan
	for (int i = 0; i < Trans.size(); i++)
	{
		string ans = Trans[i].nameBank;
		ans = standardize(ans);
		for (int j = 0; j < Bank.size(); j++)
		{
			string nameBank = Bank[j].accountNumber + Bank[j].nameBank;
			nameBank = standardize(nameBank);
			if (ans == nameBank)
			{
				this->bankManage.addTransaction(Trans[i], j);
				break;
			}
		}
	}
}

void ManageUser::generateReport()
{
	this->loanManager.generateReport();
}

void ManageUser::generateReportAll()
{
	this->loanManager.generateReportAll();
}


void ManageUser::addLoan(bool isLend)
{
	if (isLend)
		this->loanManager.addLoan(true);
	else
		this->loanManager.addLoan(false);
}

void ManageUser::makePayment(bool isLend, int index)
{
	if (isLend)
		this->loanManager.makePayment(true, index);
	else
		this->loanManager.makePayment(false, index);
}

void ManageUser::filterLoan(const std::tm timeStart, const std::tm timeEnd)
{
	this->loanManager.filterLoan(timeStart, timeEnd);
}

void ManageUser::filterPayment(const std::tm timeStart, const std::tm timeEnd)
{
	this->loanManager.filterPayment(timeStart, timeEnd);
}

vector<string> ManageUser::getAccounts()
{
	return this->bankManage.getAccounts();
}

vector<string> ManageUser::getLends()
{
	return this->loanManager.getLends();
}

vector<string> ManageUser::getBorrows()
{
	return this->loanManager.getBorrows();
}

void ManageUser::deleteAccountBank(int index)
{
	this->bankManage.deleteAccountBank(index);
}

bool ManageUser::updateBalance(double &money, int index)
{
	index = this->bankManage.updateBalance(money, index);
	if (index < 0)
		return false;
	Transaction ans = this->bankManage.getBank()[index].history[this->bankManage.getBank()[index].history.size() - 1];
	this->transManage.insertTransaction(ans);
	string purpose = ans.purpose;
	purpose = standardize(purpose);
	updatePurpose();
	return true;
}

void ManageUser::reportLoan(bool isLend, int index)
{
	return this->loanManager.reportLoan(isLend, index);
}

void ManageUser::displayPaymentHistory(bool isLend, int index)
{
	if (isLend)
	{
		this->loanManager.displayPaymentHistory(true, index);
	}
	else
	{
		this->loanManager.displayPaymentHistory(false, index);
	}
}
