#include <iostream>
#include <cstdlib> //exit and rand()

using namespace std;

class Circle {
public:
    void get(double &cx, double &cy, double &cr) { cx = x; cy = y; cr = radius; }
    void set(double newX, double newY, double newRadius);
    Circle(double cr) : x(0), y(0), radius(cr) {
        if (!isValid())
            exit(1);
    }

    Circle() : x(rand()), y(rand()), radius(rand()) {
        if (!isValid())
            exit(1);
    }

    Circle(double cx, double cy, double cr) : x(cx), y(cy), radius(cr) {
        if (!isValid())
            exit(1);
    }
private:
    double x;
    double y;
    double radius;
    bool isValid() {
        return (radius > 0); 
    }
};

void Circle::set(double newX, double newY, double newRadius) {
    x = newX;
    y = newY;
    radius = newRadius;
}
