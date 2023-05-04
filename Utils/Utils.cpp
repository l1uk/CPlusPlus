#include <iostream>

int inputInt(int min, int max) {
    // reading an int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x;
    std::cin >> x;
    while (std::cin.fail()) {
        std::cout << "Error, please input an integer!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    while (x < min || x > max) {
        std::cout << "Value out of range!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    return x;

}

int inputIntExc(int min, int max) {
    // reading an int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x = 0;
    try { std::cin >> x; }
    catch (std::string e) { std::cout << e << std::endl; }
    while (std::cin.fail()) {
        std::cout << "Error, please input an integer!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    if (x < min || x > max) {
        throw (std::string) "Value out of range!";
    }
    return x;

}

int getRandomNumber(int minNumber, int maxNumber) {
    return (rand() % (maxNumber - minNumber) + minNumber);
}

float inputFloat() {
    // reading a float from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    float x;
    std::cin >> x;
    while (std::cin.fail() || x <= 0) {
        std::cout << "Error, please input a positive Float value!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    return x;
}

float inputFloatEx() {
    // reading a float from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    float x;
    std::cin >> x;
    while (std::cin.fail()) {
        std::cout << "Error, please input a positive Float value!" << std::endl << "Input: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> x;
    }
    if (x <= 0) {
        throw (std::string) "Error! Please insert a positive value";
    }
    return x;
}