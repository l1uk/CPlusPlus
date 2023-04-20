//
// Created by luca on 15/04/23.
//

#include "SavingsAccount.h"

SavingsAccount::SavingsAccount() : Account() {

}

SavingsAccount::SavingsAccount(float balance, float initialIterestRate) : Account(balance), interestRate(initialIterestRate) {
}

SavingsAccount::SavingsAccount(float initialIterestRate) : Account(), interestRate(initialIterestRate) {
}

void SavingsAccount::payInterestOn() {

}

void SavingsAccount::setInterestRate(float newRate) {
    interestRate = newRate;
}

float SavingsAccount::getInterestRate() {
    return interestRate;
}
