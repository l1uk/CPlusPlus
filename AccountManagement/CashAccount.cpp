//
// Created by luca on 15/04/23.
//

#include "CashAccount.h"

CashAccount::CashAccount() : Account() {

}

CashAccount::CashAccount(float initialBalance) : Account(initialBalance) {

}

CashAccount::CashAccount(float initialBalance, float initialWithdrawLimit) : Account(initialBalance),
                                                                             withdrawLimit(initialWithdrawLimit) {

}

void CashAccount::setWithdrawLimit(float newLimit) {
    withdrawLimit = newLimit;
}

bool CashAccount::withdraw(float amount) {
    if (amount <= withdrawLimit)
        return Account::withdraw(amount);
    return false;
}
