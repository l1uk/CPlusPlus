//
// Created by Luca on 05/05/2023.
//

#include <limits>
#include <iomanip>
#include "Date.h"
#include "../Utils/Utils.h"

int Date::getMaxDay(int month) {
    int numDays = 31;
    switch (month) {
        case (2): {
            numDays = 28;
            break;
        }
        case (4):
        case (6):
        case (9):
        case (11): {
            numDays = 30;
            break;
        }
    }
    return numDays;
}

istream &operator>>(istream &is, Date &b) {
    cout << "Insert month: ";
    b.month = inputInt(1, 12);
    cout << "Insert day: ";
    int maxDay = Date::getMaxDay(b.month);
    b.day = inputInt(1, maxDay);
    cout << "Insert year: ";
    b.year = inputInt(0, numeric_limits<int>::max());
    return is;
}

Date::Date() {}

ostream &operator<<(ostream &os, Date &b) {
    cout << setw(2) << setfill('0') << b.day << "." << setw(2) << setfill('0') << b.month << "."
         << setw(4) << setfill('0') << b.year << endl;
    return os;
}


