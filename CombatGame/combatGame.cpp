//
// Created by Luca on 08/05/2023.
//

#include <string>
#include <iostream>
#include <list>
#include <filesystem>
#include <fstream>
#include "combatGame.h"

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
    int number, height, weight, yearOfBirth, totalPoints, currentGamePoints, numberOfRounds, numWins, numTies, totalNumberOfRounds;
    string name, surname;
public:
    Player(int number, int height, int weight, int yearOfBirth, int points, int numbersOfRounds, const string &name,
           const string &surname, int totalNumberOfRounds, int numWins, int NumTies);

    Player();

    // getters
    int getNumber() const;

    int getNumWins() const;

    int getNumTies() const;

    int getTotalNumberOfRounds() const;

    int getHeight() const;

    int getWeight() const;

    int getYearOfBirth() const;

    int getTotalPoints() const; // Total points = for every game

    int getCurrentGamePoints() const; // Current points = for the ongoing game

    int getNumberOfRounds() const; // numbers of fights in the ongoing game

    const string &getName() const;

    const string &getSurname() const;

    void addPoints(int val) {
        totalPoints += val;
        currentGamePoints += val;
    };

    void incrementRoundsCount() {
        totalNumberOfRounds++;
        numberOfRounds++;
    }

    void incrementsNumWins() {
        numWins++;
    }

    void incrementNumTies() {
        numTies++;
    }

    void resetNumberOfRounds() {
        numberOfRounds = 0;
    }

    void resetPartialPoints() {
        currentGamePoints = 0;
    }; // set point for the game to 0

    // OPERATORS OVERLOADING
    friend istream &operator>>(istream &is, Player &p); // input operator overloading
    friend ostream &operator<<(ostream &os, Player &p); // output operator overloading
    bool operator==(const Player &p) const; // == operator
    bool operator>(const Player &p) const; // > operator
    bool operator<(const Player &p) const; // < operator
    bool operator>=(const Player &p) const; // > operator
    bool operator<=(const Player &p) const; // < operator

    // STATIC MEMBERS

    static const int MAX_FIGHTS = 3;

    static void loadFile(list<Player> &playersList, const filesystem::path &fileName); // loads players from file
    static void saveFile(list<Player> &playersList, const filesystem::path &fileName); // saves players to file

    static void showPlayersList(list<Player *> &playersList); // shows list of pointers to players

    static void showPlayersList(list<Player> &playersList); // shows list of players

    static Player *
    choosePlayerFromList(list<Player *> &playersList,
                         string prompt); // prompt the user to choose from a list of pointer to players


    static bool canPlay(Player *p) {
        return p->getNumberOfRounds() < MAX_FIGHTS;
    }; // returns true if the player can join a new round

    static bool b_has_greaterPoints(Player a, Player b); // function used for finding the max in a Player list
};

class Utilities {
public:
    static void pauseExec();

    static int input_int(int min, int max);

    static void createFileIfNotExists(const filesystem::path &filePath);
};


class Fight {
private:
    Player *p1, *p2, *winner;
    static const int POINTS_VICTORY = 10;
    static const int POINTS_TIE = 5;
    static const int POINTS_LOSS = 0;
public:
    Fight(Player *p1, Player *p2) : p1(p1), p2(p2), winner(nullptr) {}

    void insertResult() {
        // prompt the user fot the insertResult result

        cout << "Result: " << endl;
        cout << "[1] - Player " << p1->getName() << " won & Player " << p2->getName() << "  lost" << endl <<
             "[2] - Player " << p1->getName() << " lost & Player " << p2->getName() << " won" << endl <<
             "[3] - Draw ";
        int choice = Utilities::input_int(1, 3);
        if (choice == 1) {
            winner = p1;
            p1->addPoints(POINTS_VICTORY);
            p2->addPoints(POINTS_LOSS);
            p1->incrementsNumWins();
        } else if (choice == 2) {
            winner = p2;
            p1->addPoints(POINTS_LOSS);
            p2->addPoints(POINTS_VICTORY);
            p2->incrementsNumWins();
        } else {
            p1->addPoints(POINTS_TIE);
            p2->addPoints(POINTS_TIE);
            p1->incrementNumTies();
            p2->incrementNumTies();
        }
        p1->incrementRoundsCount();
        p2->incrementRoundsCount();

    }

