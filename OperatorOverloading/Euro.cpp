//
// Created by Luca on 05/05/2023.
//

#include "Overloading.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Euro {
public:
    Euro() {}

    Euro(double amount) : euro((int) amount),
                          cent(
                                  ((int) (ceilf((amount - ((int) amount)) * 100)))
                          ) {
    }

    double getAmount() {
        return ((double) euro + ((double) cent / 100));
    }

    void output() {
        cout << euro << ".";
        if (cent < 10) { cout << "0"; }
        cout << cent << endl;
    }

private:
    int euro;
    int cent;
};

Euro operator+(Euro &a, Euro &b) {
    return Euro((double) a.getAmount() + b.getAmount());
}

Euro operator-(Euro &a, Euro &b) {
    return Euro(a.getAmount() - b.getAmount());
}

Euro operator*(Euro &a, double &b) {
    return Euro((double) a.getAmount() * b);
}

int euro() {
    Euro myMoney(100.80), yourMoney(45.30), fine(25.80), ourMoney;
    double interestrate = 3.5;
    ourMoney = myMoney + yourMoney;
    ourMoney.output();
    ourMoney = ourMoney - fine;
    ourMoney.output();
    ourMoney = ourMoney * (interestrate);
    ourMoney.output();

    system("pause");
    return 0;
}