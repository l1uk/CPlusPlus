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

// 4.	Operator overloading, error handling		25 points
//
// 	Complete the definition of the operator overloading functions outside of the class!
//
// 4.1 	For operator>>, the function should let the user type in the value for the data member val, so that the value will be stored in the data member val of the passed object.
//
// 4.2 	For operator<<, the function should output the value of the data member val of the passed object.
//
// 4.3 	For operator+, the function should return an object of type CALCULATOR, where the data member val holds the value of the addition of the two passed objects.
//
// 4.4 	For operator-, the function should return an object of type CALCULATOR, where the data member val holds the value of the subtraction of the two passed objects.
//
// 4.5 	For operator*, the function should return an object of type CALCULATOR, where the data member val holds the value of the multiplication of the two passed objects.
//
// 4.6 	For operator/, the function should return an object of type CALCULATOR, where the data member val holds the value of the division of the two passed objects.
//	Dividing by 0 should not be possible! Use a try-catch-block to prevent division by zero. If this happens, throw an error and set the value of val to 0.
//
// 4.7 	What's the purpose of using friend?
//	ANSWER: by declaring a class 1 as a friend on another class 2, we can access the private and protected data members of 1 in 2
// the declaration has to be in the base class (the one we want to have access to)
// the "friend" concept is not only defined for whole classes, but also for single functions
// E.G. when we overload << and >> that do not belong to the class CALCULATOR, we declare them as friends so that they can access the private data members
#include <istream>
#include <iostream>

using namespace std;

class CALCULATOR {
private:
    float val;
public:
    CALCULATOR() : val(0) {}

    // Declaring operator overloading functions for calculation
    CALCULATOR operator+(CALCULATOR);

    CALCULATOR operator-(CALCULATOR);

    CALCULATOR operator*(CALCULATOR);

    CALCULATOR operator/(CALCULATOR);

    // Declaring input/output functions as friend of the class
    friend istream &operator>>(istream &is, CALCULATOR &a);

    friend ostream &operator<<(ostream &os, const CALCULATOR &b);
};

istream &operator>>(istream &is, CALCULATOR &a) {
    cout << "Insert val: ";
    cin >> a.val;
    return is;
}

ostream &operator<<(ostream &os, const CALCULATOR &b) {
    cout << "Val: " << b.val << endl;
    return os;
}

CALCULATOR CALCULATOR::operator+(CALCULATOR c) {
    CALCULATOR res = CALCULATOR();
    res.val = val + c.val;
    return res;
}

CALCULATOR CALCULATOR::operator-(CALCULATOR c) {
    CALCULATOR res = CALCULATOR();
    res.val = val - c.val;
    return res;
}

CALCULATOR CALCULATOR::operator*(CALCULATOR c) {
    CALCULATOR res = CALCULATOR();
    res.val = val * c.val;
    return res;
}

CALCULATOR CALCULATOR::operator/(CALCULATOR c) {
    CALCULATOR res = CALCULATOR();
    try {
        if (c.val == 0) {
            throw (string) "Division by 0 forbidden!";
        }
        res.val = val / c.val;
    }
    catch (string e) {
        cout << e << endl;
        res.val = 0;
    }
    return res;
}


int calc() {
    return 0;
}
