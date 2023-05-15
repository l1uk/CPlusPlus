//
// Created by Luca on 08/05/2023.
//

#include <string>
#include <iostream>
#include <list>
#include <filesystem>
#include <fstream>
#include "combatGame.h"
#include "../Utils/Utils.h"

using namespace std;

//6 participants (players) take part in the combat game. At least the following data members have to be entered for each player:
//Number (must be unique)
//Surname
//First name
//Height in cm
//Weight in kg
//Points
//Year of birth
class Player {
private:
    int number, height, weight, yearOfBirth, points, numberOfFights;
    string name, surname;
public:
    Player(int number, int height, int weight, int yearOfBirth, int points, int numberOfFights, const string &name,
           const string &surname);

    Player();

    // getters
    int getNumber() const;

    int getHeight() const;

    int getWeight() const;

    int getYearOfBirth() const;

    int getPoints() const;

    int getNumberOfFights() const;

    const string &getName() const;

    const string &getSurname() const;


    // OPERATORS OVERLOADING
    friend istream &operator>>(istream &is, Player &p); // input operator overloading
    friend ostream &operator<<(ostream &os, Player &p); // output operator overloading
    bool operator==(const Player &p) const; // == operator
    bool operator>(const Player &p) const; // > operator
    bool operator<(const Player &p) const; // < operator
    bool operator>=(const Player &p) const; // > operator
    bool operator<=(const Player &p) const; // < operator

    // STATIC MEMBERS
    static void loadFile(list<Player> &playersList, filesystem::path fileName); // loads players from file
    static void saveFile(list<Player> &playersList, filesystem::path fileName); // saves players to file

    static void showPlayersList(list<Player *> &playersList); // shows list of pointers to players

    static void showPlayersList(list<Player> &playersList); // shows list of players

    static Player *
    choosePlayerFromList(list<Player *> &playersList); // prompt the user to choose from a list of pointer to players
};

class Utils {
public:
    static void pauseExec();
};

class Game {
public:
    Game(Player **players) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            this->players[i] = *players;
            players++;
        }
    }

    void play() {
        bool ended = false;
        while (!ended) {
            printPlayers();
            Utils::pauseExec();
        }
    }

    void printPlayers() {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            cout << *(players[i]);
        }
    }

    static const int NUM_PLAYERS = 6;
private:
    Player *players[NUM_PLAYERS];

};;


class Fight {
private:
    Player *p1, *p2;
    bool fought;
public:
    Fight(Player *p1, Player *p2) : p1(p1), p2(p2), fought(false) {}

    void fight() {
        //TODO: implement game logic
    }

    friend ostream &operator<<(ostream &os, Fight &f); // output operator overloading
};


void menu();

void createFileIfNotExists(filesystem::path filePath); // crea

list<Player *>
copyObjectReferences(list<Player> &sourceList); // create a list of pointers to the original list's objects

int combatGame() {
    cout
            << "Welcome to Combat Game Management! Do you want to work with persistent storage? Please check and adjust the file path accordingly to your needs"
            << endl <<
            "1 = yes, 0 = no:  ";
    bool fileHandling = inputInt(0, 1); // this boolean determines wheter the players will be saved or not
    filesystem::path fileName =
            filesystem::current_path().parent_path() / "CombatGame" / "combatGame.dat"; // change file path if necessary

    list<Player> playersList;

    if (fileHandling)
        try {
            createFileIfNotExists(fileName); // create file if not exists
            Player::loadFile(playersList, fileName); // read file
        }
        catch (string ex) {
            cout << ex << endl;
            return -1;
        }

    int choice;
    Player p; // temporary variable to store a new player
    do { // program
        menu();
        choice = inputInt(1, 5);
        switch (choice) {
            case 1: { // create new player and push it in the players' list
                system("cls");
                cin >> p; // input player
                playersList.push_back(p); // push it into the players list
                cout << endl;
                Utils::pauseExec();
                break;
            }
            case 2: {
                system("cls");
                if (playersList.size() < Game::NUM_PLAYERS) {
                    // check that there are at least 6 players, otherwise the combat game cannot be started
                    cout << "The game requires 6 players, please create them first!" << endl;
                } else {
                    Player *players[Game::NUM_PLAYERS];
                    list<Player *> tempList = copyObjectReferences(
                            playersList);// auxiliary list used to make sure that the user cannot choose the same player twice

                    for (int i = 0; i < Game::NUM_PLAYERS; i++) {
                        cout << "Choose player " << i << endl;
                        players[i] = Player::choosePlayerFromList(tempList);
                        tempList.remove(players[i]); // players get removed once chosen
                    }
                    tempList.clear();

                    Game g(players);

                    g.play();
                }
                Utils::pauseExec();
                break;
            }
            case 3: {
                system("cls");
                Player::showPlayersList(playersList); // show players list
                cout << endl;
                Utils::pauseExec();
                break;
            }
        }
    } while (choice != 5);

    if (fileHandling)
        try { Player::saveFile(playersList, fileName); }
        catch (string ex) {
            cout << ex << endl;
            return 0;
        }

    return 0;
}

list<Player *> copyObjectReferences(list<Player> &sourceList) {
    list<Player *> destinationList;
    list<Player>::iterator it = sourceList.begin();
    do {
        destinationList.push_front(&(*it));
        it++;
    } while (it != sourceList.end());
    return destinationList;
}

void pauseExec() {
    system("pause");
    system("cls");
}

