//
// Created by Luca on 04/05/2023.
//

#ifndef C___PERSON_H
#define C___PERSON_H

#include <string>
#include <iostream>

using namespace std;

class Person {

    friend class ListOfPeople;

private:
    string name;
    string surname;
    int birthYear;
    Person *successor;
public:
    Person(const string &name, const string &surname, int birthYear);

    const string &getName() const;

    void setName(const string &name);

    const string &getSurname() const;

    void setSurname(const string &surname);

    int getBirthYear() const;

    void setBirthYear(int birthYear);

    void calculateAge();

    Person *next();

    void displayData();
};


#endif //C___PERSON_H
