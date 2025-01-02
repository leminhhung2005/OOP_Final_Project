// Class Loan Manager

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <functional>
#include <memory>

#include "../Loan/Loan.h"
#include "../Loan/LendLoan.h"
#include "../Loan/BorrowLoan.h"
#include "../UI/header.h"

using namespace std;

class LoanManager
{
private:
    vector<shared_ptr<Loan>> lends;   // khoản cho vay
    vector<shared_ptr<Loan>> borrows; // khoản vay

public:
    // đọc file
    void loadFromFile(const string &filename);

    // ghi file
    void writeToFile(const string &filename);

    // thêm các khoản cho vay/vay dành cho UI
    void addLoan(bool isLend);

    // xóa các khoản cho vay/vay dành cho UI
    void deleteLoan(bool isLend, int choice);

    // cập nhật khoản cho vay/vay dành cho UI
    void updateLoan(bool isLend, int choice);

    // thực hiện thanh toán vay hoặc cho vay dành cho UI
    void makePayment(bool isLend, int index);

    // báo cáo khoản vay và cho vay tổng thể dành cho UI
    void generateReport();

    // báo cáo khoản vay và cho vay chi tiết dành cho UI
    void generateReportAll();

    // báo cáo khoản vay và cho vay danh cho UI
    void reportLoan(bool isLend, int index);

    // hiển thị lịch sử thanh toán dành cho UI
    void displayPaymentHistory(bool isLend, int index);

    // lọc danh sách khoản vay hoặc cho vay theo thời gian dành cho UI
    void filterLoan(const std::tm timeStart, const std::tm timeEnd);

    // lọc danh sách thanh toán theo thời gian dành cho UI
    void filterPayment(const std::tm timeStart, const std::tm timeEnd);

    void remindDueDate();

    // lấy danh sách khoản cho vay dành cho UI
    vector<string> getLends();

    // lấy danh sách khoản vay dành cho UI
    vector<string> getBorrows();

    // lấy thông tin cho vay theo index
    string getLendWithIndex(int index);

    // lấy thông tin vay theo index
    string getBorrowWithIndex(int index);
};

