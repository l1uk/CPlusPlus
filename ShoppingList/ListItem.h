//
// Created by Luca on 04/05/2023.
//

#ifndef C___LISTITEM_H
#define C___LISTITEM_H

#include <string>

using namespace std;

class ListItem {
private:
    string description;
    float price;
    int quantity;
public:
    const string &getDescription() const;

    float getPrice() const;

    int getQuantity() const;

    ListItem(const string &description, float price, int quantity);

    ListItem();

    void displayData();


};


#endif //C___LISTITEM_H