    friend ostream &operator<<(ostream &os, Fight &f); // output operator overloading
};

ostream &operator<<(ostream &os, Fight &f) {
    cout << "Fight Statistics: " << endl;
    cout << *f.p1 << "VS" << endl << *f.p2 << endl;
    if (f.winner != nullptr) {
        Player *loser;
        f.p1 == f.winner ? loser = f.p2 : loser = f.p1;
        bool taller = *f.winner >= *loser;
        bool heavier = *f.winner > *loser;
        cout << "Player " << f.winner->getName() << " (Number: " << f.winner->getNumber() << ")" << " has won, he is "
             << abs(f.winner->getHeight() - loser->getHeight())
             << "cm " << (taller ? "taller" : "shorter") << " and "
             << abs(f.winner->getWeight() - loser->getWeight()) << "kg " << (heavier ? "heavier" : "lighter")
             << " than player " << loser->getName() << " (Number: " << loser->getNumber() << ")" << endl;
    } else { cout << "There is no winner! This game ended in a Tie" << endl; }

    return os;
}


class Game {
    // a Game is made of NUM_PLAYERS players, that are stored in an array
    // for every round, the user is prompted to choose two fighters.
    // In order for a insertResult to take place, a Fight object is instantiated and printed.
public:
    Game(Player **players) {
        for (int i = 0; i < NUM_PLAYERS; i++) {
            this->players[i] = *players;
            this->players[i]->resetNumberOfRounds();
            this->players[i]->resetPartialPoints();
            players++;
        }
    }

    void play() {
        Utilities::pauseExec();
        cout << "Welcome to the battle!" << endl;
        bool ended = false;
        while (!ended) {
            Player *fighter1, *fighter2;
            list<Player *> players;
            players.assign(&this->players[0],
                           &(this->players[NUM_PLAYERS])); // copy array of players into temporary list

            int players_that_can_play = // count the players that can play
                    std::count_if(players.begin(), players.end(),
                                  Player::canPlay); // I.E. that not have been playing the maximum number of battles

            if (players_that_can_play < 2) { // there should at least be 2 players that can join a insertResult
                cout << "Game over! There are non more players available at the moment." << endl <<
                     "  Note that the maximum number of rounds per player is " << Player::MAX_FIGHTS << endl << endl;
                Utilities::pauseExec();
                break;
            }

            do { // repeat input until the user has chosen a player that has fought less than 3 battles
                fighter1 = Player::choosePlayerFromList(players, "Choose first fighter");
                if (!Player::canPlay(fighter1)) {
                    cout << "This player has already fought the maximum number of battles!" << endl <<
                         " Please choose another one!" << endl;
                    Utilities::pauseExec();
                }
            } while (!Player::canPlay(fighter1));

            players.remove(fighter1); // players get removed once chosen
            do {
                fighter2 = Player::choosePlayerFromList(players, "Choose second fighter");
                if (!Player::canPlay(fighter2)) {
                    cout << "This player has already fought the maximum number of battles!" << endl <<
                         " Please choose another one!" << endl;
                    Utilities::pauseExec();
                }
            } while (!Player::canPlay(fighter2));
            players.clear();

            Fight f(fighter1, fighter2);
            f.insertResult();
            cout << f << endl;

            Utilities::pauseExec();
            cout << "Next game(0) or quit(1)?: "; // prompting the user whether to quit or go on
            ended = Utilities::input_int(0, 1);
        }
        Player tmp;
        for (int i = NUM_PLAYERS - 1; i >= 0; i--) { // sort the players based on score
            for (int j = 0; j < i; j++) {
                if (this->players[i]->getCurrentGamePoints() > this->players[j]->getCurrentGamePoints()) {
                    tmp = *this->players[i];
                    *this->players[i] = *this->players[j];
                    *this->players[j] = tmp;
                }
            }
        }
    }

