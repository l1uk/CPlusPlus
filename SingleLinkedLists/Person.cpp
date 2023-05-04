//
// Created by Luca on 04/05/2023.
//

#include "Person.h"

Person::Person(const string &name, const string &surname, int birthYear) : name(name), surname(surname),
                                                                           birthYear(birthYear) {}

const string &Person::getName() const {
    return name;
}

void Person::setName(const string &name) {
    Person::name = name;
}

const string &Person::getSurname() const {
    return surname;
}

void Person::setSurname(const string &surname) {
    Person::surname = surname;
}

int Person::getBirthYear() const {
    return birthYear;
}

void Person::setBirthYear(int birthYear) {
    Person::birthYear = birthYear;
}

void Person::calculateAge() {
    // Determine current year
    time_t timestamp;
    tm *date;
    timestamp = time(0);
    date = localtime(&timestamp);
    int actYear = date->tm_year + 1900;

    cout << "Age: " << actYear - birthYear << " years old" << endl;
}

Person *Person::next() { return successor; } // Returns the successor of my current object

void Person::displayData() {
    cout << "Surname: " << surname << ", First name: " << name;
    cout << ", Year of Birth: " << birthYear << endl;
}

