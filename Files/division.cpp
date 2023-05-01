

#include <iostream>
#include <filesystem>
#include <fstream>
#include "../Utils/Utils.h"

using namespace std;

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


