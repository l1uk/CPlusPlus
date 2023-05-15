#include <iostream>
#include "../Utils/Utils.h"

using namespace std;

class Gamer {
private:
    string name;
    int selection, numWins, numDraw;
public:
    Gamer(string name) : name(name), selection(0), numDraw(0), numWins(0) {}

    void setSelection(int selection) {
        Gamer::selection = selection;
    }

    bool operator==(Gamer p) {
        return this->selection == p.selection;
    }

    // prefix operator for number of draws
    Gamer &operator++() {
        numDraw++;
        return *this;
    }

    //postfix operator for number of wins
    Gamer operator++(int) {
        this->numWins++;
        return *this;
    }

    bool operator>(Gamer p) {
        return (
                (this->selection == 0 && p.selection == 2) ||
                (this->selection == 1 && p.selection == 0) ||
                (this->selection == 2 && p.selection == 1)
        );
    }

    bool operator>=(Gamer p) {
        return (this->numWins > p.numWins);
    }

    friend istream &operator>>(istream &is, Gamer &p) {

        p.selection = inputInt(0, 2);
        return is;
    }

    friend ostream &operator<<(ostream &os, Gamer &p) {

        cout << "Gamer: " << p.name << ", Number of wins " << p.numWins << endl;
        return os;
    }
};

int rockPaperScrissors() {

    const int maxMoves = 5;

    Gamer p = Gamer("Gamer");
    Gamer *c = new Gamer("Computer");

    int numMoves = 0, choice;

    while (numMoves++ < maxMoves) {
        cout << "[0] Scissors\n"
                "[1] Rock\n"
                "[2] Paper\n"
                "Selection Gamer:";
        cin >> p;
        c->setSelection(getRandomNumber(0, 2));
        // if player and computer made the same choice, increment their draw count
        if (p == *c) {
            ++p;
            ++(*c);
        } else if (p > *c) { // else if player wins increment player win count
            p++;
        } else { (*c)++; } // else computer win count

        cout << p;
        cout << *c;
    }

    if (p >= *c) {
        cout << "Gamer has won!" << endl;
    } else if (*c >= p) { cout << "Computer has won!" << endl; }
    else { cout << "Draw!!" << endl; }

    return 0;
}