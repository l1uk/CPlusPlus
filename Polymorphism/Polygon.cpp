//
// Created by Luca on 05/05/2023.
//

#include <iostream>
#include "Polygon.h"

using namespace std;

class RegularPolygon {
protected:
    float lengthEdgeSize, heightEdgeSize;
public:
    RegularPolygon(float length, float height) : lengthEdgeSize(length), heightEdgeSize(height) {};

    virtual float getArea() = 0;
};

class Triangle : public RegularPolygon {
public:
    Triangle(float length, float height) : RegularPolygon(length, height) {}

private:
    float getArea() { return (lengthEdgeSize * heightEdgeSize) / 2; }
};

class Rectangle : public RegularPolygon {
public:
    Rectangle(float length, float height) : RegularPolygon(length, height) {}

private:
    float getArea() { return (lengthEdgeSize * heightEdgeSize); }
};

int polygon() {

    Triangle *tr = new Triangle(10, 20);
    Rectangle re = Rectangle(12, 12);

    RegularPolygon *t = tr;
    RegularPolygon *r = &re;

    cout << "Triangle:  " << t->getArea() << endl;
    cout << "Rectangle:  " << r->getArea() << endl;

    return 0;
}