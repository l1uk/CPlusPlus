#include <iostream>
#include "Account.h"
#include "CurrentAccount.h"
#include "SavingsAccount.h"
#include "CashAccount.h"

int moin() {
    std::cout << std::endl;

    Account a1 = Account();

    CurrentAccount a2 = CurrentAccount((float) 230);

    SavingsAccount a3 = SavingsAccount(200, .5);

    CashAccount a4 = CashAccount(200, 130);

    a1.deposit(102);

    a2.setPin(-1, 144);

    std::cout << a2.checkPin(144) << std::endl;

    std::cout << a4.withdraw(190) << std::endl;

    a1.withdraw(2);

    std::cout << a3.getInterestRate() << std::endl;

    std::cout << Account::accountsCount << std::endl;

    return 0;
}
