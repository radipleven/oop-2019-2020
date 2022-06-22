#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "date.h"
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <time.h>
#include "function.h"
using namespace std;


Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

Date::Date() :Date(currentYear(), currentMonth(), currentDay())
{
}

Date::Date(string weirdDate)
{
    //https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character/10058756
    stringstream test(weirdDate);
    string segment;
    vector<string> seglist;

    while (std::getline(test, segment, '-')) seglist.push_back(segment);

    this->year = Function().strToInt(seglist[0]);
    this->month = Function().strToInt(seglist[1]);
    this->day = Function().strToInt(seglist[2]);
}


int Date::getYear()
{
    return year;
}

int Date::getMonth()
{
    return month;
}

int Date::getDay()
{
    return day;
}


int Date::compareDates(Date date1)
{
    int year1 = date1.getYear();
    int month1 = date1.getMonth();
    int day1 = date1.getDay();

    if (year == year1 && month == month1 && day == day1) return 0;

    if (year < year1) return -1;
    else if (year > year1) return 1;

    if (month < month1) return -1;
    else if (month > month1) return 1;

    if (day < day1) return -1;
    else if (day > day1) return 1;

    return 0;
}

string Date::getInfo()
{
    string y = to_string(year) + "-" + to_string(month) + "-" + to_string(day);
    return y;
}


// Get current date, format is YYYY-MM-DD
string Date::currentDate() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);
    return buf;
}

int Date::currentYear()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y", &tstruct);
    return Function().strToInt(buf);
}

int Date::currentMonth()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%m", &tstruct);
    return Function().strToInt(buf);
}

int Date::currentDay()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%d", &tstruct);
    return Function().strToInt(buf);
}


int Date::getTotalDays()
{
    int DAYS_FOR_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int totalDays = 0;

    for (int y = 0; y < year; y++)
        if (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))  totalDays += 366;
        else totalDays += 365;


    for (int m = 0; m < month; m++) {
        if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) DAYS_FOR_MONTH[1] = 29;
        totalDays += DAYS_FOR_MONTH[m];
    }
    totalDays += day;

    return totalDays;
}

bool Date::isValid() {
    bool isValid = true;

    if (year < 0) isValid = false;
    if (month > 12 || month < 1) isValid = false;
    if (day > 31 || day < 1) isValid = false;

    return isValid;
}
