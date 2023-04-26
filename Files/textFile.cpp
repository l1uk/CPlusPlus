//
// Simple program to read from a text file
//
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

int readTextFile() {

    std::filesystem::path cwd =
            std::filesystem::current_path().parent_path() / "Files";
    ifstream readingFile(cwd / "test.txt");

    cout << endl << "--- READING ---" << endl;
    string line;
    while (!readingFile.eof()) // Reading from file
    {
        getline(readingFile, line);
        cout << line << endl;
    }
    system("pause");
    return 0;
}

