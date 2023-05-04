#include <iostream>
#include <limits>
#include "../Utils/Utils.h"


int dynamicArray() {

    std::cout << "Insert size of the array: ";

    int arraySize = inputInt(0, std::numeric_limits<int>::max());

    int *a = new int[arraySize];
    int *copyOf_a = a;


    for (int i = 0; i < arraySize; i += 1) {
        *(copyOf_a++) = inputInt(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    }

    copyOf_a = a;

    for (int i = 0; i < arraySize; i += 1) {
        std::cout << *(copyOf_a++) << std::endl;
    }

    delete[] a;

    return 0;
}