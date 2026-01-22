#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
public:
    Point() : x(0), y(0) { }
    Point(double px, double py) : x(px), y(py) { }
    friend std::ostream& operator<<(std::ostream& os, const Point& other);
    void setx(double px);
    void sety(double py);
    friend Point operator+(const Point& p1, const Point& p2);
    friend bool operator==(const Point& p1, const Point& p2);
private:
    double x;
    double y;
};

#endif