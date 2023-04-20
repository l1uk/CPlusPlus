//
// Created by luca on 15/04/23.
//
#include "Account.h"
#ifndef C___CURRENTACCOUNT_H
#define C___CURRENTACCOUNT_H


class CurrentAccount : Account {
private:


    int pin;

public:
    bool setPin(int,int);
    bool checkPin(int);

    CurrentAccount();
    CurrentAccount(float initialBalance);
};


#endif //C___CURRENTACCOUNT_H
