#include <iostream>
#include <list>

using namespace std;

template<class T>
class Comparison {
private:
    T one, two;
public:
    Comparison(T one, T two) : one(one), two(two) {
    }

    T getMin();

    T add();

    T multiply();
};

template<class T>
T Comparison<T>::getMin() {
    return (one < two ? one : two);
}

template<class T>
T Comparison<T>::multiply() {
    return one * two;
}

template<class T>
T Comparison<T>::add() {
    return one + two;
}

//overriding function add for two strings
template<>
string Comparison<string>::add() {
    return (string) one + " " + two;
}

template<>
string Comparison<string>::multiply() {
    return (string) one + " * " + two;
}

template<class T>
float calcAvg(T arr[], int len = 0) {
    float partialSum = 0;
    for (int i = 0; i < len; i++) {
        partialSum += arr[i];
    }
    partialSum /= len;
    return partialSum;
}

template<class T>
void printArray(T arr[], int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i] << "  ";
    }
    cout << endl;
}

template<class T>
void swapElements(T *a, T *b) {
    T c = *a;
    *a = *b;
    *b = c;
}

template<class T>
void bubbleSortArray(T arr[], int len) {
    for (int i = len - 1; i >= 0; i--) {
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[i]) {
                swapElements(&arr[i], &arr[j]);
            }
        }
    }
    cout << endl;
}


int avgEx() {

    double arr[] = {1, 2.5, 3};
    float res = calcAvg(arr, 3);
    cout << res << endl;

    return 0;
}

int comparisonEx() {
    int a = 10, b = 20;
    Comparison var(a, b);
    Comparison<double> expl(10.2, 20.4);
    Comparison ch('a', 'b');
    cout << var.getMin() << endl;
    cout << expl.getMin() << endl;

    return 0;
}

int calcEx() {
    Comparison integer(10, 20);
    Comparison doubles(20.4, 422.3);
    Comparison chars('a', 'b');
    Comparison strings((string) "ciao", (string) "come va");
    cout << "Integer: " << integer.add() << "  " << integer.multiply() << endl;
    cout << "Doubles: " << doubles.add() << "  " << doubles.multiply() << endl;
    cout << "Chars: " << chars.add() << "  " << chars.multiply() << endl;
    cout << "Strings: " << strings.add() << "  " << strings.multiply() << endl;

    return 0;
}

int sortEx() {

    int intArr[] = {5, 4, 3, 2, 1, 6, 8, 4, 4};

    string stringArr[] = {(string) "bbc", (string) "aad", (string) "aaa"};

    printArray(intArr, 9);
    printArray(stringArr, 3);

    bubbleSortArray(intArr, 9);
    bubbleSortArray(stringArr, 3);

    printArray(intArr, 9);
    printArray(stringArr, 3);

    return 0;

}

