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

// 5.  	Templates and Arrays		                	20 points
//
// 5.1 	Perform the following task:
// 	In the program below, a two-dimensional array named "expenditure" is defined 
//	in which the expenditure of the last three years over 12 months is stored.
//     	In the second year, the expenditure of the months April, May and June 
//     	is increased by exactly 20% compared to the previous year
//     	and the expenditure of the months July, August and September 
//	is increased by exactly 25% compared to the previous year.
//     	In the third year, the expenditure of each month
//     	is increased by exactly 10% compared to the previous year.
//     	Expand the program with exactly this adjustment of the expenses in the second 
//     	and third year and store them accordingly in the array "expenditure".
//
// 5.2 	Create a template function "Average".
//	The first input parameter is an array (any data type) and the second holds the number of elements of the array.
//	Calculate the average of each expenditure year with this function by using a for-loop in your main program
//	and output the result. The result is always of type double!

#include <iostream>

#define NUM_MONTHS 12
using namespace std;

void print(double (*matrix)[NUM_MONTHS], int num_years) {
    for (int i = 0; i < num_years; i++) {
        for (int j = 0; j < NUM_MONTHS; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void increase_expenses(double (*matrix)[NUM_MONTHS], int num_years) {
    for (int year_index = 0; year_index < num_years; year_index++) {
        for (int month_index = 0; month_index < NUM_MONTHS; month_index++) {
            if (year_index == 1 && month_index >= 3 && month_index <= 5) { // april, may, june of second year
                matrix[year_index][month_index] = matrix[year_index - 1][month_index] * 1.20;
            } else if (year_index == 1 && month_index >= 6 &&
                       month_index <= 8) { // july, august, september of second year
                matrix[year_index][month_index] = matrix[year_index - 1][month_index] * 1.25;
            } else if (year_index == 2) {
                matrix[year_index][month_index] = matrix[year_index - 1][month_index] * 1.1;
            } else if (year_index > 0) {
                matrix[year_index][month_index] =
                        matrix[year_index - 1][month_index];
            }
        }
        cout << endl;
    }
}

double average(double *arrayStart, int arrayLength) {
    int counter = 0;
    double sum = 0;
    for (double *el = arrayStart; counter < arrayLength; el++) {
        counter++;
        sum += *el;
    }
    return sum / arrayLength;
}

int matrix() {
    const int NUM_YEARS = 3;
    double expenditure[NUM_YEARS][NUM_MONTHS] = {{10, 15, 20, 36, 15, 45, 20, 35, 24, 64, 52, 12},
                                                 {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
                                                 {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}};

    increase_expenses(expenditure, NUM_YEARS);
    print(expenditure, NUM_YEARS);

    cout << "Average of first year: " <<
         average(expenditure[0], NUM_MONTHS) << endl;

    cout << "Average of second year: " <<
         average(expenditure[1], NUM_MONTHS) << endl;

    cout << "Average of third year: " <<
         average(expenditure[2], NUM_MONTHS) << endl;
    return 0;
}
