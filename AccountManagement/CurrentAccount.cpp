//
// Created by luca on 15/04/23.
//

#include "CurrentAccount.h"

bool CurrentAccount::setPin(int oldPin, int newPin) {
    if(pin != oldPin){ return false; }

    pin = newPin;

    return true;
}

bool CurrentAccount::checkPin(int pinToCheck) {
    return pinToCheck == pin;
}

CurrentAccount::CurrentAccount(float amount) : Account(amount),pin(-1){
}

CurrentAccount::CurrentAccount() : Account(),pin(-1) {

}