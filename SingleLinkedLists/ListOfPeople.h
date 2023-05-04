//
// Created by Luca on 04/05/2023.
//

#ifndef C___LISTOFPEOPLE_H
#define C___LISTOFPEOPLE_H


#include "Person.h"

class ListOfPeople {
private:
    Person *firstElementPointer;
public:
    ListOfPeople();

    void insert(Person *p);

    Person *remove();

    Person *firstItem();

    bool empty() const;

    void printList();

    void emptyList();
};


#endif //C___LISTOFPEOPLE_H
