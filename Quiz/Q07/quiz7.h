#ifndef SHAPES_H
#define SHAPES_H

#include <iostream>
#include <string>

class Shape {
public:
    Shape() : x(0), y(0), r(0), type("") { }
    Shape(int x, int y, int r, std::string s) : x(x), y(y), r(r), type(s) { }
    virtual void draw() = 0;
    virtual bool compare(const Shape *other);
protected:
    int x;
    int y;
    int r;
    std::string type;
};

class Circle : public Shape {
public:
    Circle(int x, int y, int r) : Shape(x, y, r, "circle") { }
    void draw() override;
};

class Square : public Shape {
public:
    Square(int x, int y, int r) : Shape(x, y, r, "square") { }
    void draw() override;
};

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int r, int r2) : Shape(x, y, r, "rectangle"), r2(r2) { }
    void draw() override;
    bool compare(const Shape *other) override;
private:
    int r2;
};

#endif