void LoanManager::loadFromFile(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cout << "Không thể mở file được" << endl;
        return;
    }
    string line;
    string partnerName, startDateStr, endDateStr, notes, statusStr, interestUnit, type = "";
    double amount, remaining, interestRate;
    while (getline(inputFile, line))
    {
        if (type == "")
        {
            type = line;
            getline(inputFile, partnerName);
        }
        else
        {
            partnerName = line;
        }
        inputFile >> amount;
        inputFile >> remaining;
        inputFile.ignore();

        getline(inputFile, startDateStr);
        std::tm start_date = stringChangeDate(startDateStr);

        getline(inputFile, endDateStr);
        std::tm end_date = stringChangeDate(endDateStr);

        inputFile >> interestRate;
        inputFile.ignore();

        getline(inputFile, interestUnit);
        TimeUnit loan_unit;
        if (interestUnit == "DAYS")
        {
            loan_unit = DAYS;
        }
        else if (interestUnit == "MONTHS")
        {
            loan_unit = MONTHS;
        }
        else
        {
            loan_unit = YEARS;
        }

        getline(inputFile, statusStr);
        Status loan_status = (statusStr == "PAID_OFF") ? PAID_OFF : PENDING;
        getline(inputFile, notes);
        if (type == "Lend")
        {
            auto lendLoan = make_shared<LendLoan>(partnerName, amount, remaining, start_date, end_date, interestRate, loan_unit, loan_status, notes);
            lends.push_back(lendLoan);
            while (getline(inputFile, line) && !inputFile.eof())
            {
                if (line == "Lend" || line == "Borrow")
                {
                    type = line;
                    break;
                }

                string paymentDetails = line;
                string partner_name = "", dateStr, description = "";
                double amountPaid, remainingAmount;

                stringstream ss(paymentDetails);
                string word;
                vector<string> words;

                while (ss >> word)
                {
                    words.push_back(word);
                }
                int pos = 0;
                while (pos < words.size())
                {
                    if (isalpha(words[pos][0]))
                    {
                        partner_name += words[pos] + " ";
                        pos++;
                    }
                    else
                        break;
                }
                dateStr = words[pos++];
                std::tm paymentDate = stringChangeDate(dateStr);

                amountPaid = stod(words[pos++]);
                remainingAmount = stod(words[pos++]);
                lendLoan->setRemainingAmount(remainingAmount);
                while (pos < words.size())
                {
                    description += words[pos++] + " ";
                }

                Transaction transaction;
                transaction.setTransaction(partner_name, paymentDate, amountPaid, remainingAmount, description);
                lendLoan->setpaymentHistory(transaction);
            }
        }
        else
        {
            auto borrowLoan = make_shared<BorrowLoan>(partnerName, amount, remaining, start_date, end_date, interestRate, loan_unit, loan_status, notes);
            borrows.push_back(borrowLoan);
            while (getline(inputFile, line) && !inputFile.eof())
            {
                if (line == "Lend" || line == "Borrow")
                {
                    type = line;
                    break;
                }

                string paymentDetails = line;
                string partner_name = "", dateStr, description = "";
                double amountPaid, remainingAmount;

                stringstream ss(paymentDetails);
                string word;
                vector<string> words;

                while (ss >> word)
                {
                    words.push_back(word);
                }
                int pos = 0;
                while (pos < words.size())
                {
                    if (isalpha(words[pos][0]))
                    {
                        partner_name += words[pos] + " ";
                        pos++;
                    }
                    else
                        break;
                }
                dateStr = words[pos++];
                std::tm paymentDate = stringChangeDate(dateStr);

                amountPaid = stod(words[pos++]);
                remainingAmount = stod(words[pos++]);
                borrowLoan->setRemainingAmount(remainingAmount);

                while (pos < words.size())
                {
                    description += words[pos++] + " ";
                }

                Transaction transaction;
                transaction.setTransaction(partner_name, paymentDate, amountPaid, remainingAmount, description);
                borrowLoan->setpaymentHistory(transaction);
            }
        }
    }
    inputFile.close();
}

void LoanManager::writeToFile(const string &filename)
{
    ofstream outputFile(filename);
    if (!outputFile)
    {
        cout << "Không thể mở file để ghi!" << endl;
        return;
    }
    for (auto &lend : lends)
    {
        outputFile << "Lend\n";
        outputFile << lend->getPartnerName() << "\n";
        outputFile << lend->getPrincipalAmount() << "\n";
        outputFile << lend->getRemainingAmount() << "\n";
        outputFile << dateChangeString(lend->getStartDate()) << "\n";
        outputFile << dateChangeString(lend->getDueDate()) << "\n";
        outputFile << lend->getInterestRate() << "\n";

        TimeUnit unit = lend->getInterestUnit();
        outputFile << (unit == DAYS ? "DAYS" : (unit == MONTHS ? "MONTHS" : "YEARS")) << "\n";

        Status status = lend->getStatus();
        outputFile << (status == PAID_OFF ? "PAID_OFF" : "PENDING") << "\n";

        outputFile << lend->getNotes() << "\n";

        vector<Transaction> paymentHistory = lend->getPaymentHistory();
        for (const auto &transaction : paymentHistory)
        {
            outputFile << transaction.nameBank << " "
                       << dateChangeString(transaction.date) << " "
                       << transaction.amount << " "
                       << transaction.balance << " "
                       << transaction.purpose << "\n";
        }
    }

    for (auto &borrow : borrows)
    {
        outputFile << "Borrow\n";
        outputFile << borrow->getPartnerName() << "\n";
        outputFile << borrow->getPrincipalAmount() << "\n";
        outputFile << borrow->getRemainingAmount() << "\n";
        outputFile << dateChangeString(borrow->getStartDate()) << "\n";
        outputFile << dateChangeString(borrow->getDueDate()) << "\n";
        outputFile << borrow->getInterestRate() << "\n";

        TimeUnit unit = borrow->getInterestUnit();
        outputFile << (unit == DAYS ? "DAYS" : (unit == MONTHS ? "MONTHS" : "YEARS")) << "\n";

        Status status = borrow->getStatus();
        outputFile << (status == PAID_OFF ? "PAID_OFF" : "PENDING") << "\n";

        outputFile << borrow->getNotes() << "\n";

        const vector<Transaction> paymentHistory = borrow->getPaymentHistory();
        for (auto &transaction : paymentHistory)
        {
            outputFile << transaction.nameBank << " "
                       << dateChangeString(transaction.date) << " "
                       << transaction.amount << " "
                       << transaction.balance << " "
                       << transaction.purpose << "\n";
        }
    }

    outputFile.close();
}

