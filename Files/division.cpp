

#include <iostream>
#include <filesystem>
#include <fstream>

using namespace std;

int inputInt(int min, int max);

int division() {
    cout << "Welcome" << endl;

    filesystem::path cwd =
            filesystem::current_path().parent_path() / "Files";

    ofstream outputFile(cwd / "division.txt", ios::app | ios::out);

    bool stay = true;
    int dividend, divisor;
    do {
        try {
            cout << "Insert dividend & divisor" << endl;
            cin >> dividend >> divisor;
            if (divisor == 0)
                throw (string) "Divisor is 0!";
            cout << dividend / divisor << endl;
            if(outputFile.good())
                outputFile << dividend << "/" << divisor << " = " << dividend / divisor << endl;
            else
                throw (string) "Error during file write phase";
        }
        catch (string e) { cout << e << endl; }
        cout << "Do you want to make another calculation?";
        stay = inputInt(0, 1);

    } while (stay);

    outputFile.close();

    ifstream inputFile(cwd / "division.txt");

    string row;

    cout << "History: " << endl;

    while(!inputFile.eof()){
        getline(inputFile,row);
        cout << row << endl;
    }

    return 0;
}

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