void createFileIfNotExists(filesystem::path filePath) {
    fstream file;
    file.open(filePath, std::ios::out | std::ios::app); // create file if not exists
    file.close();
}

void menu() {
    cout << "1. Create player - the recording of data is to be done via istream (>>) operator overloading\n"
            "\n"
            "\n"
            "2. Manage combat game (here you enter the players and the results. The points are awarded dynamically) - after entering the combat data, the winner of the game will be displayed.\n"
            "Operator overloading >= checks, for example, whether the winner was taller and/or heavier than the loser and outputs the determined result, e.g. Player John Doe has won, he is 2 cm taller (shorter) and 7.6 kg heavier (lighter) than player Bob Smith\n"
            "\n"
            "\n"
            "3. Output of all players - the output of the data has to be done via ostream (<<) operator overloading: e.g. John Doe, 1978, 178cm, 88kg, participated in 2 combat games: 1 x won, 1 x tie = 15 points\n\n"
            "4. Output winner"
            "\n"
            "\n"
            "5. Program exit" << endl;
}

void Player::saveFile(list<Player> &playersList, filesystem::path fileName) {
    ofstream outputFile(fileName, ios::out);
    if (outputFile.good()) {
        list<Player>::iterator it;
        for (it = playersList.begin(); it != playersList.end(); it++) {
            outputFile << it->getNumber() << "\t" << it->getName() << "\t" << it->getSurname() << "\t"
                       << it->getHeight() << "\t" << it->getWeight() << "\t"
                       << it->getYearOfBirth() << "\t"
                       << it->getPoints() << "\t" << it->getNumberOfFights() << endl;
        }
    } else {
        throw (string) "Error during file write!";
    }
    outputFile.close();
}

void Player::loadFile(list<Player> &playersList, filesystem::path fileName) {
    ifstream inputFile(fileName);
    int number, height, weight, yearOfBirth, points, numberOfFights;
    string name, surname;
    if (inputFile.good()) {
        while (inputFile >> number >> name >> surname >> height >> weight >> yearOfBirth >> points >> numberOfFights) {
            playersList.push_back(
                    Player(number, height, weight, yearOfBirth, points, numberOfFights, name, surname)
            );
        }

    } else {
        throw (string) "Error during file read!";
    }
    inputFile.close();
}

ostream &operator<<(ostream &os, Player &p) {
    cout << "Number: " << p.number << ", Number of fights: " << p.numberOfFights << ", Points: " << p.points
         << endl
         << "\t" << "Name: " << p.name << ", Surname: " << p.surname << ", Weight: " << p.weight
         << "kg, Height: " << p.height << "cm, Birth year: " << p.yearOfBirth << endl;
    return os;
}


istream &operator>>(istream &is, Player &p) { // TODO: control on univoque player number
    cout << "Insert number: ";
    p.number = inputInt(0, 100);
    cout << "Insert name: ";
    cin >> p.name;
    cout << "Insert surname: ";
    cin >> p.surname;
    cout << "Insert height in cm: ";
    p.height = inputInt(0, 1000);
    cout << "Insert weight in Kg: ";
    p.weight = inputInt(0, 1000);
    cout << "Insert points: ";
    p.points = inputInt(0, 3000);
    cout << "Insert birth year: ";
    p.yearOfBirth = inputInt(0, 3000);
    return is;
}

bool Player::operator==(const Player &p) const {
    return p.points == points && p.yearOfBirth == yearOfBirth && p.height == height && p.weight == weight &&
           p.surname == surname && p.name == name && p.number == number && p.numberOfFights == numberOfFights;
}

void Player::showPlayersList(list<Player *> &playersList) {
    list<Player *>::iterator it;
    int counter = 0;
    for (it = playersList.begin(); it != playersList.end(); it++) {
        cout << "Player #" << ++counter << " - " << **it;
    }
}

void Player::showPlayersList(list<Player> &playersList) {
    list<Player>::iterator it;
    int counter = 0;
    for (it = playersList.begin(); it != playersList.end(); it++) {
        cout << "Player #" << ++counter << " - " << *it;
    }
}

Player *Player::choosePlayerFromList(list<Player *> &playersList) {
    showPlayersList(playersList);
    cout << "Choose one player (selector # number): ";
    int selection = inputInt(1, playersList.size());

    list<Player *>::iterator it = playersList.begin(); // declare iterator for the list
    advance(it, selection - 1);// bring the iterator to the desired element
    return (*it); // return player's address
}

Player::Player(int number, int height, int weight, int yearOfBirth, int points, int numberOfFights, const string &name,
               const string &surname) : number(number), height(height), weight(weight), yearOfBirth(yearOfBirth),
                                        points(points), numberOfFights(numberOfFights), name(name), surname(surname) {}

int Player::getNumber() const {
    return number;
}

int Player::getHeight() const {
    return height;
}

int Player::getWeight() const {
    return weight;
}

int Player::getYearOfBirth() const {
    return yearOfBirth;
}

int Player::getPoints() const {
    return points;
}

int Player::getNumberOfFights() const {
    return numberOfFights;
}

const string &Player::getName() const {
    return name;
}

const string &Player::getSurname() const {
    return surname;
}

Player::Player() : points(0), numberOfFights(0) {}

bool Player::operator>(const Player &p) const {
    return (this->weight > p.weight and this->height > p.height);
}

bool Player::operator<(const Player &p) const {
    return !((*this) > p);
}

bool Player::operator<=(const Player &p) const {
    return (*this < p or *this == p);
}

bool Player::operator>=(const Player &p) const {
    return (*this > p or *this == p);
}