    friend ostream &operator<<(ostream &os, Game &g) {
        cout << "Game Results: " << endl << endl;
        for (int i = 0; i < NUM_PLAYERS; i++) {
            cout << *(g.players[i]) << "  Points in this game: " << g.players[i]->getCurrentGamePoints() << endl;
        }
        return os;
    }

    static const int NUM_PLAYERS = 6;
private:
    Player *players[NUM_PLAYERS];

};


void menu(); // prints the menu

// this method is used to create a list of pointers to the first list
void copyObjectReferences(list<Player> &sourceList,
                          list<Player *> &destinationList);

int combatGame() {
    filesystem::path fileName =
            filesystem::current_path().parent_path() / "CombatGame" / "combatGame.txt"; // change file path if necessary
    cout
            << "Welcome to Combat Game Management! Do you want to work with persistent storage? Please check and adjust the file path accordingly to your needs"
            << endl << "Current path: " << fileName << endl <<
            "1 = yes, 0 = no:  ";
    bool fileHandling = Utilities::input_int(0, 1); // this boolean determines wheter the players will be saved or not


    list<Player> playersList;

    if (fileHandling)
        try {
            Utilities::createFileIfNotExists(fileName); // create file if not exists
            Player::loadFile(playersList, fileName); // read file
        }
        catch (string &ex) {
            cout << ex << endl;
            return -1;
        }

    int choice;
    Player p; // temporary variable to store a new player
    do { // program
        menu();
        choice = Utilities::input_int(1, 5);
        switch (choice) {
            case 1: { // create new player and push it in the players' list
                system("cls");
                int duplicates;
                do { // the player needs to have an univoque number, so repeat the input until the number is not already found in the players list
                    cin >> p; // input player

                    // inspiration taken from https://stackoverflow.com/questions/42933943/how-to-use-lambda-for-stdfind-if
                    // (using lambda for this use case is necessary because we need to capture p variable)
                    duplicates = std::count_if(playersList.begin(),
                                               playersList.end(), // count the occurance of players with the same number as the one just inserted
                                               [&p](const Player &x) {
                                                   return p.getNumber() ==
                                                          x.getNumber(); // returns true if the current player (in the list) has the same number as the p parameter (just inserted)
                                               });
                    if (duplicates != 0) { // there should be 0 players with the same number
                        cout
                                << "Attention! There is another player with the same player Number!! Please input the player's data again"
                                << endl;
                    }

                } while (duplicates != 0);

                playersList.push_back(p); // push it into the players list
                cout << endl;
                Utilities::pauseExec();
                break;
            }
            case 2: { // create new Game
                system("cls");
                if (playersList.size() < Game::NUM_PLAYERS) {
                    // check that there are at least 6 players, otherwise the combat game cannot be started
                    cout << "The game requires 6 players, please create them first!" << endl;
                } else { // input 6 players and create game
                    Player *players[Game::NUM_PLAYERS];
                    list<Player *> tempList; // auxiliary list used to make sure that the user cannot choose the same player twice
                    copyObjectReferences(
                            playersList, // a list of pointer is used to always keep a reference to the same objects
                            tempList);  // across all the program

                    for (int i = 0; i < Game::NUM_PLAYERS; i++) {
                        players[i] = Player::choosePlayerFromList(tempList,
                                                                  ("Choose player " + to_string(i + 1)));
                        tempList.remove(players[i]); // players get removed once chosen
                    }
                    tempList.clear();

                    Game g(players); // create a new game
                    g.play(); // play it
                    cout << g; // and print the results

                }
                Utilities::pauseExec();
                break;
            }
            case 3: {
                system("cls");
                Player::showPlayersList(playersList); // show players list
                cout << endl;
                Utilities::pauseExec();
                break;
            }
            case 4: {
                system("cls");
                // inspiration taken from https://www.geeksforgeeks.org/stdmin-in-cpp/
                list<Player>::iterator maxPlayer =
                        max_element(playersList.begin(), playersList.end(), // find the maximum in playersList
                                    Player::b_has_greaterPoints); // according to this method


                cout << *maxPlayer << endl;
                Utilities::pauseExec();
                break;
            }
            default: {
                break;
            }
        }
    } while (choice != 5);

    if (fileHandling)
        try { Player::saveFile(playersList, fileName); }
        catch (string &ex) {
            cout << ex << endl;
            return -1;
        }

    return 0;
}

