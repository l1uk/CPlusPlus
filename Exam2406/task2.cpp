// Deggendorf Institute of Technology - vhb Exam
// Examination subject:     Programming in C++ / Part 1+2 (6 ECTS)
// Semester:                Summer 2023
// Examiner:                Prof. Dr. Peter Faber
// Score:                   90 Points
// Additional Materials:    None
// Duration:                90 Minutes

// ----- YOUR INFORMATION -----
// Street+House number: Schirmitzer Weg 2
// Surname, First name: Volonterio Luca
// Postcode + City: 92637, Weiden in der Oberpfalz
// Matriculation number: 744690 (IT), 14695321(DE, Erasmus+)
// E-Mail: l.volonterio@oth-aw.de
// ----------------------------

// 2.	Linked lists                    			10 points
//
// 2.1  Create a default constructor for the class ListOfWorkers, which initalizes the data member Head with the value NULL.
//
// 2.2  Add one line of code in the class Worker so that the class ListOfWorkers has access to the private data members.
//      The data members should still be private and getters/setters are not allowed!
//
// 2.3 	Create a member function insert_front in the class ListOfWorkers with no parameters which does the following:
//	A new dynamic object of type Worker should be created.
//	The user should fill the data members birthYear and name of that dynamic object.
//	Afterwards, the new node should be inserted at the start of the linked list.
//	Make use of the data members next and head.
//
// 2.4 	Create an object of the class ListOfWorkers in the main function.
//	Call the member function insert_front.


#include <iostream>

using namespace std;

class Worker {

    friend class ListOfWorkers;

private:
    int birthYear;
    string name;
    Worker *next;
public:
    Worker() {}
};

class ListOfWorkers {
private:
    Worker *head;
public:
    ListOfWorkers() : head(NULL) {};

    void insert_front() {
        Worker *w = new Worker();
        cout << "Enter worker name: ";
        cin >> w->name;
        cout << "Enter worker birth year: ";
        cin >> w->birthYear;
        w->next = head;
        head = w;
    }
};


int workers() {

    ListOfWorkers l = ListOfWorkers();

    l.insert_front();

    return 0;
}
