// Date Utils Header File

#pragma once
#include <ctime>
#include <iostream>

using namespace std;

// Hàm lấy ngày hiện tại
std::tm getCurrentDate()
{
    std::time_t t = std::time(nullptr); // lấy thời gian hiện tại dưới dạng time_t
    std::tm currentDate;

#ifdef _WIN32 // cách sử dụng với Windows
    localtime_s(&currentDate, &t);
#else // các hệ điều hành khác (Linux, MacOS, ...)
    currentDate = *std::localtime(&t);
#endif

    return currentDate;
}

// tính số ngày chênh lệch giữa 2 ngày
int getDayDifference(const std::tm &date1, const std::tm &date2)
{
    std::tm date1Copy = date1;
    std::tm date2Copy = date2;

    // Đặt giờ, phút, giây thành 0 để chỉ tính đến phần ngày tháng năm
    date1Copy.tm_hour = 0;
    date1Copy.tm_min = 0;
    date1Copy.tm_sec = 0;
    date2Copy.tm_hour = 0;
    date2Copy.tm_min = 0;
    date2Copy.tm_sec = 0;

    // Chuyển std::tm thành time_t để so sánh
    std::time_t time1 = std::mktime(&date1Copy);
    std::time_t time2 = std::mktime(&date2Copy);

    // Kiểm tra lỗi chuyển đổi
    if (time1 == -1 || time2 == -1)
    {
        std::cout << "Loi chuyen doi thoi gian!" << std::endl;
        return 0; // Trả về 0 khi có lỗi
    }

    // Tính số giây chênh lệch và chuyển sang ngày
    double secondsDifference = std::difftime(time1, time2);
    int daysDifference = secondsDifference / (60 * 60 * 24);

    return daysDifference; // Trả về số ngày chênh lệch
}

// so sánh 2 ngày
bool compareDate(const string &startDateStr, const string &dueDateStr)
{
    std::tm startDate = stringChangeDate(startDateStr);
    std::tm dueDate = stringChangeDate(dueDateStr);

    return mktime(&startDate) <= mktime(&dueDate);
}
