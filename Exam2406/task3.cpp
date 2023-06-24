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

// 3. 	Abstract classes and polymorphism   		20 points
//
// 3.1  Extend the below given class Property by adding the correct data members given in the constructor.
//      Only derived classes should be able to change these data members. The program should then run error-free.
//
// 3.2  Modify the class Property so that it will be an abstract class [by using the member function print()].
//
// 3.3  What is special about abstract base classes?
//	Name at least 3 features.				
//      ANSWER:
//      -  Abstract classes cannot instantiate objects
//      -  Derived classes inherits pure virtual functions, so if they are not explicitly re-defined the derived class is still abstract
//      -  Pointer of abstract class type can be created (that point to a derived non-abstract object)
//
// 3.4  Extend the program by adding a derived class House of the abstract class Property.
//      This derived class should have the data member floors, which is of the data type int,
//      and furnished, which is of the data type bool, implemented.
//      It’s also supposed to have a default constructor and a constructor member initializer list.
//      Which member function(s) have to be implemented to run the program? Implement this member function(s).
// the function print() needs to be implemented

#include <iostream>

using namespace std;

class Property {
protected:
    float area;
    string location, street;
    static int count;
public:
    Property() { count++; };

    Property(float a, string l, string s) : area(a), location(l), street(s) { count++; };

    virtual void print() = 0; //Output of the data
};

int Property::count = 0;

class House : Property {

private:
    int floors;
    bool furnished;
public:
    House() : Property() {};

    House(float a, string l, string s, int f, bool furnish) : Property(a, l, s), floors(f), furnished(furnish) {};

    void print() {
        cout << "Area: " << area << " Location: " << location << " Street: " << street << " Floors: " << floors
             << " Furnished: " << furnished << endl;
    }

};;

int property() {

    House a = House();

    return 0;
}