void menu() {
    cout << "1. Create player - the recording of data is to be done via istream (>>) operator overloading\n"
            "\n"
            "\n"
            "2. Manage combat game (here you enter the players and the results. The totalPoints are awarded dynamically) - after entering the combat data, the winner of the game will be displayed.\n"
            "Operator overloading >= checks, for example, whether the winner was taller and/or heavier than the loser and outputs the determined result, e.g. Player John Doe has won, he is 2 cm taller (shorter) and 7.6 kg heavier (lighter) than player Bob Smith\n"
            "\n"
            "\n"
            "3. Output of all players - the output of the data has to be done via ostream (<<) operator overloading: e.g. John Doe, 1978, 178cm, 88kg, participated in 2 combat games: 1 x won, 1 x tie = 15 totalPoints\n\n"
            "4. Output winner (Player that currently has more points)"
            "\n"
            "\n"
            "5. Program exit" << endl; // copied and pasted from the assignment text
}

// copy a list of objects (first arg) to a list of references to those objects (second arg)
void copyObjectReferences(list<Player> &sourceList, list<Player *> &destinationList) {
    destinationList.clear();
    list<Player>::iterator it = sourceList.begin();
    do {
        destinationList.push_front(&(*it)); // push the address of the current element in the destinationList
        it++;
    } while (it != sourceList.end());
}

void Utilities::pauseExec() {
    system("pause");
    system("cls");
}

void Utilities::createFileIfNotExists(const filesystem::path &filePath) {
    fstream file;
    file.open(filePath, std::ios::out | std::ios::app); // create file if not exists
    file.close();
}

