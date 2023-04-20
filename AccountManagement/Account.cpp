//
// Created by luca on 15/04/23.
//

#include "Account.h"

int Account::accountsCount = 0;

Account::Account(){
    accountsCount++;
    accountNumber = accountsCount;
}

Account::Account(float initialBalance) {
    balance = initialBalance;
    accountsCount++;
    accountNumber = accountsCount;
}

void Account::deposit(float amount) {
    balance += amount;
}

float Account::getBalance() {
    return balance;
}

bool Account::withdraw(float amount) {
    float newBalance = balance - amount;
    if( newBalance < 0 ){ return false; }
    balance = newBalance;
    return true;
}

int Account::getAccountNumber() {
    return accountNumber;
}


