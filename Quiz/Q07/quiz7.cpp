#include <iostream>
#include <string>
#include "quiz7.h"

using namespace std;

bool Shape::compare(const Shape *other) {
    if (type == other->type)
        return ((x == other->x) && (y == other->y) && (r == other->r));
    
    return false;
}

void Circle::draw() {
    cout << "This is a circle at (" 
         << x << "," << y << "," << r << ")\n";
}

void Square::draw() {
    cout << "This is a square at (" 
         << x << "," << y << "," << r << ")\n";
}

void Rectangle::draw() {
    cout << "This is a rectangle at (" 
         << x << "," << y << "," << r << "," << r2 << ")\n";
}

bool Rectangle::compare(const Shape *other) {
    if(Shape::compare(other) == false)
        return false;
    
    const Rectangle* recPtr = dynamic_cast<const Rectangle*>(other);
    if (recPtr != nullptr)
        return (r2 == recPtr->r2);

    return false;
}