int Utilities::input_int(int min, int max) {
    // reading an int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x;
    std::cin >> x;
    while (std::cin.fail()) {
        std::cout << "Error, please input an integer!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    while (x < min || x > max) {
        std::cout << "Value out of range!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    return x;

}

void Player::saveFile(list<Player> &playersList, const filesystem::path &fileName) {
    ofstream outputFile(fileName, ios::out);
    if (outputFile.good()) {
        list<Player>::iterator it;
        for (it = playersList.begin(); it != playersList.end(); it++) {
            outputFile << it->getNumber() << "\t" << it->getName() << "\t" << it->getSurname() << "\t"
                       << it->getHeight() << "\t" << it->getWeight() << "\t"
                       << it->getYearOfBirth() << "\t"
                       << it->getTotalPoints() << "\t" << it->getNumberOfRounds() << "\t"
                       << it->getTotalNumberOfRounds() << "\t" << it->getNumWins() << "\t" << it->getNumTies() << endl;
        }
    } else {
        throw (string) "Error during file write!";
    }
    outputFile.close();
}

void Player::loadFile(list<Player> &playersList, const filesystem::path &fileName) {
    ifstream inputFile(fileName);
    int number, height, weight, yearOfBirth, points, numberOfFights, totalNumberOfRounds, numWins, numTies;
    string name, surname;
    if (inputFile.good()) {
        while (inputFile >> number >> name >> surname >> height >> weight >> yearOfBirth >> points >> numberOfFights
                         >> totalNumberOfRounds >> numWins >> numTies) {
            playersList.push_back(
                    Player(number, height, weight, yearOfBirth, points, numberOfFights, name, surname,
                           totalNumberOfRounds, numWins, numTies)
            );
        }

    } else {
        throw (string) "Error during file read!";
    }
    inputFile.close();
}

ostream &operator<<(ostream &os, Player &p) {
    cout << "Number: " << p.number << " has partecipated in " << p.totalNumberOfRounds << " fights, having awarded "
         << "("
         << p.numWins
         << " x won, " << p.numTies << " x tie) = " << p.totalPoints << " TotalPoints"
         << endl
         << "\t" << "Name: " << p.name << ", Surname: " << p.surname << ", Weight: " << p.weight
         << "kg, Height: " << p.height << "cm, Birth year: " << p.yearOfBirth << endl;
    return os;
}


istream &operator>>(istream &is, Player &p) {
    cout << "Insert number: ";
    p.number = Utilities::input_int(0, numeric_limits<int>::max());
    cout << "Insert name: ";
    cin >> p.name;
    cout << "Insert surname: ";
    cin >> p.surname;
    cout << "Insert height in cm: ";
    p.height = Utilities::input_int(0, numeric_limits<int>::max());
    cout << "Insert weight in Kg: ";
    p.weight = Utilities::input_int(0, numeric_limits<int>::max());
    cout << "Insert birth year: ";
    p.yearOfBirth = Utilities::input_int(0, numeric_limits<int>::max());
    return is;
}

bool Player::operator==(const Player &p) const {
    return p.totalPoints == totalPoints && p.yearOfBirth == yearOfBirth && p.height == height && p.weight == weight &&
           p.surname == surname && p.name == name && p.number == number && p.numberOfRounds == numberOfRounds;
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

Player *Player::choosePlayerFromList(list<Player *> &playersList, string prompt) {
    showPlayersList(playersList);
    cout << prompt << " (selector # number): ";
    int selection = Utilities::input_int(1, playersList.size());

    list<Player *>::iterator it = playersList.begin(); // declare iterator for the list
    advance(it, selection - 1);// bring the iterator to the desired element
    return (*it); // return player's address
}

Player::Player(int number, int height, int weight, int yearOfBirth, int points, int numbersOfRounds, const string &name,
               const string &surname, int totalNumberOfRounds, int numWins, int numTies) : number(number),
                                                                                           height(height),
                                                                                           weight(weight),
                                                                                           yearOfBirth(yearOfBirth),
                                                                                           totalPoints(points),
                                                                                           numberOfRounds(
                                                                                                   numbersOfRounds),
                                                                                           name(name),
                                                                                           surname(surname),
                                                                                           totalNumberOfRounds(
                                                                                                   totalNumberOfRounds),
                                                                                           numWins(numWins),
                                                                                           numTies(numTies) {}

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

int Player::getTotalPoints() const {
    return totalPoints;
}

int Player::getNumberOfRounds() const {
    return numberOfRounds;
}

const string &Player::getName() const {
    return name;
}

const string &Player::getSurname() const {
    return surname;
}

Player::Player() : totalPoints(0), numberOfRounds(0), totalNumberOfRounds(0), currentGamePoints(0), numWins(0),
                   numTies(0) {}

bool Player::operator>(const Player &p) const {
    return (this->weight > p.weight);
}

bool Player::operator<(const Player &p) const {
    return !((*this) > p);
}

bool Player::operator<=(const Player &p) const {
    return !(*this >= p);
}

bool Player::operator>=(const Player &p) const {
    return (this->height > p.getHeight());
}

int Player::getCurrentGamePoints() const {
    return currentGamePoints;
}

bool Player::b_has_greaterPoints(Player a, Player b) {
    return a.getTotalPoints() < b.getTotalPoints();
}

int Player::getTotalNumberOfRounds() const {
    return totalNumberOfRounds;
}

int Player::getNumWins() const {
    return numWins;
}

int Player::getNumTies() const {
    return numTies;
}


