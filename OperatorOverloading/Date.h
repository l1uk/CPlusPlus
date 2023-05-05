//
// Created by Luca on 05/05/2023.
//

#ifndef C___DATE_H
#define C___DATE_H

#include <iostream>

using namespace std;

class Date {
public:
    Date();

private:
    int day, month, year;

    friend istream &operator>>(istream &is, Date &b);
    friend ostream &operator<<(ostream &os, Date &b);

    static int getMaxDay(int month);
};


#endif //C___DATE_H
