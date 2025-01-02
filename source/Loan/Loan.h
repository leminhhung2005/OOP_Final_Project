// Class Loan Abstract Data Type

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <math.h>

#include "../Transaction/Transaction.h"
#include "../Date_Time/CheckValidDate.h"
#include "../Date_Time/DateUtils.h"

using namespace std;

// trạng thái thanh toán
enum Status
{
    PENDING,
    PAID_OFF
};

// đơn vị tính lãi
enum TimeUnit
{
    DAYS,
    MONTHS,
    YEARS
};

class Loan
{
protected:
    string partnerName;                 // người cho vay hoặc người vay
    double principalAmount;             // số tiền gốc
    double remainingAmount;             // số tiền còn lại
    std::tm startDate;                  // ngày bắt đầu
    std::tm dueDate;                    // ngày đến hạng
    double interestRate;                // lãi xuất (%)
    TimeUnit interestUnit;              // đơn vị tính lãi
    string notes;                       // ghi chú
    Status status;                      // trạng thái thanh toán
    vector<Transaction> paymentHistory; // lịch sử thanh toán
public:
    // constructor with parameter
    Loan(const string &partnerName, double principalAmount, double remainingAmount, const std::tm &startDate, const std::tm &dueDate, double interestRate, TimeUnit interestUnit, Status status, string notes);

    // destructor
    virtual ~Loan() = default;

    // thêm khoản vay và cho vay mới UI
    virtual void addLoan() = 0;

    // hiện thị danh sách các khoản vay hoặc cho vay UI
    virtual void displayLoan() = 0;

    // thực hiện thanh toán cho vay và vay dành cho UI
    virtual void makePayment() = 0;

    // nhắc nhở khi đến hạn thanh toán dành cho UI
    virtual void remindDueDate() = 0;

    // hiển thị lịch sử thanh toán UI
    virtual void displayPaymentHistory() = 0;

    // tính toán lãi suất UI
    virtual double calculateInterest(bool isCompound, TimeUnit unit);

    // getter
    string getPartnerName() { return partnerName; }

    // getter
    double getPrincipalAmount() { return principalAmount; }

    // getter
    double getRemainingAmount() { return remainingAmount; }

    // getter
    std::tm getStartDate() { return startDate; }

    // getter
    std::tm getDueDate() { return dueDate; }

    // getter
    double getInterestRate() { return interestRate; }

    // getter
    TimeUnit getInterestUnit() { return interestUnit; }

    // getter
    Status getStatus() { return status; }

    // getter
    string getNotes() { return notes; }

    // getter
    vector<Transaction> getPaymentHistory() { return paymentHistory; }

    // setter
    void setpaymentHistory(Transaction &transaction) { paymentHistory.push_back(transaction); }

    // setter
    void setRemainingAmount(double new_remainingAmount) { remainingAmount = new_remainingAmount; }

    // setter
    void setPartnerName(string newname) { this->partnerName = newname; };

    // setter
    void setDueDate(std::tm newdate)
    {
        int time = getDayDifference(newdate, this->dueDate);
        if (time == 0)
        {
            return;
        }

        switch (this->interestUnit)
        {
        case DAYS:
            break;
        case MONTHS:
            time /= 30;
            break;
        case YEARS:
            time /= 365;
            break;
        default:
            cout << "Invalid interest unit!" << endl;
            return;
        }

        this->remainingAmount += (this->principalAmount * time * (this->interestRate / 100.0));
        this->dueDate = newdate;
    }

    // setter
    void setNotes(string newnote) { this->notes = newnote; };
};

Loan::Loan(const string &partnerName, double principalAmount, double remainingAmount, const std::tm &startDate, const std::tm &dueDate, double interestRate, TimeUnit interestUnit, Status status, string notes)
{
    this->partnerName = partnerName;
    this->principalAmount = principalAmount;
    this->remainingAmount = remainingAmount;
    this->startDate = startDate;
    this->dueDate = dueDate;
    this->interestRate = interestRate;
    this->interestUnit = interestUnit;
    this->status = status;
    this->notes = notes;
}

double Loan::calculateInterest(bool isCompound, TimeUnit unit)
{
    int time = getDayDifference(dueDate, startDate);
    switch (unit)
    {
    case DAYS:
        break;
    case MONTHS:
        time /= 30;
        break;
    case YEARS:
        time /= 365;
        break;
    }
    // lãi suất kép
    if (isCompound)
    {
        return principalAmount * pow((1 + interestRate / 100.0), time) - principalAmount;
    }
    // lãi suất đơn
    else
    {
        return principalAmount * time * (interestRate / 100.0);
    }
}
