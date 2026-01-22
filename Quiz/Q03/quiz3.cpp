#include <iostream>
#include "quiz3.h"

using namespace std;

std::ostream& operator<<(std::ostream& os, const Point& other) {
    os << "(" << other.x << "," << other.y << ")";

    return os;
}

void Point::setx(double px) {
    x = px;
}

void Point::sety(double py) {
    y = py;
}

Point operator+(const Point& p1, const Point& p2) {
    double newX = p1.x + p2.x;
    double newY = p1.y + p2.y;

    return Point(newX, newY);
}

bool operator==(const Point& p1, const Point& p2) {
    return ((p1.x == p2.x) && (p1.y == p2.y));
}