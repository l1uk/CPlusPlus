#include <list>
#include <iostream>
#include <limits>
#include <filesystem>
#include <fstream>
#include "ListItem.h"
#include "../Utils/Utils.h"

void loadFile(list<ListItem> &list, filesystem::path fileName);

void saveFile(list<ListItem> &list, filesystem::path fileName);

void showlist(string str, list<ListItem> &L);

ListItem newItem();

using namespace std;

int shoppingList() {

    filesystem::path fileName =
            filesystem::current_path().parent_path() / "ShoppingList" / "shoppingList.dat";


    list<ListItem> shoppingList;


    loadFile(shoppingList, fileName);

    int choice = 0;

    ListItem item;
    int index = 0;
    do {
        // Print the menu and collect user choice in choice variable
        cout << "Welcome to the Main Menu, at the moment there are " << shoppingList.size() << " items in the list"
             << endl << endl << "Commands:" << endl <<
             "1 to create a new item" << endl << "2 to modify an item" << endl << "3 to delete an item"
             << endl << "4 to show available items" << endl << "5 to empty the list" << endl << "6 to exit" << endl
             << endl << "Input: ";
        try {
            choice = inputInt(0, 6);
        }
        catch (string e) { cout << e << endl; }

        switch (choice) {
            case 1: {
                item = newItem();
                if (item.getDescription() != "")
                    shoppingList.push_back(item);
                break;
            }
            case 2: {
                showlist("Choose an item to modify: ", shoppingList);
                if (shoppingList.size() > 0)
                    index = inputInt(1, shoppingList.size());
                else {
                    cout << "List is empty!" << endl;
                    break;
                }
                item = newItem();
                if (item.getDescription() == "") break;
                list<ListItem>::iterator it = shoppingList.begin();
                advance(it, index - 1);
                it = shoppingList.erase(it);
                shoppingList.insert(it, item);
                break;
            }
            case 3: {
                showlist("Choose an item to erase: ", shoppingList);
                if (shoppingList.size() > 0) {
                    bool input = false;
                    while (!input) {
                        try {
                            index = inputIntExc(1, shoppingList.size());
                            input = true;
                        }
                        catch (string e) {
                            cout << e << endl;
                        }
                    }
                } else {
                    cout << "List is empty!" << endl;
                    break;
                }
                list<ListItem>::iterator it = shoppingList.begin();
                advance(it, index - 1);
                it = shoppingList.erase(it);
                break;
            }
            case 4: {
                showlist("Shopping list: ", shoppingList);
                break;
            }
            case 5: {
                shoppingList.clear();
            }
        }
    } while (choice != 6);

    saveFile(shoppingList, fileName);


    return 0;
}

void saveFile(list<ListItem> &shoppingList, filesystem::path fileName) {
    ofstream outputFile(fileName, ios::out);
    if (outputFile.good()) {
        list<ListItem>::iterator it;
        for (it = shoppingList.begin(); it != shoppingList.end(); it++) {
            outputFile << it->getDescription() << "\t" << it->getPrice() << "\t" << it->getQuantity() << endl;
        }
    } else {
        throw "Error during file write!";
    }
}

void loadFile(list<ListItem> &shoppingList, filesystem::path fileName) {
    ifstream inputFile(fileName);
    string name;
    int quantity;
    float price;
    if (inputFile.good()) {
        while (inputFile >> name >> price >> quantity) {
            shoppingList.push_back(
                    ListItem(name, price, quantity)
            );
        }

    } else {
        throw "Error during file read!";
    }
}

void showlist(string str, list<ListItem> &L) // Definition of the showlist function: Returns the contents of the list
{
    list<ListItem>::iterator i;
    cout << str << endl;
    int index = 1;
    for (i = L.begin(); i != L.end(); ++i) {
        cout << "Element #" << index++ << ": ";
        i->displayData();
    }

    cout << endl;
}

ListItem newItem() {
    string newName;
    float newPrice;
    int newQuantity;
    cout << "Insert name: ";
    cin >> newName;
    try {
        cout << "Insert price: ";
        newPrice = inputFloatEx();
        cout << "Insert quantity: ";
        newQuantity = inputIntExc(0, numeric_limits<int>::max());
    } catch (string e) {
        cout << e << endl;
        return ListItem();
    }

    return ListItem(newName, newPrice, newQuantity);
}
