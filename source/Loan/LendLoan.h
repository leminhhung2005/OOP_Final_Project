// Class LendLoan

#pragma once

#include "Loan.h"
#include "../UI/header.h"

class LendLoan : public Loan
{
public:
    // defaut constructor
    LendLoan();

    // constructor with parameter
    LendLoan(const string &partnerName, double principalAmount, double remainingAmount, const std::tm &startDate, const std::tm &dueDate, double interestRate, TimeUnit interestUnit, Status status, string notes);

    // thêm khoản cho vay UI
    void addLoan() override;

    // thực hiện thanh toán cho vay UI
    void makePayment() override;

    // nhắc nhở thanh toán cho vay UI
    void remindDueDate() override;

    // hiển thị thông tin cho vay UI
    void displayLoan() override;

    // hiển thị lịch sử giao dịch UI
    void displayPaymentHistory();
};

LendLoan::LendLoan() : Loan("", 0, 0, {}, {}, 0, MONTHS, PENDING, "") {};

LendLoan::LendLoan(const string &partnerName, double principalAmount, double remainingAmount, const std::tm &startDate, const std::tm &dueDate, double interestRate, TimeUnit interestUnit, Status status, string notes)
    : Loan(partnerName, principalAmount, remainingAmount, startDate, dueDate, interestRate, interestUnit, status, notes) {};

void LendLoan::addLoan()
{
    string partnerName, startDateStr, dueDateStr, notes;
    double amount, interestRate;
    int unitChoice;
    do
    {
        system("cls");
        printTitle();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        cout << "-------------- Nhập thông tin khoản cho vay --------------" << endl
             << endl;
        SetConsoleTextAttribute(hConsole, 7);
        cout << "Nhập người vay: ";
        getline(cin, partnerName);
    } while (partnerName.empty());
    this->partnerName = partnerName;
    cout << endl;
    cout << "Nhập số tiền cho vay: ";
    string sotien;
    getAmount(sotien, amount);
    this->principalAmount = amount;
    this->remainingAmount = amount;
    cout << endl
         << endl;

    do
    {
        int startLine = getCurrentLine();
        cout << "Nhập ngày bắt đầu theo định dạng (DD/MM/YYYY): ";
        getline(cin, startDateStr);
        if (!isValidDate(startDateStr))
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
    } while (!isValidDate(startDateStr));
    this->startDate = stringChangeDate(startDateStr);
    cout << endl;

    do
    {
        int startLine = getCurrentLine();
        cout << "Nhập hạn trả định theo dạng (DD/MM/YYYY): ";
        getline(cin, dueDateStr);
        if (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), stringChangeDate(startDateStr)) < 0)
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
    } while (!isValidDate(dueDateStr) || getDayDifference(stringChangeDate(dueDateStr), stringChangeDate(startDateStr)) < 0);
    this->dueDate = stringChangeDate(dueDateStr);
    cout << endl;

    std::tm startDate = stringChangeDate(startDateStr);
    std::tm dueDate = stringChangeDate(dueDateStr);

    string laisuat;
    cout << "Nhập lãi suất (%): ";
    getAmount(laisuat, interestRate);
    this->interestRate = interestRate;
    cout << endl<<endl;

    cout << "Chọn đơn vị thời gian tính lãi bạn muốn: " << endl;
    cout << "1. Ngày" << endl;
    cout << "2. Tháng" << endl;
    cout << "3. Năm" << endl;
    do
    {
        int startLine = getCurrentLine();
        cout << "Nhập lựa chọn (1/2/3): ";
        cin >> unitChoice;
        cin.ignore();

        if (unitChoice < 1 || unitChoice > 3)
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "\n-----------------------------------------------------------\n";
            cout << "               Lỗi! Vui lòng nhập lại!\n";
            cout << "-----------------------------------------------------------\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            pause();
            int currentLine = getCurrentLine();
            clearLines2(startLine, currentLine - startLine + 1);
        }

    } while (unitChoice < 1 || unitChoice > 3);
    this->interestUnit = static_cast<TimeUnit>(unitChoice - 1);
    cout << endl;

    char key_choice;
    do
    {
        int startLine = getCurrentLine();
        cout << "Bạn muốn tính lãi theo lãi kép (K) hay lãi đơn (D): ";
        cin >> key_choice;

        if (key_choice != 'K' && key_choice != 'D' && key_choice != 'k' && key_choice != 'd')
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "\n-----------------------------------------------------------\n";
            cout << "               Lỗi! Vui lòng nhập lại!\n";
            cout << "-----------------------------------------------------------\n";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            pause();

            int currentLine = getCurrentLine();
            clearLines2(startLine, currentLine - startLine + 2);
        }

    } while (key_choice != 'K' && key_choice != 'D' && key_choice != 'k' && key_choice != 'd');

    if (key_choice == 'K' || key_choice == 'k')
    {
        setRemainingAmount(remainingAmount + calculateInterest(true, interestUnit));
    }
    else
    {
        setRemainingAmount(remainingAmount + calculateInterest(false, interestUnit));
    }
    cout << "\nSố tiền mà người vay phải trả: " << formatNumber(to_string(remainingAmount)) + " VND" << endl;
    cout << endl;

    cin.ignore();
    cout << "Nhập ghi chú (nếu có): ";
    getline(cin, notes);
    this->notes = notes;
    cout << endl;
}

