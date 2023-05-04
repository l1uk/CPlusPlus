//
// Created by Luca on 04/05/2023.
//

#include <iostream>
#include "ListItem.h"

ListItem::ListItem(const string &description, float price, int quantity) : description(description), price(price),
                                                                           quantity(quantity) {}

ListItem::ListItem() {

}

void ListItem::displayData() {
    std::cout << "Name: " << description << ", Price: " << price
              << ", Quantity: " << quantity << std::endl;
}

const string &ListItem::getDescription() const {
    return description;
}

float ListItem::getPrice() const {
    return price;
}

int ListItem::getQuantity() const {
    return quantity;
}