void LoanManager::filterLoan(const std::tm timeStart, const std::tm timeEnd)
{
    if (this->lends.empty() && this->borrows.empty())
    {
        cout << "Chưa có khoản vay và cho vay\n";
    }
    else
    {
        bool check = false;
        for (int i = 0; i < this->lends.size(); i++)
        {
            if (getDayDifference(lends[i]->getStartDate(), timeStart) >= 0 && getDayDifference(lends[i]->getStartDate(), timeEnd) <= 0)
            {
                this->reportLoan(true, i);
                check = true;
            }
        }

        for (int i = 0; i < this->borrows.size(); i++)
        {
            if (getDayDifference(borrows[i]->getStartDate(), timeStart) >= 0 && getDayDifference(borrows[i]->getStartDate(), timeEnd) <= 0)
            {
                this->reportLoan(false, i);
                check = true;
            }
        }

        if (check == false)
        {
            cout << "Không có khoản vay hay cho vay nào trong khoảng thời gian: ";
            printDate(timeStart);
            cout << " - ";
            printDate(timeEnd);
            cout << endl;
        }
    }
}

void LoanManager::updateLoan(bool isLend, int choice)
{
    if (isLend)
    {

        vector<string> choiceItems = {"Tên người cho vay", "Ngày đến hạn", "Ghi chú", "Quay lại trang trước"};
        int choice1 = 0;
        bool exit = false;
        while (!exit)
        {
            system("cls");
            printTitle();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << getLendWithIndex(choice) << endl
                 << endl;
            displayMenu(choiceItems, choice1);
            int keyInput = _getch();
            switch (keyInput)
            {
            case KEY_UP:
                choice1 = (choice1 - 1 + choiceItems.size()) % choiceItems.size();
                break;
            case KEY_DOWN:
                choice1 = (choice1 + 1) % choiceItems.size();
                break;
            case KEY_ENTER:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n ---------------- Nhập thông tin cập nhật ---------------" << endl
                     << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                if (choice1 == 0)
                {
                    string newname;
                    do
                    {
                        system("cls");
                        printTitle();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "\n ---------------- Nhập thông tin cập nhật ---------------" << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        cout << "Nhập tên người cho vay mới: ";
                        getline(cin, newname);
                    } while (newname.empty());

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->lends[choice]->setPartnerName(newname);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản cho vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản cho vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 1)
                {
                    string dueDateStr;
                    do
                    {
                        int startLine = getCurrentLine();
                        cout << "Nhập hạn trả mới theo định dạng (DD/MM/YYYY): ";
                        getline(cin, dueDateStr);
                        if (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), lends[choice]->getStartDate()) < 0)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                            cout << "-----------------------------------------------------------\n";
                            cout << "               Lỗi! Vui lòng nhập lại!\n";
                            cout << "-----------------------------------------------------------\n";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            pause();
                            int currentLine = getCurrentLine();
                            clearLines2(startLine, currentLine - startLine + 1);
                        }
                    } while (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), lends[choice]->getStartDate()) < 0);

                    std::tm newdate = stringChangeDate(dueDateStr);

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->lends[choice]->setDueDate(newdate);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản cho vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản cho vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 2)
                {
                    string newnote;
                    cout << "Nhập ghi chú mới: ";
                    getline(cin, newnote);

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->lends[choice]->setNotes(newnote);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản cho vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản cho vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 3)
                {
                    exit = true;
                }
                break;
            }
        }
    }
    else
    {
        vector<string> choiceItems = {"Tên người vay", "Ngày đến hạn", "Ghi chú", "Quay lại trang trước"};
        int choice1 = 0;
        bool exit = false;
        while (!exit)
        {
            system("cls");
            printTitle();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            cout << getBorrowWithIndex(choice) << endl
                 << endl;
            displayMenu(choiceItems, choice1);
            int keyInput = _getch();
            switch (keyInput)
            {
            case KEY_UP:
                choice1 = (choice1 - 1 + choiceItems.size()) % choiceItems.size();
                break;
            case KEY_DOWN:
                choice1 = (choice1 + 1) % choiceItems.size();
                break;
            case KEY_ENTER:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                cout << "\n ----------------- Nhập thông tin cập nhật ----------------" << endl
                     << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                if (choice1 == 0)
                {
                    string newname;
                    do
                    {
                        system("cls");
                        printTitle();
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "\n ---------------- Nhập thông tin cập nhật ---------------" << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                        cout << "Nhập tên người cho vay mới: ";
                        getline(cin, newname);
                    } while (newname.empty());

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->borrows[choice]->setPartnerName(newname);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 1)
                {
                    string dueDateStr;
                    do
                    {
                        int startLine = getCurrentLine();
                        cout << "Nhập hạn trả mới theo định dạng (DD/MM/YYYY): ";
                        getline(cin, dueDateStr);
                        if (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), borrows[choice]->getStartDate()) < 0)
                        {
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                            cout << "-----------------------------------------------------------\n";
                            cout << "               Lỗi! Vui lòng nhập lại!\n";
                            cout << "-----------------------------------------------------------\n";
                            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                            pause();
                            int currentLine = getCurrentLine();
                            clearLines2(startLine, currentLine - startLine + 1);
                        }
                    } while (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), borrows[choice]->getStartDate()) < 0);

                    std::tm newdate = stringChangeDate(dueDateStr);

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->borrows[choice]->setDueDate(newdate);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 2)
                {
                    string newnote;
                    cout << "Nhập ghi chú mới: ";
                    getline(cin, newnote);

                    if (confirmUpdate())
                    {
                        cout << endl
                             << endl;
                        this->borrows[choice]->setNotes(newnote);
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                        cout << "-----------------------------------------------------------\n";
                        cout << "             Cập nhật khoản vay thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    else
                    {
                        cout << endl
                             << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << "-----------------------------------------------------------\n";
                        cout << "          Cập nhật khoản vay không thành công.\n";
                        cout << "-----------------------------------------------------------\n";
                    }
                    pause();
                }
                else if (choice1 == 3)
                {
                    exit = true;
                }
                break;
            }
        }
    }
}