void LendLoan::makePayment()
{
    if (status == PAID_OFF)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        cout << "\nKhoản cho vay đã được thanh toán hết!" << endl;
        return;
    }

    double amount;
    string date;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "--------------- Nhập thông tin thanh toán ---------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Số tiền người mượn thanh toán: ";
    string sotien;
    getAmount(sotien, amount);
    cout << endl;

    do
    {
        int startLine = getCurrentLine();
        cout << "Nhập ngày thanh toán theo định dạng (DD/MM/YYYY): ";
        getline(cin, date);
        if (!isValidDate(date))
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
    } while (!isValidDate(date));
    cout << endl;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    cout << "--------- Bạn có chắc chắn muốn thêm thanh toán ? ---------" << endl
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
                cout << "          Thêm thanh toán khoản cho vay thành công.\n";
                cout << "-----------------------------------------------------------\n";
                SetConsoleTextAttribute(hConsole, 7);
                Transaction transaction;
                transaction.setTransaction(partnerName, stringChangeDate(date), amount, remainingAmount - amount, "Thanh toan tu nguoi vay");
                paymentHistory.push_back(transaction);

                remainingAmount -= amount;
                if (remainingAmount <= 0)
                {
                    status = PAID_OFF;
                }
                cout << endl;
                return;
            }
            else if (choice == 1)
            {
                cout << endl
                     << endl;
                SetConsoleTextAttribute(hConsole, 4);
                cout << "-----------------------------------------------------------\n";
                cout << "      Thêm thanh toán khoản cho vay không thành công.\n";
                cout << "-----------------------------------------------------------\n";
                SetConsoleTextAttribute(hConsole, 7);
                return;
            }
            break;
        }
        }
    }
}

void LendLoan::remindDueDate()
{
    int daysDiff = getDayDifference(dueDate, getCurrentDate());
    if (status == PAID_OFF)
    {
        return;
    }
    if (daysDiff == 0)
    {
        cout << "   Nhắc nhở: Hôm nay là ngày đến hạn thanh toán nợ của " << partnerName << "!" << endl
             << endl;
    }
    else if (daysDiff <= 31 && daysDiff > 0)
    {
        cout << "   Nhắc nhở: Còn " << daysDiff << " ngày đến hạn thanh toán nợ của " << partnerName << "!" << endl
             << endl;
    }
    else if (daysDiff < 0)
    {
        cout << "   Nhắc nhở: Đã trễ hạn thanh toán nợ của " << partnerName << " " << abs(daysDiff) << " ngày!" << endl
             << endl;
    }
}

void LendLoan::displayLoan()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    cout << "----------------- Thông tin khoản cho vay ----------------" << endl
         << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Tên người vay: " << partnerName << endl
         << endl;

    ostringstream startDateStream, dueDateStream;
    startDateStream << put_time(&startDate, "%d/%m/%Y");
    dueDateStream << put_time(&dueDate, "%d/%m/%Y");

    cout << "Ngày cho vay: " << startDateStream.str() << endl
         << endl;
    cout << "Ngày đến hạn " << dueDateStream.str() << endl
         << endl;
    cout << "Lãi suất: " << fixed << setprecision(2) << interestRate << "%" << endl
         << endl;
    cout << "Số tiền đã cho vay: " << formatNumber(to_string(principalAmount)) + " VND" << endl
         << endl;
    cout << "Số tiền cần thanh toán: " << formatNumber(to_string(remainingAmount)) + " VND" << endl
         << endl;
    cout << "Trạng thái thanh toán: " << (status == PAID_OFF ? "Đã thanh toán" : "Chưa thanh toán") << endl
         << endl;
    cout << "Ghi chú: " << notes << endl
         << endl;
}

void LendLoan::displayPaymentHistory()
{
    if (paymentHistory.empty())
    {
        cout << "Chưa có thanh toán nào hết!";
    }
    else
    {
        cout << "Lịch sử thanh toán: " << endl;
        for (auto &payment : paymentHistory)
        {
            payment.displayTransaction();
        }
    }
}