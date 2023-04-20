//
// Created by luca on 15/04/23.
//

#ifndef C___SAVINGSACCOUNT_H
#define C___SAVINGSACCOUNT_H


#include "Account.h"

class SavingsAccount : Account{
private:
    float interestRate;

public:
    SavingsAccount();
    SavingsAccount(float balance, float initialIterestRate);
    SavingsAccount(float initialIterestRate);
    void payInterestOn();
    float getInterestRate();
    void setInterestRate(float newRate);
};


#endif //C___SAVINGSACCOUNT_H
