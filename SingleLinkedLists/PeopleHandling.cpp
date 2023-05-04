#include <list>
#include "ListOfPeople.h"

using namespace std;

void showlist(string, list<Person> &); // Declaration of the showlist function

int peopleHandling() {
    ListOfPeople listOfPeople;

    list<Person> L;

    char ans = 'y';
    string surname = "", name = "";
    int birthYear;

    Person *p;

    while (ans == 'y') {
        cout << "Surname: " << endl;
        cin >> surname;
        cout << endl << "First name: " << endl;
        cin >> name;
        cout << endl << "Year of birth: " << endl;
        cin >> birthYear;

        p = new Person(name, surname, birthYear);

        listOfPeople.insert(p);

        L.push_back(*p);

        cout << "Insert another? (y/n)" << endl;
        cin >> ans;

    }

    listOfPeople.printList();

    listOfPeople.emptyList();

    showlist("Stock c++ list: ", L);

    L.clear();

    return 0;
}

void showlist(string str, list<Person> &L) // Definition of the showlist function: Returns the contents of the list
{
    list<Person>::iterator i;
    cout << str << endl;
    for (i = L.begin(); i != L.end(); ++i)
        i->displayData();
    cout << endl;
}