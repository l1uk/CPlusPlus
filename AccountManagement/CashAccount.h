//
// Created by luca on 15/04/23.
//

#ifndef C___CASHACCOUNT_H
#define C___CASHACCOUNT_H


#include "Account.h"

class CashAccount : Account {
public:
    CashAccount();

    CashAccount(float initialBalance);

    CashAccount(float initialBalance, float initialWithdrawLimit);

    void setWithdrawLimit(float newLimit);

    bool withdraw(float amount);

private:
    float withdrawLimit;

};


#endif //C___CASHACCOUNT_H
