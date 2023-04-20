//
// Created by luca on 15/04/23.
//

#ifndef C___ACCOUNT_H
#define C___ACCOUNT_H


class Account {
private:
    float balance;
    int accountNumber;
public:
    Account();
    Account(float);
    static int accountsCount;

    float getBalance();
    void deposit(float);
    bool withdraw(float);
    int getAccountNumber();

};


#endif //C___ACCOUNT_H
