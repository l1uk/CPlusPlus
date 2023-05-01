#include <iostream>
#include <limits>
#include "../Utils/Utils.h"

using namespace std;

int dynamicArray() {

    cout << "Insert size of the array: ";

    int arraySize = inputInt(0, numeric_limits<int>::max());

    int *a = new int[arraySize];
    int *copyOf_a = a;


    for (int i = 0; i < arraySize; i += 1) {
        *(copyOf_a++) = inputInt(numeric_limits<int>::min(), numeric_limits<int>::max());
    }

    copyOf_a = a;

    for (int i = 0; i < arraySize; i += 1) {
        cout << *(copyOf_a++) << endl;
    }

    delete [] a;

    return 0;
}