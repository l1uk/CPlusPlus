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

// 1. Basics                         	 			15 points
//
// 1.1 	Declare a class Candle with the following data members:
// 	Height (in cm) and color. Choose appropriate data types. Only derived classes can change these data members.
// 	Define for the class:
// 	a) Default constructor
// 	b) Parameterized constructor with member initialization list
// 	c) Member function "data_output" for outputting all data of the class. The member function "data_output" should be defined outside the class.
//
// 1.2 	Definition of member functions
// 	You know from experience that a candle loses an average of 2.5 cm in "height" every hour.
// 	Define a member function “update_height” with a parameter “burning_hours” and a suitable data type for it.
// 	The task of the member function is to update the "height" of the candle based on the hours.
// 	If the candle has burned down after the update, the user should get a corresponding message, 
// 	otherwise the user gets as the output the current height of the candle.
//
// 1.3 	Dynamic instantiation
// 	Define two dynamic objects of the class Candle. Since the values of the data members do not have to be queried, 
// 	they can be passed as static members. 
// 	Call the member function „data_output“ for the second instance and the member function „updateHeight“ for the first instance.

#include <iostream>

using namespace std;

class Candle {
private:
    double height;
    string color;
    constexpr static const double CM_PER_HOUR = 2.5;
public:
    Candle() {};

    Candle(double h, string c) : height(h), color(c) {}

    void data_output();

    void update_height(double burning_hours) {
        if (burning_hours > 0) {
            height = height - (burning_hours * CM_PER_HOUR);
        }
        if (height <= 0) {
            height = 0;
            cout << "Candle is burned down!" << endl;
        } else {
            cout << "Height after " << burning_hours << "hrs of burning: " << height << "cm" << endl;
        }
    }
};

void Candle::data_output() {
    cout << "Height: " << height << "cm" << ", color: " << color << endl;
}

int candle() {

    double h1 = 25, h2 = 10;
    string color1 = "red", color2 = "blue";

    Candle *c1 = new Candle(h1, color1), *c2 = new Candle(h2, color2);

    (*c2).data_output();

    c1->update_height(9.9);

    return 0;
}
