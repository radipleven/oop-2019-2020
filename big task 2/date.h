#ifndef date_header
#define date_header
#include <iostream>
using namespace std;
class Date {
private:
    int year;
    int month;
    int day;

public:
    Date(int year, int month, int day);
    Date();
    Date(string weirdDate);

    int getYear();
    int getMonth();
    int getDay();
    int compareDates(Date date1);
    string getInfo();
    bool inPeriod(Date from, Date to, Date targetDate);
    string currentDate();
    int currentYear();
    int currentMonth();
    int currentDay();
    int getTotalDays();

    bool isValid();
};

#endif
