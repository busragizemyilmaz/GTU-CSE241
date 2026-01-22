#include <iostream>
using namespace std;

class Circle {
public:
    Circle() { xc = 0; yc = 0; r = 0; }
    Circle(double x, double y, double rad) : xc(x), yc(y), r(rad) { }
    void get(double &xc, double &yc, double &r) {
        xc = this->xc;
        yc = this->yc;
        r = this->r;
    }

    void set(double xc, double yc, double r) {
        this->xc = xc;
        this->yc = yc;
        this->r = r;
    }
    void print();
private:
    double xc;
    double yc;
    double r;
};

class CircleArray {
public:
    CircleArray() : size(0), capacity(1) {
        array = new Circle[capacity];
    }

    void add(const Circle& c) {
        if (size == capacity)
        {
            capacity = capacity * 2;
            Circle *temp = new Circle[capacity];

            for (int i = 0; i < size; i++)
                temp[i] = array[i];

            delete [] array;
            array = temp;
        }

        array[size] = c;
        size++;
    }

    void get(int index, Circle& c) {
        if (index >= 0 && index < size)
            c = array[index];
        else
            cerr << "Index can not be negative and not exceed of size!\n";
    }

    int getsize()
    {
        return size;
    }
private:
    Circle *array;
    int size;
    int capacity;
};