void LoanManager::remindDueDate()
{
    bool hasDueLoans = false;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    for (auto lend : lends)
    {
        lend->remindDueDate();
    }
    for (auto borrow : borrows)
    {
        borrow->remindDueDate();
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void LoanManager::deleteLoan(bool isLend, int choice)
{
    if (isLend)
    {
        if (choice < 0 || choice >= this->lends.size())
        {
            throw std::out_of_range("Index out of range for lends");
        }

        this->lends.erase(this->lends.begin() + (choice));
    }
    else
    {
        if (choice < 0 || choice >= this->borrows.size())
        {
            throw std::out_of_range("Index out of range for lends");
        }
        this->borrows.erase(this->borrows.begin() + (choice));
    }
}

void LoanManager::addLoan(bool isLend)
{
    if (isLend == true)
    {
        auto loan = make_shared<LendLoan>();
        loan->addLoan();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "--------- Bạn có chắc chắn muốn thêm khoản cho vay ? ---------" << endl
             << endl;
        vector<string> choiceItems = {"Chắc chắn", "Không"};
        int choice = 0;
        int keyInput;
        int startLine = getCurrentLine();
        while (true)
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
                    cout << "               Thêm khoản cho vay thành công.\n";
                    cout << "-----------------------------------------------------------\n";
                    SetConsoleTextAttribute(hConsole, 7);
                    pause();
                    lends.push_back(loan);
                    return;
                }
                else if (choice == 1)
                {
                    cout << endl
                         << endl;
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << "-----------------------------------------------------------\n";
                    cout << "           Thêm khoản cho vay không thành công.\n";
                    cout << "-----------------------------------------------------------\n";
                    SetConsoleTextAttribute(hConsole, 7);
                    pause();
                    return;
                }
                break;
            }
            }
        }
    }
    else
    {
        auto loan = make_shared<BorrowLoan>();
        loan->addLoan();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "--------- Bạn có chắc chắn muốn thêm khoản cho vay ? ---------" << endl
             << endl;
        vector<string> choiceItems = {"Chắc chắn", "Không"};
        int choice = 0;
        int keyInput;
        int startLine = getCurrentLine();
        while (true)
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
                    cout << "                 Thêm khoản vay thành công.\n";
                    cout << "-----------------------------------------------------------\n";
                    SetConsoleTextAttribute(hConsole, 7);
                    pause();
                    borrows.push_back(loan);
                    return;
                }
                else if (choice == 1)
                {
                    cout << endl
                         << endl;
                    SetConsoleTextAttribute(hConsole, 10);
                    cout << "-----------------------------------------------------------\n";
                    cout << "              Thêm khoản vay không thành công.\n";
                    cout << "-----------------------------------------------------------\n";
                    SetConsoleTextAttribute(hConsole, 7);
                    pause();
                    return;
                }
                break;
            }
            }
        }
    }
}

