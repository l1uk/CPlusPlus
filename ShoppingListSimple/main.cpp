// simple program that enables the user to create a shopping list with a maximum fixed length, and sort it by price

#include <iostream>
#include <cstdlib>
#include "../Utils/Utils.h"

using namespace std;

// method that prints the shopping list
void printElements(string[], float[], int);

//method that sorts the shopping list by price
void sortElementsByPrice(string[], float[], int);

int muin(int argc, char *argv[]) {

    // state max lenght of the list and declare 2 arrays for prices and names
    const int maxLength = 10;

    float prices[maxLength];
    string names[maxLength];

    // initialize arrays with empty elements
    for (int i = 0; i < maxLength; i += 1) {
        prices[i] = 0.0;
        names[i] = "";
    }

    // variable that holds the current number of items and acts as an index for the arrays
    int numItems = 0;

    int choice;
    do {
        // Print the menu and collect user choice in choice variable
        cout << "Welcome to the Main Menu, at the moment there are " << numItems << " items in the list (capacity = "
             << maxLength << ") ;" << endl << endl << "Commands:" << endl <<
             "1 to create a new item" << endl << "2 to show available items"
             << endl << "3 to sort items by price" << endl << "4 to exit" << endl << endl << "Input: ";

        choice = inputInt(1, 4);

        switch (choice) {
            case 1:
                // in case there is room in the list ask the user for data and save it, then increment the numItems variable
                if (numItems < maxLength) {
                    string newName;
                    float newPrice;
                    cout << "Insert name: ";
                    cin >> newName;
                    cout << "Insert price: ";
                    newPrice = inputFloat();
                    names[numItems] = newName;
                    prices[numItems] = newPrice;
                    numItems++;
                } else { cout << "The shopping list is full!" << endl; }
                cout << endl;
                break;
            case 2:
                printElements(names, prices, numItems);
                break;
            case 3:
                sortElementsByPrice(names, prices, numItems);
                cout << "Sorted list: " << endl;
                printElements(names, prices, numItems);
                break;
            case 4:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Not a valid choice" << endl;
                break;
        }
        cout << endl;
    } while (choice != 4); // if choice is equal to 4, it means that the user wants to exit the program

    system("pause");

    return 0;
}


int inputInteger(int min, int max) {
    // reading a int in a range from cin, the cin.fail() method return false when an alphanumeric string is inputted instead of a numeric value
    // inspiration taken from https://stackoverflow.com/questions/18728754/checking-cin-input-stream-produces-an-integer
    int x;
    cin >> x;
    while (cin.fail()) {
        cout << "Error, please input an integer!" << endl << "Input: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> x;
    }
    while (x < min || x > max) {
        cout << "Value out of range!" << endl << "Input: ";
        cin.clear();
        cin.ignore(256, '\n');
        cin >> x;
    }
    return x;

}

void sortElementsByPrice(string names[], float prices[], int size) {
    // bubble sort the prices array and apply the same swaps on the names array

    float tmp_price = 0.0;
    string tmp_name = "";
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (prices[i] > prices[j]) {
                tmp_price = prices[i];
                prices[i] = prices[j];
                prices[j] = tmp_price;

                tmp_name = names[i];
                names[i] = names[j];
                names[j] = tmp_name;
            }
        }
    }
}

void printElements(string names[], float prices[], int numItems) {
    for (int i = 0; i < numItems; i++) {
        cout << "Element #" << i + 1 << ": " << names[i] << ", Price " << prices[i] << endl;
    }
}


