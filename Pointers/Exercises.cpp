#include <iostream>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

using namespace std;

int swapExercise() {

    int a = 10, b = 20;

    cout << a << " " << b << endl;

    swap(&a, &b);

    cout << a << " " << b << endl;

    return 0;

}

void incrementEachByOne(int *arrayStart, int *arrayEnd) {
    int *i = arrayStart;
    while (i != arrayEnd) {
        ++(*i);
        ++i;
    }
}

int arrayModificationExercise() {
    int numbers[] = {10, 20, 30};
    incrementEachByOne(numbers, numbers + 2);

    cout << numbers[0];

    return 0;
}

int stringLength(char *startString, const int maxLength) {

    int len = -1;
    char tmp;

    do {
        tmp = *startString;
        startString++;
        len++;
        if (len == maxLength - 1) { return len; }
    } while (tmp != '\0');

    return len;

}

int stringLengthExercise() {
    const int MAX_LENGTH = 50;
    char string[MAX_LENGTH] = "";
    cout << "Input string: ";
    cin >> string;

    int length = stringLength(string, MAX_LENGTH);

    cout << "String length: " << length << endl;

    return 0;

}