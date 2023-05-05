#include "iostream"
#include "cstdlib"

using namespace std;

class Vehicle {
public:
    Vehicle(const string &brand, const string &licencePlate, int hp, int yearOfConstruction) : brand(brand),
                                                                                               licencePlate(
                                                                                                       licencePlate),
                                                                                               hp(hp),
                                                                                               yearOfConstruction(
                                                                                                       yearOfConstruction) {}

private:
    string brand;
    string licencePlate;
    int hp;
    int yearOfConstruction;

public:
    void displayData() {
        cout << "Brand: " << brand << endl;
        cout << "Licence plate: " << licencePlate << endl;
        cout << "Number of HP: " << hp << endl;
        cout << "Year of construction: " << yearOfConstruction << endl;
    }

    bool operator==(Vehicle &a) {
        return a.brand == brand && a.licencePlate == licencePlate && a.hp == hp &&
               a.yearOfConstruction == yearOfConstruction;
    }

    bool operator>(Vehicle &a) {
        return a.yearOfConstruction > yearOfConstruction;
    }

    bool operator<(Vehicle &a) {
        return a.yearOfConstruction < yearOfConstruction;
    }
};

int veichle() {

    Vehicle a = Vehicle("ford", "abc123", 100, 2000);
    Vehicle b = Vehicle("ford", "abc123", 100, 2000);
    Vehicle c = Vehicle("ford", "abc123", 100, 2007);

    cout << (a == b) << endl;
    cout << (a > c) << endl;
    cout << (a < c) << endl;
    system("pause");
    return 0;
};