void LoanManager::makePayment(bool isLend, int index)
{
    if (isLend)
    {
        lends[index]->makePayment();
    }
    else
    {
        borrows[index]->makePayment();
    }
}

void LoanManager::generateReport()
{
    double totalLendAmount = 0, totalBorrowAmount = 0;
    int paidLends = 0, unpaidLends = 0;
    int paidBorrows = 0, unpaidBorrows = 0;
    for (auto &lend : lends)
    {
        totalLendAmount += lend->getPrincipalAmount();

        if (lend->getStatus() == PAID_OFF)
            paidLends++;
        else
            unpaidLends++;
    }
    for (auto &borrow : borrows)
    {
        totalBorrowAmount += borrow->getPrincipalAmount();

        if (borrow->getStatus() == PAID_OFF)
            paidBorrows++;
        else
            unpaidBorrows++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "\n-------------------- Thống kê tổng hợp -------------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << "Tổng số tiền cho vay: " << formatNumber(to_string(totalLendAmount)) + " VND" << endl
         << endl;
    cout << "Tổng số tiền vay: " << formatNumber(to_string(totalBorrowAmount)) + " VND" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "----------------------------------------------------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Số lượng khoản cho vay đã thanh toán: " << paidLends << endl
         << endl;
    cout << "Số lượng khoản cho vay chưa thanh toán: " << unpaidLends << endl
         << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "----------------------------------------------------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Số lượng khoản vay đã thanh toán: " << paidBorrows << endl
         << endl;
    cout << "Số lượng khoản vay chưa thanh toán: " << unpaidBorrows << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "----------------------------------------------------------" << endl;
}

void LoanManager::generateReportAll()
{

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "--------------- Danh sách các khoản cho vay ---------------" << endl
         << endl;
    if (lends.empty())
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Danh sách khoản cho vay rỗng!";
    }
    int i = 1;
    for (auto &lend : lends)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << i++ << ".";
        lend->displayLoan();
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "------------------- Danh sách các khoản vay -------------------" << endl
         << endl;
    if (borrows.empty())
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Danh sách các khoản vay rỗng!";
    }
    int j = 1;
    for (auto &borrow : borrows)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        cout << j++ << ".";
        borrow->displayLoan();
    };
}

