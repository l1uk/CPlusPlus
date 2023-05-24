//
//A player is to fight a total of 3 monsters to find a treasure.
//
//Create a class "Creature" that has the data members "healthPoints" and "damage".
//Create a subclass "Gamer" that additionally has the data member "potionOfLife".
//
//The player has 100 life totalPoints at the beginning and one potion to use.
//
//A menu is to appear which always displays the player's current healthPoints.
//The following options are available:
//
//- Attack
//	A new monster (creature) appears whose number of healthPoints is random (between 30 and 50).
//	--> Always create a new object of the type "Creature" and assign it to the dynamic object.
//	The player's and the monster's healthPoints are displayed.
//	The attack damage is determined by a random number (between 10 and 20).
//	The player attacks the monster first.
//	If the monster has less than 1 healthPoints, the message that it has died appears.
//	If the monster is not dead, the monster will then attack the player.
//	If the player has less than 1 healthPoints, the message that he has died appears and how many creatures he has defeated already.
//
//- Drink Potion of Life
//	The number of the player's healthPoints increase (randomly between 20 and 30)
//	The potionOfLife can only be used once.
//
//- Flee
//	The player runs away [program exits]. The number of defeated creatures is displayed.
//
//If the player has defeated 3 creatures, the message appears that he has found the treasure [program exits].
//If no potionOfLife has been used, the message appears that the player is a "true hero".
//
//Hint:
//
//Include the library <ctime>.
//A random number is created as follows:
//
//srand(time(NULL)); // Random number re-initialized based on time, so that not always the same values occur
//int randomNumber = rand() % (maxNumber - minNumber) + minNumber; // Example: maxNumber = 20, minNumber = 10 --> Random number between 20 and 10
//

#include <iostream>
#include "../Utils/Utils.h"

using namespace std;

class Creature {
protected:
    int healthPoints;
    int damage;
public:
    Creature(int healthPoints) : healthPoints(healthPoints) {}

    void setDamage(int damage) {
        Creature::damage = damage;
    }

    int getDamage() const {
        return damage;
    }

    void attack(Creature *target) {
        target->healthPoints -= (this->damage);
    }

    int getHP() { return healthPoints; }
};

class Gamer : public Creature {
private:
    int potionOfLife;
public:
    Gamer() : Creature(100), potionOfLife(1) {}

    int getPotionOfLife() {
        return potionOfLife;
    }

    bool hasLifePotion() {
        return potionOfLife > 0;
    }

    bool cure() {
        if (this->hasLifePotion()) {
            this->healthPoints += getRandomNumber(20, 30);
            this->potionOfLife -= 1;
            return true;
        }
        return false;

    }
};

int game() {
    srand(time(NULL));
    Gamer *p = new Gamer();
    int choice, creaturesDefeated = 0;
    do {
        cout << "1. fight, 2. cure (" << p->getPotionOfLife() << " available), 3. exit" << endl
             << "HP: " << p->getHP() << endl;
        choice = inputInt(1, 3);
        switch (choice) {
            case 1: {
                // create new creature
                Creature *c = new Creature(getRandomNumber(30, 50));
                // set damage for player and creature
                c->setDamage(getRandomNumber(10, 20));
                p->setDamage(getRandomNumber(10, 20));


                while (true) {
                    // player attacks first
                    cout << "Creature HP before attack: " << c->getHP() << endl;
                    p->attack(c);
                    cout << "Creature HP after attack: " << c->getHP() << endl;
                    // if monster dead, exit while
                    if (c->getHP() < 1) {
                        creaturesDefeated++;
                        break;
                    }
                    // then monster attacks
                    cout << "Gamer HP before attack: " << p->getHP() << endl;
                    c->attack(p);
                    cout << "Gamer HP after attack: " << p->getHP() << endl;
                    // if player dead, exit while
                    if (p->getHP() < 1) break;
                }
                break;
            }
            case 2: {
                if (p->hasLifePotion()) {
                    p->cure();
                } else {
                    cout << "You don't have potions anymore!" << endl;
                }

                break;
            }

        }
        if (p->getHP() < 1) {
            cout << "Gamer is dead, thanks for playing!" << endl << "Defeated creatures: " << creaturesDefeated
                 << endl;
            break;
        }
        if (creaturesDefeated == 3) {
            if (p->hasLifePotion()) cout << "You are a true hero!!" << endl;
            else cout << "You have found a treasure!" << endl;
            break;
        }

    } while (choice != 3);

    return 0;
}