

#include <iostream>

using namespace std;

int pointersOverwiew() {

    int i = 1, j = 2;

    int &a = i, &b = j;

    a = b; // i = 2

    i = 1, j = 2;

    int *c = &i, *d = &j;

    c = d; // i = 1
    *c = *d; // i = 2

    const double *cptr; // pointer to constant value, but the pointer can change address

    // *cptr = 32; // error
    cptr = cptr;

    int ierr = 0;
    int *const curErr = &ierr; // constant pointer to value, the value can be changed

    *curErr = 12;
    //curErr = curErr; // error

    const double pi = 3.14;

    const double *const pointPi = &pi; // constant pointer to constant value
    //pointPi = &pi; // error
    //*pointPi = 3.15; // error

    return 0;
}

int rValueReference() {

    //right value => temporary object that can be destroyed in a bit
    // right because it can be on the right of an assignment

    int i = 42;

    int &&tmp = i * 42; // rvalue that stores a temporary result

    cout << tmp << endl;

    //int &&temp = i; // error

    return 0;
}