void LoanManager::reportLoan(bool isLend, int index)
{
    if (isLend)
    {
        lends[index]->displayLoan();
    }
    else
    {
        borrows[index]->displayLoan();
    }
}

void LoanManager::displayPaymentHistory(bool isLend, int index)
{
    if (isLend)
    {
        lends[index]->displayPaymentHistory();
    }
    else
    {
        borrows[index]->displayPaymentHistory();
    }
}

void LoanManager::filterPayment(const std::tm timeStart, const std::tm timeEnd)
{
    bool found1 = false;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "---------- Giao dịch thanh toán khoản cho vay ----------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    for (auto &lend : lends)
    {
        for (auto &payment : lend->getPaymentHistory())
        {
            std::tm paymentDate = payment.date;
            if (getDayDifference(timeStart, paymentDate) <= 0 && getDayDifference(timeEnd, paymentDate) >= 0)
            {
                found1 = true;
                payment.displayTransaction();
            }
        }
    }

    if (!found1)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Không có khoản cho vay nào trong khoảng thời gian: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printDate(timeStart);
        cout << " - ";
        printDate(timeEnd);
        cout << endl;
    }
    cout << endl;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "------------ Giao dịch thanh toán khoản vay ------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    bool found2 = false;
    for (auto &borrow : borrows)
    {
        for (auto &payment : borrow->getPaymentHistory())
        {
            std::tm paymentDate = payment.date;
            if (getDayDifference(timeStart, paymentDate) <= 0 && getDayDifference(timeEnd, paymentDate) >= 0)
            {
                found2 = true;
                payment.displayTransaction();
            }
        }
    }

    if (!found2)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "Không có khoản vay nào trong khoảng thời gian: ";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printDate(timeStart);
        cout << " - ";
        printDate(timeEnd);
        cout << endl;
    }
}

vector<string> LoanManager::getLends()
{
    vector<string> lendInfo;
    for (auto &lend : this->lends)
    {
        string partnerName = lend->getPartnerName();
        double principalAmount = lend->getPrincipalAmount(), remainingAmount = lend->getRemainingAmount();
        string startDate = dateChangeString(lend->getStartDate());
        string dueDate = dateChangeString(lend->getDueDate());
        Status status = lend->getStatus();
        string loanDetails = "Khoản cho vay: " + partnerName + " - Hạn trả: " + dueDate + " - Trạng thái: " + (status == PAID_OFF ? "Đã thanh toán" : "Chưa thanh toán");
        lendInfo.push_back(loanDetails);
    }
    return lendInfo;
}

vector<string> LoanManager::getBorrows()
{
    vector<string> borrowInfo;
    for (auto &lend : this->borrows)
    {
        string partnerName = lend->getPartnerName();
        double principalAmount = lend->getPrincipalAmount(), remainingAmount = lend->getRemainingAmount();
        string startDate = dateChangeString(lend->getStartDate());
        string dueDate = dateChangeString(lend->getDueDate());
        Status status = lend->getStatus();
        string loanDetails = "Khoản vay: " + partnerName + " - Hạn trả: " + dueDate + " - Trạng thái: " + (status == PAID_OFF ? "Đã thanh toán" : "Chưa thanh toán");
        borrowInfo.push_back(loanDetails);
    }
    return borrowInfo;
}

string LoanManager::getLendWithIndex(int index)
{
    string loanDetails = "Khoản cho vay: " + lends[index]->getPartnerName() + " - Hạn trả: " + dateChangeString(lends[index]->getDueDate()) + " - Trạng thái: " + (lends[index]->getStatus() == PAID_OFF ? "Đã thanh toán" : "Chưa thanh toán");
    return loanDetails;
}

string LoanManager::getBorrowWithIndex(int index)
{
    string loanDetails = "Khoản vay: " + borrows[index]->getPartnerName() + " - Hạn trả: " + dateChangeString(borrows[index]->getDueDate()) + " - Trạng thái: " + (borrows[index]->getStatus() == PAID_OFF ? "Đã thanh toán" : "Chưa thanh toán");
    return loanDetails;
}
