#include <iostream>
#include "../Utils/Utils.h"

using namespace std;

class Player {
private:
    string name;
    int selection, numWins, numDraw;
public:
    Player(string name) : name(name), selection(0), numDraw(0), numWins(0) {}

    void setSelection(int selection) {
        Player::selection = selection;
    }

    bool operator==(Player p) {
        return this->selection == p.selection;
    }

    // prefix operator for number of draws
    Player &operator++() {
        numDraw++;
        return *this;
    }

    //postfix operator for number of wins
    Player operator++(int) {
        this->numWins++;
        return *this;
    }

    bool operator>(Player p) {
        return (
                (this->selection == 0 && p.selection == 2) ||
                (this->selection == 1 && p.selection == 0) ||
                (this->selection == 2 && p.selection == 1)
        );
    }

    bool operator>=(Player p) {
        return (this->numWins > p.numWins);
    }

    friend istream &operator>>(istream &is, Player &p) {

        p.selection = inputInt(0, 2);
        return is;
    }

    friend ostream &operator<<(ostream &os, Player &p) {

        cout << "Player: " << p.name << ", Number of wins " << p.numWins << endl;
        return os;
    }
};

int rockPaperScrissors() {

    const int maxMoves = 5;

    Player p = Player("Player");
    Player *c = new Player("Computer");

    int numMoves = 0, choice;

    while (numMoves++ < maxMoves) {
        cout << "[0] Scissors\n"
                "[1] Rock\n"
                "[2] Paper\n"
                "Selection Player:";
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
        cout << "Player has won!" << endl;
    } else if (*c >= p) { cout << "Computer has won!" << endl; }
    else { cout << "Draw!!" << endl; }

    return 0;
}