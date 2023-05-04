//
// Created by Luca on 04/05/2023.
//

#include "ListOfPeople.h"

ListOfPeople::ListOfPeople() : firstElementPointer(0) {}

void ListOfPeople::insert(Person *p) {
    p->successor = firstElementPointer;
    firstElementPointer = p;
}

Person *ListOfPeople::remove() {
    if (firstElementPointer != 0) {
        Person *tmp = firstElementPointer;
        firstElementPointer = firstElementPointer->successor;
        return tmp;
    }
    return nullptr;
}

bool ListOfPeople::empty() const {
    return firstElementPointer == 0;
}

Person *ListOfPeople::firstItem() {
    return firstElementPointer;
}

void ListOfPeople::printList() {
    Person *p = firstElementPointer;
    if (p == 0) cout << "Empty List!!" << endl;
    while (p != 0) {
        p->displayData();
        p = p->successor;
    }
}

void ListOfPeople::emptyList() {
    Person *p = 0;
    do {
        p = remove();
    } while (p != 0);
}
